#pragma once
#include <memory>

namespace SuperGameEngine
{
    class PureSuperTextureWrapper;
    class PureTexture;

    /// <summary>
    /// Creates texture wrappers.
    /// </summary>
    class TextureWrapperFactory
    {
    public:

        /// <summary>
        /// Creates a texture wrapper asset.
        /// </summary>
        /// <param name="texture">A raw texture renderer. </param>
        /// <returns>A created super texture wrapper. </returns>
        virtual std::shared_ptr<PureSuperTextureWrapper> Create(const std::shared_ptr<PureTexture>& texture) const = 0;
    };
}
