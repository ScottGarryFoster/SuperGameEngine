#pragma once
#include <memory>

namespace SuperGameEngine
{
    class TextureFactory;
    class TextureAssetFactory;
    class TextureWrapperFactory;

    /// <summary>
    /// All the factories to create content.
    /// </summary>
    struct ContentFactories
    {
    public:

        /// <summary>
        /// Creates raw textures.
        /// </summary>
        std::shared_ptr<TextureFactory> TextureFactory;

        /// <summary>
        /// Creates texture assets.
        /// </summary>
        std::shared_ptr<TextureAssetFactory> TextureAssetFactory;

        /// <summary>
        /// Creates texture wrappers.
        /// </summary>
        std::shared_ptr<TextureWrapperFactory> TextureWrapperFactory;
    };
}
