#include "CombinedGamePackage.h"

#include "PackageFileUnarchived.h"
#include "PackageFileArchived.h"
#include "PackagePaths.h"
#include "../../StandardOperations/AllReferences.h"

#include "../../BinaryOperations/BinaryZip/StandardBinaryZip.h"
#include "PackageFile.h"

using namespace FatedQuestLibraries;

CombinedGamePackage::CombinedGamePackage()
{
    m_binaryZip = std::make_shared<StandardBinaryZip>();
}

CombinedGamePackage::~CombinedGamePackage()
{
}

bool CombinedGamePackage::Load(std::shared_ptr<PackagePaths> paths)
{
    std::string productsOnFile = Directory::CombinePath(paths->ProductsDirectory(), "Products");
    if (Directory::Exists(productsOnFile))
    {
        std::vector<std::string> files;
        FillListWithAllProductsFiles(productsOnFile, {}, files);

        for (const std::string& file : files)
        {
            std::string f = file;
            m_systemFile.push_back(
                std::make_shared<PackageFileUnarchived>(paths, f));
        }
    }

    std::string productArchive = Directory::CombinePath(paths->ProductsDirectory(), "Products.zip");
    if (File::Exists(productArchive))
    {
        std::vector<std::string> errors;
        std::vector<std::string> files = 
            m_binaryZip->ListFilesInArchive(
                productArchive, errors);

        std::shared_ptr<PackageFile> packageFile = std::make_shared<PackageFileArchived>(paths, m_binaryZip,
            "Engine\\Input\\ControllerMappings\\NintendoN64Controller.xml");
        std::string contents = packageFile->ReadFileContents();
        std::vector<std::string> contentsLines = packageFile->ReadFileContentsByLine();
    }

    return true;
}

void CombinedGamePackage::FillListWithAllProductsFiles(
    const std::string& productsPath, 
    const std::string& currentPath,
    std::vector<std::string>& files)
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