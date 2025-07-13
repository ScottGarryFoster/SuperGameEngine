#pragma once
#include <memory>
#include <vector>

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
    class AssetFile;
    class AssetFolder;

    /// <summary>
    /// Provides all files we know about.
    /// </summary>
    class AssetFileProvider
    {
    public:
        /// <summary>
        /// Run on the main loop. Responds to updates.
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// Get all folders in root directory of the products folder.
        /// </summary>
        /// <returns>Returns all the folders within the root directory of the products folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFolder>> GetFoldersInRootDirectory() const = 0;

        /// <summary>
        /// Get all files in the root directory of the products folder.
        /// </summary>
        /// <returns>Returns all files in the root directory of the products folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFile>> GetFilesInRootDirectory() const = 0;

        /// <summary>
        /// Get the top level folder.
        /// </summary>
        /// <returns>The top level folder. </returns>
        virtual std::shared_ptr<AssetFolder> GetRootFolder() const = 0;

        /// <summary>
        /// Gets the event listener called when the file system detects changes.
        /// </summary>
        /// <returns>Event listener called when the file system detects changes.</returns>
        virtual std::weak_ptr<FatedQuestLibraries::FEventSubscriptions> OnFileSystemUpdated() const = 0;
    };
}
