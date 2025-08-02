#pragma once
#include <mutex>
#include <queue>

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
    class AssetTemplateProvider;
    class FileUpdateEventArguments;
    class AssetMetaData;
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
            const std::shared_ptr<FatedQuestLibraries::PackagePaths>& packagePaths,
            const std::shared_ptr<AssetTemplateProvider>& assetTemplateProvider);
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
        /// Where to store the asset templates within the game package.
        /// </summary>
        const std::string m_assetTemplateFolder = "Tools\\AssetTemplates";

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
        /// Updates about the files in the game package.
        /// </summary>
        std::queue<std::shared_ptr<FileUpdateEventArguments>> m_reloadPackageQueue;

        /// <summary>
        /// True when we are adding to or using the queue.
        /// </summary>
        std::mutex m_reloadPackageQueueLock;

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

        /// <summary>
        /// Loads, holds and provides <see cref="AssetMetaData"/> in a single location.
        /// Describes what asset metadata files are exactly, what files they relate to, how to edit them and so on.
        /// </summary>
        std::shared_ptr<AssetTemplateProvider> m_assetTemplateProvider;

        void SearchAllFilesForPotentialMissingAssetFiles();
        void SearchAllFilesForPotentialMissingAssetFiles(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage, const std::string& currentDirectory);
        void CreateAssetFilesForValidAssets();

        /// <summary>
        /// Tries to find the asset template file.
        /// </summary>
        /// <param name="packagePath">Path to the game package file. </param>
        /// <param name="assetFileContents">If found, the contents are created and returned. </param>
        /// <returns>True means a match was found, false means this type is not an asset. </returns>
        bool TryFindAssetFileTemplate(const std::string& packagePath, std::string& assetFileContents);

        /// <summary>
        /// Looks at the given package path and if applicable will create an asset file.
        /// </summary>
        /// <param name="gamePackage">Game package containing all the files which we know about. </param>
        /// <param name="packagePath">Path to attempt to observe. </param>
        void TryAddAssetFile(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage, const std::string& packagePath);

        /// <summary>
        /// Setup the listener to file changes.
        /// </summary>
        void ListenToFilePackageChanges();

        /// <summary>
        /// Process or attempt to process if there is something any changes to the file system.
        /// Will create asset files and reload the game package.
        /// </summary>
        void ProcessFilePackageChanges();
    };
}
