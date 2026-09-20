#pragma once
#include "TilesetAsset.h"
#include "Structural/Assets/SuperGameAsset.h"

namespace SuperGameEngine
{
    class TextureManager;

    class SuperTilesetAsset : public virtual TilesetAsset, public SuperGameAsset
    {
    public:
        /// <summary>
        /// Constructor.
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
        /// </param>
        SuperTilesetAsset(
            const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject,
            const std::string& path,
            const std::weak_ptr<TextureManager>& textureManager);
        
        /// <summary>
        /// Gets the textures which can be displayed as standard not moving tiles.
        /// </summary>
        /// <returns>
        /// Textures which can be display as non-moving tiles.
        /// The order should not change.
        /// </returns>
        virtual std::vector<std::shared_ptr<TextureAsset>> GetStandardTextures() const override;
        
    private:
        
        /// <summary>
        /// The standard tiles for the tileset.
        /// </summary>
        std::vector<std::shared_ptr<TextureAsset>> m_textureAssets;
    };
}
