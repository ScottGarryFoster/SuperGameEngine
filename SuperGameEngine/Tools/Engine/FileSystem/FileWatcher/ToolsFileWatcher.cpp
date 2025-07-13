#include "ToolsFileWatcher.h"
#include "../../../FatedQuestLibraries.h"
#include "FileUpdateAction.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <string>

#include "FileUpdateEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsFileWatcher::ToolsFileWatcher(const std::shared_ptr<FatedQuestLibraries::PackagePaths>& paths)
{
    m_packagePaths = paths;
}

ToolsFileWatcher::~ToolsFileWatcher()
{
    Stop();
}

void ToolsFileWatcher::Start()
{
    // Start watching for files and ensure we can stop it on deconstruction
    m_watchFiles.store(true, std::memory_order_relaxed);
    std::thread worker(&ToolsFileWatcher::WatchTask, this);
    m_watchTaskThread = std::move(worker);
}

void ToolsFileWatcher::Stop()
{
    m_watchFiles.store(false, std::memory_order_relaxed);
    if (m_watchTaskThread.joinable())
    {
        m_watchTaskThread.join();
    }
}

std::weak_ptr<FEventSubscriptions> ToolsFileWatcher::WatchFolder(const std::string& packageFolder)
{
    // Ensure we have a uniform path which is a directory
    std::string cleanedPath = File::Sanitize(packageFolder);
    if (!cleanedPath.empty())
    {
        std::string fullPath = Directory::CombinePath(m_packagePaths->ProductsDirectory(), m_packagePaths->ProductsDirectoryName(), cleanedPath);
        if (!Directory::IsDirectory(fullPath))
        {
            std::vector<std::string> folderPieces = StringHelpers::Split(cleanedPath, "\\");
            cleanedPath = {};
            for (size_t d = 0; d < folderPieces.size() - 1; ++d)
            {
                std::string& directory = folderPieces.at(d);
                if (cleanedPath.empty())
                {
                    cleanedPath += directory;
                }
                else
                {
                    cleanedPath += "\\" + directory;
                }
            }
        }
    }

    // No need for the backslash for our purposes.
    if (cleanedPath.ends_with("\\"))
    {
        cleanedPath = cleanedPath.substr(0, cleanedPath.size() - 1);
    }

    std::weak_ptr<FEventSubscriptions> returnSubscription = {};
    // We require the events, ensure we have a lock and only for as long as we need.
    {
        std::unique_lock lock(m_lastKnownFileStatusLock);
        if (m_completeFolderWatchers.contains(cleanedPath))
        {
            returnSubscription = m_completeFolderWatchers.at(cleanedPath);
        }
        else
        {
            auto newEvent = std::make_shared<FEvent>();
            m_completeFolderWatchers.insert_or_assign(cleanedPath, newEvent);
            return newEvent;
        }
    }

    return returnSubscription;
}

void ToolsFileWatcher::WatchTask()
{
    while (m_watchFiles.load(std::memory_order_relaxed))
    {
        std::string fullPackagePath = Directory::CombinePath(m_packagePaths->ProductsDirectory(), m_packagePaths->ProductsDirectoryName());
        FileUpdateCheckResults fileUpdates;
        {
            std::unique_lock lock(m_lastKnownFileStatusLock);

            fileUpdates = GetUpdatesFromFiles(fullPackagePath, m_lastKnownFileStatus);
            FindAndAddDeletes(fileUpdates, m_lastKnownFileStatus);
        }

        // Early out, no updates, no events.
        if (fileUpdates.UpdatesDiscovered.empty())
        {
            continue;
        }


        for (const auto& [watcherKey, watcherValue] : m_completeFolderWatchers)
        {
            std::vector<std::string> addedFiles;
            std::vector<std::string> removedFiles;
            std::vector<std::string> updatedFiles;
            for (const auto& [updateKey, updateValue] : fileUpdates.UpdatesDiscovered)
            {
                // If this entry is relevant to the watcher.
                if (!updateKey.starts_with(watcherKey))
                {
                    continue;
                }

                FileUpdateAction action = updateValue.first;
                switch (action)
                {
                    case FileUpdateAction::Added:
                    {
                        addedFiles.push_back(updateKey);
                        break;
                    }
                    case FileUpdateAction::Updated:
                    {
                        updatedFiles.push_back(updateKey);
                        break;
                    }
                    case FileUpdateAction::Removed:
                    {
                        removedFiles.push_back(updateKey);
                        break;
                    }
                    default:
                        Log::Error("There is not a response for file event: " + 
                            EFileUpdateAction::ToString(action) + ". Nothing sent",
                            "ToolsFileWatcher::WatchTask");
                }
            }

            // No updates no event.
            if (addedFiles.empty() && updatedFiles.empty() && removedFiles.empty())
            {
                continue;
            }

            auto eventArgument = std::make_shared<FileUpdateEventArguments>(addedFiles, updatedFiles, removedFiles);
            watcherValue->Invoke(eventArgument);
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

ToolsFileWatcher::FileUpdateCheckResults ToolsFileWatcher::GetUpdatesFromFiles(
    const std::string& directory,
    std::unordered_map<std::string, FileStatus>& currentFileStatus)  const
{
    FileUpdateCheckResults updateStorage;

    std::string fullPackagePath = Directory::CombinePath(m_packagePaths->ProductsDirectory(), m_packagePaths->ProductsDirectoryName());
    std::string packagePath = File::MakeRelative(fullPackagePath, directory);

    // If we are sending in the root, this can also happen
    if (packagePath == ".")
    {
        packagePath = "";
    }

    GetUpdatesFromFiles(directory, currentFileStatus, packagePath, updateStorage);
    return updateStorage;
}

void ToolsFileWatcher::GetUpdatesFromFiles(
    const std::string& directory,
    std::unordered_map<std::string, FileStatus>& currentFileStatus,
    const std::string& packagePath,
    FileUpdateCheckResults& currentUpdates)  const
{
    std::vector<std::string> filenames = Directory::ListFileNames(directory);
    for (const std::string& filename : filenames)
    {
        const std::string fullpath = Directory::CombinePath(directory, filename);
        const std::string currentFilePackagePath = Directory::CombinePath(packagePath, filename);

        // I have found that between deletes and detections, files may appear in here but not exist.
        if (!File::Exists(fullpath))
        {
            continue;
        }

        currentUpdates.FoundFiles.insert(currentFilePackagePath);

        FileStatus latestStatus = GetFileStatus(fullpath, currentFilePackagePath);
        if (currentFileStatus.contains(currentFilePackagePath))
        {
            const FileStatus current = currentFileStatus.at(currentFilePackagePath);
            if (current.LastModified < latestStatus.LastModified)
            {
                auto update = std::pair(FileUpdateAction::Updated, latestStatus);
                currentUpdates.UpdatesDiscovered.insert_or_assign(currentFilePackagePath, update);
                currentFileStatus.insert_or_assign(currentFilePackagePath, (FileUpdateAction::Updated, latestStatus));
            }
        }
        else
        {
            auto newEntry = std::pair(FileUpdateAction::Added, latestStatus);
            currentUpdates.UpdatesDiscovered.insert_or_assign(currentFilePackagePath, newEntry);
            currentFileStatus.insert_or_assign(currentFilePackagePath, (FileUpdateAction::Added, latestStatus));
        }
    }

    std::vector<std::string> directories = Directory::ListDirectoryNames(directory);
    for (const std::string& directoryName : directories)
    {
        std::string directoryFullPath = Directory::CombinePath(directory, directoryName);
        std::string directoryPackagePath = Directory::CombinePath(packagePath, directoryName);
        GetUpdatesFromFiles(directoryFullPath, currentFileStatus, directoryPackagePath, currentUpdates);
    }
}

ToolsFileWatcher::FileStatus ToolsFileWatcher::GetFileStatus(
    const std::string& filepath,
    const std::string& packagePath) const
{
    std::time_t lastModified = File::GetLastModifiedTime(filepath);
    if (lastModified == 0)
    {
        Log::Error("Could not get last modified time of: " + packagePath,
            "ToolsFileWatcher::GetFileStatus(const std::string&,const std::string&)");
    }

    return { filepath, packagePath, lastModified };
}

void ToolsFileWatcher::FindAndAddDeletes(
    FileUpdateCheckResults& fileUpdates,
    std::unordered_map<std::string, FileStatus>& allCurrentFiles)
{
    std::vector<std::string> missingFiles;
    missingFiles.reserve(allCurrentFiles.size());

    for (const auto& [key, value] : allCurrentFiles)
    {
        if (fileUpdates.FoundFiles.find(key) == fileUpdates.FoundFiles.end())
        {
            missingFiles.push_back(key);
        }
    }

    for (const std::string& missingFile : missingFiles)
    {
        allCurrentFiles.erase(missingFile);
        auto deleteEntry = std::pair(FileUpdateAction::Removed, FileStatus(missingFile, missingFile, 0));
        fileUpdates.UpdatesDiscovered.insert_or_assign(missingFile, deleteEntry);
    }
}
