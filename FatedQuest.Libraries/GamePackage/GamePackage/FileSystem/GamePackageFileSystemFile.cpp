#include "GamePackageFileSystemFile.h"
#include "../../../StandardOperations/AllReferences.h"

#include <iostream>

#include "../PackageFile.h"

#include "PackageFiles.h"

using namespace FatedQuestLibraries;

GamePackageFileSystemFile::GamePackageFileSystemFile(const std::shared_ptr<PackageFiles>& files)
{
    m_packageFiles = files;
    Refresh();
}

GamePackageFileSystemFile::~GamePackageFileSystemFile()
{
    m_filePaths.clear();
}

bool GamePackageFileSystemFile::Exists(const std::string& filepath) const
{
    std::string path = File::Sanitize(filepath);
    return m_filePaths.contains(path);
}

std::string GamePackageFileSystemFile::ReadFileContents(const std::string& filepath) const
{
    std::string path = File::Sanitize(filepath);
    if (m_filePaths.contains(path))
    {
        return m_filePaths.at(path)->ReadFileContents();
    }

    return {};
}

std::vector<std::string> GamePackageFileSystemFile::ReadFileContentsByLine(const std::string& filepath) const
{
    std::string path = File::Sanitize(filepath);
    if (m_filePaths.contains(path))
    {
        return m_filePaths.at(path)->ReadFileContentsByLine();
    }

    return {};
}

std::vector<unsigned char> GamePackageFileSystemFile::ReadFileContentsExplicitly(const std::string& filepath) const
{
    std::string path = File::Sanitize(filepath);
    if (m_filePaths.contains(path))
    {
        return m_filePaths.at(path)->ReadFileContentsExplicitly();
    }

    return {};
}

void GamePackageFileSystemFile::Refresh()
{
    m_filePaths.clear();

    for (const std::shared_ptr<PackageFile>& file : m_packageFiles->GetFiles())
    {
        std::string path = File::Sanitize(file->Path());
        if (!m_filePaths.contains(path))
        {
            m_filePaths.insert_or_assign(path, file);
        }
    }
}

