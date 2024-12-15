#include "Texture.h"
#include "../../../FatedQuestReferences.h"
#include <string>
#include <SDL_image.h>

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

Texture::Texture(const std::shared_ptr<SDLRendererReader>& renderer)
{
    m_sdlRenderer = renderer;
    m_texture = nullptr;
    m_textureSize = std::make_shared<FPoint>();
    m_screenRect = std::make_shared <SDL_Rect>();
    m_textureRect = std::make_shared <SDL_Rect>();
}

Texture::~Texture()
{
    // Create texture
    // Keep in mind that texture here should only be trusted as long as the
    // renderer exists however we only render anyway with an active renderer
    // so this should not be an issue.
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
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
    UpdateTextureMetaData(m_texture);

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

    // Render texture
    m_screenRect->x = 0;
    m_screenRect->y = 0;
    m_screenRect->w = m_textureSize->GetX();
    m_screenRect->h = m_textureSize->GetY();

    double rotation = 0;
    SDL_RenderCopyEx(m_sdlRenderer->GetRenderer(), m_texture, NULL, m_screenRect.get(), rotation, NULL, SDL_FLIP_NONE);
}

void Texture::Draw(const FPoint& location) const
{
    Draw(location, *m_textureSize);
}

void Texture::Draw(const FPoint& location, const FPoint& size) const
{
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        // TODO: ADD Logger for this error.
        return;
    }

    if (!m_texture)
    {
        // TODO: ADD Logger for this error.
        return;
    }

    // Screen Texture
    m_screenRect->x = location.GetX();
    m_screenRect->y = location.GetY();
    m_screenRect->w = size.GetX();
    m_screenRect->h = size.GetY();

    double rotation = 0;
    SDL_RenderCopyEx(m_sdlRenderer->GetRenderer(), m_texture, NULL, m_screenRect.get(), rotation, NULL, SDL_FLIP_NONE);
}

void Texture::Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const
{
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        // TODO: ADD Logger for this error.
        return;
    }

    if (!m_texture)
    {
        // TODO: ADD Logger for this error.
        return;
    }

    // Screen Texture
    m_screenRect->x = screenRectangle.GetLeft();
    m_screenRect->y = screenRectangle.GetTop();
    m_screenRect->w = screenRectangle.GetWidth();
    m_screenRect->h = screenRectangle.GetHeight();

    // Texture Area
    m_textureRect->x = textureRectangle.GetLeft();
    m_textureRect->y = textureRectangle.GetTop();
    m_textureRect->w = textureRectangle.GetWidth();
    m_textureRect->h = textureRectangle.GetHeight();

    double rotation = 0;
    SDL_RenderCopyEx(m_sdlRenderer->GetRenderer(), m_texture, m_textureRect.get(), m_screenRect.get(), rotation, NULL, SDL_FLIP_NONE);
}

std::string SuperGameEngine::Texture::GetLoadedFilePath() const
{
    return m_filePath;
}

FPoint Texture::Size() const
{
    return *m_textureSize;
}

bool Texture::Remake(std::vector<std::string>& errors)
{
    return LoadImageFromFile(m_filePath, errors);
}

void Texture::UpdateTextureMetaData(SDL_Texture* texture) const
{
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    m_textureSize->SetXYValue(textureWidth, textureHeight);
}