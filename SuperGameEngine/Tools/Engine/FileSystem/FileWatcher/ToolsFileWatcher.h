#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>

#include "FileWatcher.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace FatedQuestLibraries
{
    class PackagePaths;
}

namespace SuperGameTools
{
    enum class FileUpdateAction : uint8_t;
    
    /// <summary>
    /// Watches the requested folder for updates to files and presents its findings.
    /// Keep in mind, this is multithreaded and the invokes will therefore be on the threads.
    /// </summary>
    class ToolsFileWatcher : public FileWatcher
    {
    public:
        ToolsFileWatcher(const std::shared_ptr<FatedQuestLibraries::PackagePaths>& paths);
        virtual ~ToolsFileWatcher() override;

        /// <summary>
        /// Starts watching for file updates.
        /// </summary>
        virtual void Start() override;

        /// <summary>
        /// Stops watching for file updates.
        /// </summary>
        virtual void Stop() override;

        /// <summary>
        /// Watches the given folder and will invoke only when there are changes.
        /// The watcher will not invoke instantly and there will be a cooldown to allow a full list of
        /// changes to come through.
        /// </summary>
        /// <param name="packageFolder">Folder location relative to the game package. </param>
        /// <returns>
        /// Listener to the folder.
        /// Uses FileUpdateEventArguments as the return arguments.
        /// </returns>
        virtual std::weak_ptr<FatedQuestLibraries::FEventSubscriptions> WatchFolder(const std::string& packageFolder) override;

    private:

        struct FileStatus
        {
            std::string FullPath;
            std::string PackagePath;
            std::time_t LastModified;

            FileStatus(const std::string& fullpath, const std::string& packagePath, const std::time_t& lastModified)
            {
                FullPath = fullpath;
                PackagePath = packagePath;
                LastModified = lastModified;
            }
        };

        struct FileUpdateCheckResults
        {
            std::unordered_map<std::string, std::pair<FileUpdateAction, FileStatus>> UpdatesDiscovered;
            std::unordered_set<std::string> FoundFiles;
        };

        /// <summary>
        /// Event call backs without any filtering applied on the files.
        /// These watchers are interested in all files within the given folder.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<FatedQuestLibraries::FEvent>> m_completeFolderWatchers;

        /// <summary>
        /// The actual thread for the watch task.
        /// </summary>
        std::thread m_watchTaskThread;

        /// <summary>
        /// True when files should be watched.
        /// </summary>
        std::atomic<bool> m_watchFiles;

        /// <summary>
        /// Helps us to find where the package is on file.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::PackagePaths> m_packagePaths;

        /// <summary>
        /// Keeps a record of all known files and the last known status for these files.
        /// </summary>
        std::unordered_map<std::string, FileStatus> m_lastKnownFileStatus;

        /// <summary>
        /// Lock for Last Known File Status
        /// </summary>
        std::mutex m_lastKnownFileStatusLock;

        /// <summary>
        /// The code run multithreaded which will check for files.
        /// </summary>
        void WatchTask();

        /// <summary>
        /// Gets all the file updates from the given folder.
        /// </summary>
        FileUpdateCheckResults  GetUpdatesFromFiles(
            const std::string& directory, 
            std::unordered_map<std::string, FileStatus>& currentFileStatus) const;

        /// <summary>
        /// Gets all the file updates from the given folder.
        /// This is the recursive version which searches everything.
        /// </summary>
        void  GetUpdatesFromFiles(
            const std::string& directory,
            std::unordered_map<std::string, FileStatus>& currentFileStatus,
            const std::string& packagePath,
            ToolsFileWatcher::FileUpdateCheckResults& currentUpdates)  const;

        /// <summary>
        /// Get a single file's status.
        /// </summary>
        /// <param name="filepath">Full file path. </param>
        /// <param name="packagePath">Path to the file relative to the package. </param>
        /// <returns>The updated file status. </returns>
        FileStatus GetFileStatus(const std::string& filepath, const std::string& packagePath) const;


        void FindAndAddDeletes(FileUpdateCheckResults& fileUpdates, std::unordered_map<std::string, FileStatus>& pairs);
    };
}
