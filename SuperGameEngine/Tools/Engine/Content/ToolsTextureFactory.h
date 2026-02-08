#pragma once
#include "Engine/Content/TextureFactory.h"

namespace SuperGameTools
{
    /// <summary>
    /// Creates ImGuiTextures.
    /// </summary>
    class ToolsTextureFactory : public virtual SuperGameEngine::TextureFactory
    {
    public:

        /// <summary>
        /// Creates the lowest texture wrapper.
        /// </summary>
        /// <param name="renderer">The renderer to add the texture to. </param>
        /// <returns>A SDL texture. </returns>
        virtual std::shared_ptr<SuperGameEngine::PureTexture> Create(const std::shared_ptr<SuperGameEngine::SDLRendererReader>& renderer) const override;
    };
}
