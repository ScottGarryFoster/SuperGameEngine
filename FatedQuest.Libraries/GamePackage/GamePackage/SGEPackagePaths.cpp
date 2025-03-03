#include "../../StandardOperations/AllReferences.h"
#include "SGEPackagePaths.h"

using namespace FatedQuestLibraries;

SGEPackagePaths::SGEPackagePaths()
{
    m_lastDiscoveredProductsDirectory = {};
    m_lastDiscoveredProductsDirectory = FindProductsDirectory();
}

std::string SGEPackagePaths::ProductsDirectory() const
{
#ifdef _DEBUG
    return FindProductsDirectory();
#endif

    std::string exePath = FilePaths::ApplicationDirectory();
    std::filesystem::path exeFilepath(exePath);
    return exeFilepath.string();
}

std::string SGEPackagePaths::ProductsDirectoryName() const
{
    return "Products";
}

std::string SGEPackagePaths::ProductsArchiveName() const
{
    return "Products.zip";
}

std::string SGEPackagePaths::FindProductsDirectory() const
{
    if (!m_lastDiscoveredProductsDirectory.empty())
    {
        return m_lastDiscoveredProductsDirectory;
    }

    std::filesystem::path currentPath(FilePaths::ApplicationDirectory());
    std::string productsDirectory = Directory::CombinePath(currentPath, ProductsDirectoryName());
    std::string productsArchive = Directory::CombinePath(currentPath, ProductsDirectoryName());
    for (size_t i = 0; i < 10; ++i)
    {
        if (Directory::Exists(productsDirectory) || File::Exists(productsArchive))
        {
            break;
        }

        currentPath = currentPath.parent_path();
        productsDirectory = Directory::CombinePath(currentPath, ProductsDirectoryName());
        productsArchive = Directory::CombinePath(currentPath, ProductsDirectoryName());
    }

    return currentPath.string();
}
