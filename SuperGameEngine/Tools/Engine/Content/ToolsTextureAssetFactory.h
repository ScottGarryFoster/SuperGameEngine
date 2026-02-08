#pragma once
#include "Engine/Content/TextureAssetFactory.h"

namespace SuperGameTools
{
    /// <summary>
    /// Creates Texture Assets for the Tools.
    /// </summary>
    class ToolsTextureAssetFactory : public virtual SuperGameEngine::TextureAssetFactory
    {
    public:

        /// <summary>
        /// Creates texture assets.
        /// </summary>
        /// <param name="universalObject">
        /// Universal object as a stored document.
        /// </param>
        /// <param name="path">
        /// Path to the file which loaded this actual asset.
        /// </param>
        /// <param name="textureManager">
        /// A method to acquire textures, for SuperTextureAsset we need SuperTextures
        /// as this type wraps that level of texture.
        /// It is best practice to ensure the texture used for the asset already exists
        /// in the texture manager so that you may better handle errors.
        /// </param>
        /// <returns>A created super texture asset. </returns>
        virtual std::shared_ptr<SuperGameEngine::SuperTextureAsset> Create(
            const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject,
            const std::string& path,
            const std::weak_ptr<SuperGameEngine::TextureManager>& textureManager
        ) const override;
    };
}
