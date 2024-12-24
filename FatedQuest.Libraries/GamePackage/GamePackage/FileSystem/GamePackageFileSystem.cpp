#include "GamePackageFileSystem.h"

#include <unordered_set>

#include "GamePackageFileSystemDirectory.h"
#include "GamePackageFileSystemFile.h"
#include "PackageFiles.h"
#include "../PackageFile.h"
#include "../../../Logger/Logger/Log.h"

using namespace FatedQuestLibraries;

GamePackageFileSystem::GamePackageFileSystem()
{
    m_packageFiles = std::make_shared<PackageFiles>();
    m_fileSystem = std::make_shared<GamePackageFileSystemFile>(m_packageFiles);
    m_directorySystem = std::make_shared<GamePackageFileSystemDirectory>(m_packageFiles);
}

GamePackageFileSystem::~GamePackageFileSystem()
{
}

const std::shared_ptr<PackageFileSystemFile> GamePackageFileSystem::File() const
{
    return m_fileSystem;
}

const std::shared_ptr<PackageFileSystemDirectory> GamePackageFileSystem::Directory() const
{
    return m_directorySystem;
}

void GamePackageFileSystem::GiveFiles(
    const std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>>& packageFiles)
{
    for (const std::pair < PackageFileOrigin, std::shared_ptr<PackageFile>>& pair : packageFiles)
    {
        switch (pair.first)
        {
        case PackageFileOrigin::Archived:
            AddToCollection(m_archivedFiles, pair.second);
            break;
        case PackageFileOrigin::Unarchived:
        case PackageFileOrigin::Unknown:
            AddToCollection(m_unarchivedFiles, pair.second);
            break;
        default:
            Log::Exception("No implementation for: " + EPackageFileOrigin::ToString(pair.first), "GamePackageFileSystem::GiveFiles", "NotImplementedException");
            break;
        }
    }

    Refresh();
}

void GamePackageFileSystem::Refresh()
{
    std::vector<std::shared_ptr<PackageFile>> newSet;
    std::unordered_set<std::string> pathsAdded;
    for (const auto& [key, value] : m_unarchivedFiles)
    {
        if (!pathsAdded.contains(key))
        {
            pathsAdded.insert(key);
            newSet.push_back(value);
        }
    }

    for (const auto& [key, value] : m_archivedFiles)
    {
        if (!pathsAdded.contains(key))
        {
            pathsAdded.insert(key);
            newSet.push_back(value);
        }
    }

    m_packageFiles->SetFiles(newSet);
    m_fileSystem->Refresh();
    m_directorySystem->Refresh();
}

void GamePackageFileSystem::AddToCollection(std::unordered_map<std::string, std::shared_ptr<PackageFile>>& collection,
                                            const std::shared_ptr<PackageFile>& potentialNewEntry) const
{
    std::string path = File::Sanitize(potentialNewEntry->Path());
    if (path.ends_with(".gz"))
    {
        path = path.substr(0, path.length() - 3);
    }

    collection.insert_or_assign(path, potentialNewEntry);
}
