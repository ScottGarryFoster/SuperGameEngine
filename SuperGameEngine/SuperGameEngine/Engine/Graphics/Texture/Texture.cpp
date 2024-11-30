#include "Texture.h"
#include "../../../FatedQuestReferences.h"
#include <string>

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

Texture::Texture(std::shared_ptr<SDLRendererReader> renderer)
{
    m_sdlRenderer = renderer;
    m_texture = nullptr;
}

Texture::~Texture()
{
}

bool Texture::LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors)
{
    errors.clear();
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        std::string error = "Renderer is not active. Window might not exist. Try giving the textures an active renderer.";
        // TODO: ADD Logger for this error.
        errors.push_back(error);
        return false;
    }

    if (!File::Exists(filePath))
    {
        std::string error = "File not found: " + filePath;
        // TODO: ADD Logger for this error.
        errors.push_back(error);
        return false;
    }

    // Load image
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr)
    {
        std::string error = "Unable to load image! SDL_Error: ", IMG_GetError();
        // TODO: ADD Logger for this error.
        errors.push_back(error);
        return false;
    }

    // Create texture
    // Keep in mind that texture here should only be trusted as long as the
    // renderer exists however we only render anyway with an active renderer
    // so this should not be an issue.
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }

    m_texture  = SDL_CreateTextureFromSurface(m_sdlRenderer->GetRenderer(), surface);

    // Free surface as it's no longer needed
    SDL_FreeSurface(surface);
    surface = NULL;
    if (!m_texture)
    {
        std::string error = "Error creating texture: ", SDL_GetError();
        // TODO: ADD Logger for this error.
        errors.push_back(error);
        return false;
    }

    // TODO: Implement this: UpdateTextureMetaData(m_texture);

    m_filePath = filePath;
    return true;
}

bool Texture::LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors)
{
    return false;
}

void Texture::Draw() const
{
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        // TODO: ADD Logger for this error.
        return;
    }

    if (!m_texture)
    {
        // TODO: ADD Logger for this error.;
        return;
    }

    int textureWidth, textureHeight;
    SDL_QueryTexture(m_texture, NULL, NULL, &textureWidth, &textureHeight);

    // Render texture
    SDL_Rect* rect = new SDL_Rect();
    rect->x = 0;
    rect->y = 0;
    rect->w = textureWidth;
    rect->h = textureHeight;

    double rotation = 0;
    SDL_RenderCopyEx(m_sdlRenderer->GetRenderer(), m_texture, NULL, rect, rotation, NULL, SDL_FLIP_NONE);
}

std::string SuperGameEngine::Texture::GetLoadedFilePath()
{
    return m_filePath;
}

bool SuperGameEngine::Texture::Remake(std::vector<std::string>& errors)
{
    return LoadImageFromFile(m_filePath, errors);
}
