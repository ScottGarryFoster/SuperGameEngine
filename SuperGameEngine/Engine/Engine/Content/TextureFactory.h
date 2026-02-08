#pragma once
#include <memory>

namespace SuperGameEngine
{
    class PureTexture;
    class SDLRendererReader;

    /// <summary>
    /// Creates texture.
    /// </summary>
    class TextureFactory
    {
    public:

        /// <summary>
        /// Creates the lowest texture wrapper.
        /// </summary>
        /// <param name="renderer">The renderer to add the texture to. </param>
        /// <returns>A SDL texture. </returns>
        virtual std::shared_ptr<PureTexture> Create(const std::shared_ptr<SDLRendererReader>& renderer) const = 0;
    };
}
