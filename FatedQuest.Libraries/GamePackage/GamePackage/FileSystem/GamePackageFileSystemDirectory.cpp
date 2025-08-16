#include "GamePackageFileSystemDirectory.h"

#include "../PackageFile.h"
#include "PackageFiles.h"
#include "../../../SharedEnums/CaseRespective.h"
#include "../../../StandardOperations/FileHandling/File.h"
#include "../../../StandardOperations/FileHandling/Directory.h"

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

    // Directories are stored without the final \\ on the end.
    if (!cleanPath.empty() && cleanPath.size() > 1 && cleanPath.ends_with('\\'))
    {
        cleanPath = cleanPath.substr(0, cleanPath.length());
    }

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
    std::string cleanPath = File::Sanitize(path);
    if (m_directories.contains(cleanPath))
    {
        std::vector<std::string> answer;
        for (const std::string& directoryRelative : m_directories.at(cleanPath))
        {
            answer.push_back(Directory::CombinePath(cleanPath, directoryRelative));
        }
        return answer;
    }

    return {};
}

std::vector<std::string> GamePackageFileSystemDirectory::ListDirectoryNames(const std::string& path) const
{
    std::string cleanPath = File::Sanitize(path);
    if (m_directories.contains(cleanPath))
    {
        std::vector<std::string>
            answer(
                m_directories.at(cleanPath).begin(),
                m_directories.at(cleanPath).end());
        return answer;
    }

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

        AddPathToCollection(m_filePaths, directory, file->Path());

        if (pathPieces.size() > 1)
        {
            std::string current = pathPieces[0];
            for (size_t i = 0; i < pathPieces.size() - 2; ++i)
            {
                const std::string& nextDirectory = pathPieces[i + 1];
                AddToCollection(m_directories, current, nextDirectory);

                current += "\\" + nextDirectory;
            }

            // Ensure to add top level directories
            AddToCollection(m_directories, {}, pathPieces[0]);
        }

    }
}

void GamePackageFileSystemDirectory::AddToCollection(
    std::unordered_map<std::string, std::unordered_set<std::string>>& collection, 
    const std::string& key, 
    const std::string& newValue) const
{
    if (collection.contains(key))
    {
        if (!collection.at(key).contains(newValue))
        {
            collection.at(key).insert(newValue);
        }
    }
    else
    {
        std::unordered_set<std::string> paths;
        paths.insert(newValue);
        collection.insert_or_assign(key, paths);
    }
}

void GamePackageFileSystemDirectory::AddPathToCollection(
    std::unordered_map<std::string, std::unordered_set<std::string>>& collection,
    const std::string& directory,
    const std::string& rawPath) const
{
    std::string path = File::Sanitize(rawPath);
    std::vector<std::string> pathPieces = StringHelpers::Split(path, "\\");

    AddToCollection(collection, directory, pathPieces.back());
}
