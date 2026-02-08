#pragma once
#include "TextureWrapperFactory.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Creates texture wrappers for the engine rendered textures.
    /// </summary>
    class SuperTextureWrapperFactory : public virtual TextureWrapperFactory
    {
    public:

        /// <summary>
        /// Creates a texture wrapper asset.
        /// </summary>
        /// <param name="texture">A raw texture renderer. </param>
        /// <returns>A created super texture wrapper. </returns>
        virtual std::shared_ptr<PureSuperTextureWrapper> Create(const std::shared_ptr<PureTexture>& texture) const override;
    };
}
