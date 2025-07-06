#pragma once
#include "AssetFolder.h"
#include "../../../../../FatedQuest.Libraries/StandardObjects/Structural/DistributeWeakPointers.h"

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
    /// Implementation of <see cref="AssetFolder"/>
    /// </summary>
    class ToolsAssetFolder : public AssetFolder, public FatedQuestLibraries::DistributeWeakPointers<ToolsAssetFolder>
    {
    public:

        ToolsAssetFolder(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath);

        /// <summary>
        /// Get the files which are directly contained within this folder.
        /// </summary>
        /// <returns>Get all the asset files directly within this folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFile>> GetContainingFiles() const override;

        /// <summary>
        /// Get the folders which are directly contained within this folder.
        /// </summary>
        /// <returns>Get all the asset folders directly within this folder. </returns>
        virtual std::vector<std::shared_ptr<AssetFolder>> GetContainingFolders() const override;

        /// <summary>
        /// Get the name of the folder to display in the asset browser.
        /// </summary>
        /// <returns>The name of the folder to display. </returns>
        virtual std::string GetDisplayName() const override;

        /// <summary>
        /// Get the package path of the given directory.
        /// </summary>
        /// <returns>Get the path to this directory relative to the package. </returns>
        virtual std::string GetPackagePath() const override;

    private:
        /// <summary>
        /// Given game package.
        /// </summary>
        std::weak_ptr<FatedQuestLibraries::GamePackage> m_gamePackage;

        /// <summary>
        /// Given texture manager.
        /// </summary>
        std::weak_ptr<SuperGameEngine::TextureManager> m_textureManager;

        /// <summary>
        /// My location.
        /// </summary>
        std::string m_packagePath;

        /// <summary>
        /// The name of this directory;
        /// </summary>
        std::string m_directoryName;

        /// <summary>
        /// Files directly in this folder.
        /// </summary>
        std::vector<std::shared_ptr<AssetFile>> m_files;

        /// <summary>
        /// Folders directly in this folder.
        /// </summary>
        std::vector<std::shared_ptr<AssetFolder>> m_folders;
    };
}
