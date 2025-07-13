#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
    /// <summary>
    /// Watches the requested folder for updates to files and presents its findings.
    /// </summary>
    class FileWatcher
    {
    public:
        virtual ~FileWatcher() = default;

        /// <summary>
        /// Starts watching for file updates.
        /// </summary>
        virtual void Start() = 0;

        /// <summary>
        /// Stops watching for file updates.
        /// </summary>
        virtual void Stop() = 0;

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
        virtual std::weak_ptr<FatedQuestLibraries::FEventSubscriptions> WatchFolder(const std::string& packageFolder) = 0;
    };
}
