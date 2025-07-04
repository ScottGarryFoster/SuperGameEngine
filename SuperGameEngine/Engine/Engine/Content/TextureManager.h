#pragma once
#include <string>
#include <memory>

namespace SuperGameEngine
{
    class SuperTexture;
    class TextureAsset;

    /// <summary>
    /// Creates, stores and manages all textures in the engine.
    /// </summary>
    class TextureManager
    {
    public:
        virtual ~TextureManager() = default;

        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path relative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        virtual std::shared_ptr<SuperTexture> GetTexture(const std::string& filePath) = 0;

        /// <summary>
        /// Creates or gets the texture asset for the given path.
        /// A texture asset has the ability to predefine more information about the texture.
        /// </summary>
        /// <param name="filepath">Filepath to the texture asset with the asset extension, relative to the products folder. </param>
        /// <returns>The texture asset or empty if not found. </returns>
        virtual std::shared_ptr<TextureAsset> GetTextureAsset(const std::string& filepath) = 0;
    };

}
