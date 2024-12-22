#include "PackageFileUnarchived.h"
#include "../../StandardOperations/AllReferences.h"
#include "PackagePaths.h"

using namespace FatedQuestLibraries;

PackageFileUnarchived::PackageFileUnarchived(std::weak_ptr<PackagePaths> paths, const std::string& path) : PackageFilePathing(paths, path)
{
    if (const std::shared_ptr<PackagePaths> sharedPtr = paths.lock())
    {
        std::string directoryName = sharedPtr->ProductsDirectoryName();
        if (directoryName.empty())
        {
            m_fullPath = Directory::CombinePath(sharedPtr->ProductsDirectory(), path);
        }
        else
        {
            m_fullPath = Directory::CombinePath(sharedPtr->ProductsDirectory(), directoryName, path);
        }
    }
}

std::string PackageFileUnarchived::ReadFileContents()
{
    return File::ReadFileContents(m_fullPath);
}

std::vector<std::string> PackageFileUnarchived::ReadFileContentsByLine()
{
    std::string fileContents = File::ReadFileContents(m_fullPath);
    return StringHelpers::Split(fileContents, "\n");
}