#include "ImGuiTexture.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ImGuiTexture::ImGuiTexture(const std::shared_ptr<SDLRendererReader>& renderer)
    : Texture(renderer)
{
    m_textureID = -1;
}

ImGuiTexture::~ImGuiTexture()
{
    m_textureID = -1;
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

    textureID = m_textureID;
    return !m_noTextureID;
}

bool ImGuiTexture::LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors)
{
    bool didLoad = Texture::LoadImageFromFile(filePath, errors);
    if (didLoad)
    {
        m_textureID = reinterpret_cast<ImTextureID>(m_texture);
        m_noTextureID = false;
    }
    else
    {
        m_textureID = -1;
        m_noTextureID = true;
    }

    return didLoad;
}

bool ImGuiTexture::LoadImageFromData(
    std::vector<unsigned char>& data, 
    const std::string& filepath,
    std::vector<std::string>& errors)
{
    bool didLoad = Texture::LoadImageFromData(data, filepath, errors);
    if (didLoad)
    {
        m_textureID = reinterpret_cast<ImTextureID>(m_texture);
        m_noTextureID = false;
    }
    else
    {
        m_textureID = -1;
        m_noTextureID = true;
    }

    return didLoad;
}
