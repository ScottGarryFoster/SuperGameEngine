#include "FileUpdateEventArguments.h"

using namespace SuperGameTools;

FileUpdateEventArguments::FileUpdateEventArguments(
    const std::vector<std::string>& addedFiles,
    const std::vector<std::string>& updatedFiles,
    const std::vector<std::string>& deletedFiles)
{
    m_filesAdded = addedFiles;
    m_filesUpdated = updatedFiles;
    m_filesDeleted = deletedFiles;
}

std::vector<std::string> FileUpdateEventArguments::GetFilesAdded() const
{
    return m_filesAdded;
}

std::vector<std::string> FileUpdateEventArguments::GetFilesUpdated() const
{
    return m_filesUpdated;
}

std::vector<std::string> FileUpdateEventArguments::GetFilesDeleted() const
{
    return m_filesDeleted;
}
