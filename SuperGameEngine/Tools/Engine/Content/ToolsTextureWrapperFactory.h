#pragma once
#include "Engine/Content/TextureWrapperFactory.h"

namespace SuperGameTools
{
    /// <summary>
    /// Creates texture wrappers for the tools to create 
    /// </summary>
    class ToolsTextureWrapperFactory : public virtual SuperGameEngine::TextureWrapperFactory
    {
    public:

        /// <summary>
        /// Creates a texture wrapper asset.
        /// </summary>
        /// <param name="texture">A raw texture renderer. </param>
        /// <returns>A created super texture wrapper. </returns>
        virtual std::shared_ptr<SuperGameEngine::PureSuperTextureWrapper> Create(const std::shared_ptr<SuperGameEngine::PureTexture>& texture) const override;
    };
}
