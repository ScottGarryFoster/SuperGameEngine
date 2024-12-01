#pragma once
#include "../Graphics/Texture/SuperTexture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Creates, stores and manages all textures in the engine.
    /// </summary>
    class TextureManager
    {
    public:
        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path relative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        virtual std::shared_ptr<SuperTexture> GetTexture(const std::string& filePath) = 0;
    };

}
