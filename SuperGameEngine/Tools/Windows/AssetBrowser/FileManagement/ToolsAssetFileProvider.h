#pragma once
#include <mutex>

#include "AssetFileProvider.h"
#include "../../../FatedQuestLibraries.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameEngine
{
    class TextureManager;
}

namespace SuperGameTools
{
    class FileWatcher;
    class ToolsAssetFolder;

    /// <summary>
    /// Implementation of <see cref="AssetFileProvider"/>
    /// </summary>
    class ToolsAssetFileProvider : public AssetFileProvider, public FatedQuestLibraries::FEventObserver
    {
    public:

        ToolsAssetFileProvider(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::shared_ptr<FatedQuestLibraries::PackagePaths>& packagePaths);
        virtual ~ToolsAssetFileProvider() override;

        /// <summary>
        /// Run on the main loop. Responds to updates.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Get all folders in root directory of the products folder.
        /// </summary>
        /// <returns>Returns all the folders within the root directory of the products folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFolder>> GetFoldersInRootDirectory() const override;

        /// <summary>
        /// Get all files in the root directory of the products folder.
        /// </summary>
        /// <returns>Returns all files in the root directory of the products folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFile>> GetFilesInRootDirectory() const override;

        /// <summary>
        /// Get the top level folder.
        /// </summary>
        /// <returns>The top level folder. </returns>
        virtual std::shared_ptr<AssetFolder> GetRootFolder() const override;

        /// <summary>
        /// Gets the event listener called when the file system detects changes.
        /// </summary>
        /// <returns>Event listener called when the file system detects changes.</returns>
        virtual std::weak_ptr<FatedQuestLibraries::FEventSubscriptions> OnFileSystemUpdated() const override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

    private:
        /// <summary>
        /// All the folders at the root level.
        /// </summary>
        std::shared_ptr<ToolsAssetFolder> m_rootFolder;

        /// <summary>
        /// Given game package.
        /// </summary>
        std::weak_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// Given texture manager.
        /// </summary>
        std::weak_ptr<SuperGameEngine::TextureManager> m_textureManager;

        /// <summary>
        /// True when we should we reload all the files we care about.
        /// </summary>
        std::atomic<bool> m_reloadPackage;

        /// <summary>
        /// Allows us to update the asset browser on file updates.
        /// </summary>
        std::shared_ptr<FileWatcher> m_fileWatcher;

        /// <summary>
        /// Subscription to the file watcher. Kept to unsubscribe.
        /// </summary>
        std::weak_ptr<FatedQuestLibraries::FEventSubscriptions> m_watcherSubscription;

        /// <summary>
        /// Helper class to grab paths.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::PackagePaths> m_packagePaths;

        /// <summary>
        /// Event trigger when the file system updates.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onFileSystemUpdated;

        void CreateAssetFilesForValidAssets();
    };
}
