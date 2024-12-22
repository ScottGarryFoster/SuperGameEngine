#include "PackageFileUnarchived.h"
#include "../../StandardOperations/AllReferences.h"
#include "PackagePaths.h"
#include "../../BinaryOperations/BinaryZip/BinaryZip.h"
#include "../../BinaryOperations/BinaryZip/StandardBinaryZip.h"

using namespace FatedQuestLibraries;

PackageFileUnarchived::PackageFileUnarchived(
    const std::weak_ptr<PackagePaths>& paths, 
    const std::shared_ptr<BinaryZip>& binaryZip,
    const std::string& path) : PackageFilePathing(paths, path)
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

    m_binaryZip = binaryZip;
}

std::string PackageFileUnarchived::ReadFileContents()
{
    if (m_packageFileStorageType == PackageFileStorageType::Binary)
    {
        std::vector<unsigned char> data;
        std::vector<std::string> error;
        m_binaryZip->BinaryToData(
            m_fullPath, data, error);

        std::string contents(data.begin(), data.end());
        return contents;
    }
    
    return File::ReadFileContents(m_fullPath);
}

std::vector<std::string> PackageFileUnarchived::ReadFileContentsByLine()
{
    std::string fileContents = ReadFileContents();
    return StringHelpers::Split(fileContents, "\n");
}