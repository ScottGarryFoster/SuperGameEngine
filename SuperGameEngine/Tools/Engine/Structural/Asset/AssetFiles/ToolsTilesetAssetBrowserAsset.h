#pragma once
#include "TilesetAssetBrowserAsset.h"
#include "Panels/AssetBrowser/FileManagement/ToolsAssetFile.h"

namespace SuperGameTools
{
    /// <summary>
    /// Represents a tileset asset in the asset browser.
    /// </summary>
    class ToolsTilesetAssetBrowserAsset : public virtual TilesetAssetBrowserAsset, public ToolsAssetFile
    {
    public:
        ToolsTilesetAssetBrowserAsset(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent);

        ToolsTilesetAssetBrowserAsset(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent,
            const std::shared_ptr<const SingleAssetLayoutMetaData>& assetMetaData);

    private:

        /// <summary>
        /// Sets up the tileset asset.
        /// Used in the constructor.
        /// </summary>
        void Setup(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent);
    };
}
