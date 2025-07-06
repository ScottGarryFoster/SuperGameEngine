#pragma once
#include <memory>
#include <vector>

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
    };
}
