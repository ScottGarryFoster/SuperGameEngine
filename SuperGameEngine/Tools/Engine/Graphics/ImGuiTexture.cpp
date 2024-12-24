#include "ImGuiTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ImGuiTexture::ImGuiTexture(const std::shared_ptr<SDLRendererReader>& renderer)
    : Texture(renderer)
{
}

bool ImGuiTexture::GetTextureID(ImTextureID& textureID) const
{
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        textureID = -1;
        return false;
    }

    if (m_texture == nullptr)
    {
        textureID = -1;
        return false;
    }

    textureID = reinterpret_cast<ImTextureID>(static_cast<void*>(m_texture));
    return true;
}
