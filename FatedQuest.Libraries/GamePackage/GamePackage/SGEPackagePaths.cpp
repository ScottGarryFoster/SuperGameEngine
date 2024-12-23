#include "../../StandardOperations/AllReferences.h"
#include "SGEPackagePaths.h"

using namespace FatedQuestLibraries;

std::string SGEPackagePaths::ProductsDirectory() const
{
    std::string exePath = FilePaths::ApplicationDirectory();
    std::filesystem::path exeFilepath(exePath);
#ifdef _DEBUG
    std::filesystem::path threeAbove = exeFilepath.parent_path().parent_path().parent_path();
    return threeAbove.string();
#endif
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