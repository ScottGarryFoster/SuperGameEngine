#include "PackageFileUnarchived.h"
#include "../../StandardOperations/AllReferences.h"
#include "PackagePaths.h"

using namespace FatedQuestLibraries;

PackageFileUnarchived::PackageFileUnarchived(std::weak_ptr<PackagePaths> paths, const std::string& path) : PackageFilePathing(paths, path)
{

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