#pragma once
#include "AssetFileProvider.h"

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

    /// <summary>
    /// Implementation of <see cref="AssetFileProvider"/>
    /// </summary>
    class ToolsAssetFileProvider : public AssetFileProvider
    {
    public:

        ToolsAssetFileProvider(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture);

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

    private:
        /// <summary>
        /// All the folders at the root level.
        /// </summary>
        std::shared_ptr<AssetFolder> m_rootFolder;

        /// <summary>
        /// Given game package.
        /// </summary>
        std::weak_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// Given texture manager.
        /// </summary>
        std::weak_ptr<SuperGameEngine::TextureManager> m_textureManager;
    };
}
