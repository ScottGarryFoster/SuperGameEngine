#pragma once
#include <unordered_map>

#include "Structural/Assets/GameAsset.h"

namespace SuperGameEngine
{
    class TextureAsset;
    
    /// <summary>
    /// Defines a Tileset which is a collection of textures split into tiles with potentially
    /// some inner tilesets acting with special behaviour.
    /// </summary>
    class TilesetAsset : public virtual GameAsset
    {
    public:
        
        /// <summary>
        /// Gets the textures which can be displayed as standard not moving tiles.
        /// </summary>
        /// <returns>
        /// Textures which can be display as non-moving tiles.
        /// The order should not change.
        /// </returns>
        virtual std::vector<std::shared_ptr<TextureAsset>> GetStandardTextures() const = 0;
    };
}
