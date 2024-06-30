#include "ActiveDiskFileHandler.h"
#include "FilepathCollectionFromExternalSource.h"
#include "LibraryIncludes.h"

using namespace PackageFileProvider;
using namespace StandardCLibrary;

ActiveDiskFileHandler::ActiveDiskFileHandler(const std::string& topLevelFolder)
{
    m_topLevelDirectory = topLevelFolder;
}

bool ActiveDiskFileHandler::ReadFileContents
    (const std::string& filepath, std::string& fileOutput) const
{
    return false;
}

bool ActiveDiskFileHandler::ReadFileContentsUnsigned
    (const std::string& filepath, std::vector<unsigned char>& fileOutput) const
{
    return false;
}

const std::shared_ptr<const FilepathCollection> ActiveDiskFileHandler::GetFilePathInfo() const
{
    // Note: Do not store this, it is for externals only.
    std::shared_ptr<const FilepathCollection> filepathCollection =
        std::enable_shared_from_this<FilepathCollection>::shared_from_this();
    return filepathCollection;
}

const std::vector<std::string> ActiveDiskFileHandler::GetAllFiles() const
{
    return Directory::GetFilesOnlyStd(m_topLevelDirectory, true);
}

bool ActiveDiskFileHandler::Exists(const std::string& filePath) const
{
    std::string cleanInnerPath = filePath;
    std::replace(cleanInnerPath.begin(), cleanInnerPath.end(), '\\', '/');
    std::string newPath = m_topLevelDirectory + "\\" + cleanInnerPath;
    return File::Exists(newPath);
}

const std::vector<std::string> ActiveDiskFileHandler::GetAllFilesInDirectory(const std::string& directoryPath) const
{
    return Directory::GetFilesOnlyStd(m_topLevelDirectory + "\\" + directoryPath, true);
}
