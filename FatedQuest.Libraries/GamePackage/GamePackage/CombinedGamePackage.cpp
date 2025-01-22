#include "CombinedGamePackage.h"

#include "PackageFileUnarchived.h"
#include "PackageFileArchived.h"
#include "PackagePaths.h"
#include "../../StandardOperations/AllReferences.h"

#include "../../BinaryOperations/BinaryZip/StandardBinaryZip.h"
#include "PackageFile.h"
#include "FileSystem/GamePackageFileSystem.h"

using namespace FatedQuestLibraries;

CombinedGamePackage::CombinedGamePackage()
{
    m_binaryZip = std::make_shared<StandardBinaryZip>();
    m_fileSystem = std::make_shared<GamePackageFileSystem>();
}

CombinedGamePackage::~CombinedGamePackage()
{
}

const std::shared_ptr<PackageFileSystemFile> CombinedGamePackage::File() const
{
    return m_fileSystem->File();
}

const std::shared_ptr<PackageFileSystemDirectory> CombinedGamePackage::Directory() const
{
    return m_fileSystem->Directory();
}

bool CombinedGamePackage::Reload() const
{
    if (!m_packagePaths)
    {
        return false;
    }

    m_fileSystem->ForgetFiles();

    if (!AddAllFiles())
    {
        return false;
    }
}

bool CombinedGamePackage::Load(const std::shared_ptr<PackagePaths>& paths)
{
    m_packagePaths = paths;

    return Reload();
}

void CombinedGamePackage::FillListWithAllProductsFiles(
    const std::string& productsPath, 
    const std::string& currentPath,
    std::vector<std::string>& files) const
{
    std::string fullPath = Directory::CombinePath(productsPath, currentPath);

    std::vector<std::string> currentFiles = Directory::GetFiles(fullPath);
    std::vector<std::string> currentFilesAsFullpaths = std::vector<std::string>(currentFiles.size());
    for (size_t i = 0; i < currentFilesAsFullpaths.size(); ++i)
    {
        currentFilesAsFullpaths[i] = Directory::CombinePath(currentPath, currentFiles[i]);
    }

    files.insert(files.end(), currentFilesAsFullpaths.begin(), currentFilesAsFullpaths.end());

    std::vector<std::string> directories = Directory::ListDirectoryNames(fullPath);
    for (const std::string& directory : directories)
    {
        std::string relativePath = Directory::CombinePath(currentPath, directory);
        FillListWithAllProductsFiles(productsPath, relativePath, files);
    }
}

bool CombinedGamePackage::AddAllFiles() const
{
    if (!m_packagePaths)
    {
        return false;
    }

    std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>> gamePackageFiles;

    std::string productsOnFile = Directory::CombinePath(m_packagePaths->ProductsDirectory(), "Products");
    if (Directory::Exists(productsOnFile))
    {
        std::vector<std::string> files;
        FillListWithAllProductsFiles(productsOnFile, {}, files);

        for (const std::string& file : files)
        {
            auto newFile = std::make_shared<PackageFileUnarchived>(m_packagePaths, m_binaryZip, file);
            gamePackageFiles.emplace_back(PackageFileOrigin::Unarchived, newFile);
        }
    }

    std::string productArchive = Directory::CombinePath(m_packagePaths->ProductsDirectory(), "Products.zip");
    if (File::Exists(productArchive))
    {
        std::vector<std::string> errors;
        std::vector<std::string> files =
            m_binaryZip->ListFilesInArchive(
                productArchive, errors);

        for (const std::string& file : files)
        {
            auto newFile = std::make_shared<PackageFileArchived>(m_packagePaths, m_binaryZip, file);
            gamePackageFiles.emplace_back(PackageFileOrigin::Archived, newFile);
        }
    }

    m_fileSystem->GiveFiles(gamePackageFiles);

    return true;
}
