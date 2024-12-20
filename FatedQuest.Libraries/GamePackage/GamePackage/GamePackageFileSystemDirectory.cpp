#include "GamePackageFileSystemDirectory.h"

#include "PackageFile.h"
#include "PackageFiles.h"
#include "../../StandardOperations/FileHandling/File.h"
#include "../../StandardOperations/FileHandling/Directory.h"

using namespace FatedQuestLibraries;

GamePackageFileSystemDirectory::GamePackageFileSystemDirectory(const std::shared_ptr<PackageFiles>& files)
{
    m_packageFiles = files;
    Refresh();
}

GamePackageFileSystemDirectory::~GamePackageFileSystemDirectory()
{
}

bool GamePackageFileSystemDirectory::Exists(const std::string& path) const
{
    std::string cleanPath = File::Sanitize(path);
    return m_filePaths.contains(cleanPath);
}

std::vector<std::string> GamePackageFileSystemDirectory::GetFiles(const std::string& path) const
{
    std::string cleanPath = File::Sanitize(path);
    if (m_filePaths.contains(cleanPath))
    {
        std::vector<std::string>
            answer(
                m_filePaths.at(cleanPath).begin(),
                m_filePaths.at(cleanPath).end());
        return answer;
    }
    return {};
}

std::vector<std::string> GamePackageFileSystemDirectory::ListDirectories(const std::string& path) const
{
    return {};
}

std::vector<std::string> GamePackageFileSystemDirectory::ListDirectoryNames(const std::string& path) const
{
    return {};
}

void GamePackageFileSystemDirectory::Refresh()
{
    m_filePaths.clear();

    for (const std::shared_ptr<PackageFile>& file : m_packageFiles->GetFiles())
    {
        std::string path = File::Sanitize(file->Path());
        std::vector<std::string> pathPieces = StringHelpers::Split(path, "\\");
        std::string directory = Directory::GetParent(path);
        if (!directory.empty())
        {
            if (m_filePaths.contains(directory))
            {
                if (!m_filePaths.at(directory).contains(pathPieces.back()))
                {
                    m_filePaths.at(directory).insert(pathPieces.back());
                }
            }
            else
            {
                std::unordered_set<std::string> paths;
                paths.insert(pathPieces.back());
                m_filePaths.insert_or_assign(directory, paths);
            }

            std::string current = pathPieces[0];
            for (size_t i = 0; i < pathPieces.size() - 2; ++i)
            {
                const std::string& nextDirectory = pathPieces[i + 1];
                if (m_directories.contains(current))
                {
                    if (!m_directories.at(current).contains(nextDirectory))
                    {
                        m_directories.at(current).insert(nextDirectory);
                    }

                }

                current += "\\" + nextDirectory;
            }
        }

    }
}
