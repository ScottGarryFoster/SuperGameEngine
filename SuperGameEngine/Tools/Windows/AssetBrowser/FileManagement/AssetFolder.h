#pragma once
#include <memory>
#include <string>
#include <vector>

namespace SuperGameTools
{
    class AssetFile;

    /// <summary>
    /// Represents a single folder potentially containing assets.
    /// </summary>
    class AssetFolder
    {
    public:

        /// <summary>
        /// Get the files which are directly contained within this folder.
        /// </summary>
        /// <returns>Get all the asset files directly within this folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFile>> GetContainingFiles() const = 0;

        /// <summary>
        /// Get the folders which are directly contained within this folder.
        /// </summary>
        /// <returns>Get all the asset folders directly within this folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFolder>> GetContainingFolders() const = 0;

        /// <summary>
        /// Get the name of the folder to display in the asset browser.
        /// </summary>
        /// <returns>The name of the folder to display. </returns>
        virtual std::string GetDisplayName() const = 0;

        /// <summary>
        /// Get the package path of the given directory.
        /// </summary>
        /// <returns>Get the path to this directory relative to the package. </returns>
        virtual std::string GetPackagePath() const = 0;

        /// <summary>
        /// Gets the parent folder.
        /// </summary>
        /// <returns>The parent of the given folder. </returns>
        virtual std::weak_ptr<AssetFolder> GetParent() const = 0;
    };
}
