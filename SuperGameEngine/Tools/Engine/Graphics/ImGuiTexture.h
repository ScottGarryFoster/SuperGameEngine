#pragma once
#include "../../../Engine/Engine/Graphics/Texture/Texture.h"
#include "../../ImGuiIncludes.h"

using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// A Texture used to display in ImGui.
    /// </summary>
    class ImGuiTexture : public Texture
    {
    public:
        ImGuiTexture(const std::shared_ptr<SDLRendererReader>& renderer);
        virtual ~ImGuiTexture() override = default;

        /// <summary>
        /// Gets the Texture ID for the texture this
        /// represents.
        /// </summary>
        /// <param name="textureID">ImGui Texture ID. </param>
        /// <returns>True means texture could be rendered. </returns>
        bool GetTextureID(ImTextureID& textureID) const;
    };

}

