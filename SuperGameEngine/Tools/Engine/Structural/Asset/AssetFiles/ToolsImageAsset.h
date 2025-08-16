#pragma once
#include "ImageAsset.h"
#include "Windows/AssetBrowser/FileManagement/ToolsAssetFile.h"

namespace SuperGameTools
{
    /// <summary>
    /// An Asset File which represents a texture directly commonly a PNG file.
    /// </summary>
    class ToolsImageAsset : public virtual ImageAsset, public ToolsAssetFile
    {
    public:
        ToolsImageAsset(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent);

        ToolsImageAsset(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent,
            const std::shared_ptr<const AssetMetaData>& assetMetaData);

    private:

        /// <summary>
        /// Sets up the image asset.
        /// Used in the constructor.
        /// </summary>
        void Setup(
            const std::weak_ptr<FatedQuestLibraries::GamePackage>& package,
            const std::weak_ptr<SuperGameEngine::TextureManager>& texture,
            const std::string& packagePath,
            const std::weak_ptr<AssetFolder>& parent);
    };
}
