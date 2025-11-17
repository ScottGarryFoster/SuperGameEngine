#pragma once
#include "AssetFolder.h"
#include "../../../../../FatedQuest.Libraries/StandardObjects/Structural/DistributeWeakPointers.h"
#include "Engine/Structural/Asset/AssetFiles/AssetFileType.h"

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
    class AssetMetaData;
    class AssetTemplateProvider;

    /// <summary>
    /// Implementation of <see cref="AssetFolder"/>
    /// </summary>
    class ToolsAssetFolder : public AssetFolder, public std::enable_shared_from_this<ToolsAssetFolder>
    {
    public:

        ToolsAssetFolder(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::shared_ptr<AssetTemplateProvider>& assetTemplateProvider,
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

        /// <summary>
        /// Gets the parent folder.
        /// </summary>
        /// <returns>The parent of the given folder. </returns>
        virtual std::weak_ptr<AssetFolder> GetParent() const override;

        void PopulateChildren(const std::weak_ptr<AssetFolder>& parent);

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

        /// <summary>
        /// The folder above this one (the parent).
        /// </summary>
        std::weak_ptr<AssetFolder> m_parent;

        /// <summary>
        /// Loads, holds and provides <see cref="AssetMetaData"/> in a single location.
        /// </summary>
        std::shared_ptr<AssetTemplateProvider> m_assetTemplateProvider;

        /// <summary>
        /// Creates an asset file in the correct format.
        /// </summary>
        /// <param name="packagePath">Path to the ast. </param>
        /// <returns>The created asset file. </returns>
        std::shared_ptr<AssetFile> CreateAssetFile(const std::string& packagePath);

        /// <summary>
        /// Creates an asset file in the correct format.
        /// </summary>
        /// <param name="packagePath">Path to the ast. </param>
        /// <param name="metaData">The metadata for the asset file.</param>
        /// <returns>The created asset file. </returns>
        std::shared_ptr<AssetFile> CreateAssetFile(const std::string& packagePath, const std::shared_ptr<const AssetMetaData>& metaData);
    };
}
