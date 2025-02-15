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
    m_textureDataOrigin = TextureDataOrigin::Unknown;
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
        errors.push_back(error);
        return false;
    }

    if (!File::Exists(filePath))
    {
        std::string error = "File not found: " + filePath;
        errors.push_back(error);
        return false;
    }

    // Load image
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr)
    {
        std::string error = "Unable to load image! SDL_Error: ", IMG_GetError();
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
        errors.push_back(error);
        return false;
    }

    m_filePath = filePath;
    m_textureData.clear();
    m_textureDataOrigin = TextureDataOrigin::FromFile;

    UpdateTextureMetaData(m_texture);

    return true;
}

bool Texture::LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors)
{
    if (data.empty())
    {
        errors.emplace_back("No data to create texture. ");
        return false;
    }

    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        std::string error = "Renderer is not active. Window might not exist. Try giving the textures an active renderer.";
        errors.push_back(error);
        return false;
    }

    SDL_RWops* rwOps = SDL_RWFromMem(data.data(), data.size());
    if (!rwOps)
    {
        errors.emplace_back("Failed to create RWops from memory.");
        return false;
    }

    SDL_Surface* imageSurface = IMG_Load_RW(rwOps, 1); // 1 means SDL will close the RWops for us
    if (!imageSurface)
    {
        std::string imageError = IMG_GetError();
        errors.emplace_back("Failed to load image from RWops: " + imageError);
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

    // Create texture
    m_texture = SDL_CreateTextureFromSurface(m_sdlRenderer->GetRenderer(), imageSurface);

    // Free surface as it's no longer needed
    SDL_FreeSurface(imageSurface);
    imageSurface = nullptr;
    if (!m_texture)
    {
        std::stringstream ss;
        ss << "Error creating texture: " << SDL_GetError();
        errors.push_back(ss.str());
        return false;
    }

    UpdateTextureMetaData(m_texture);

    m_filePath = filepath;
    m_textureData = data;
    m_textureDataOrigin = TextureDataOrigin::FromData;

    return true;
}

void Texture::Draw() const
{
    if (!ValidateRendererAndTexture("Texture::Draw()"))
    {
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
    if (!ValidateRendererAndTexture("Texture::Draw(const FPoint&, const FPoint&)"))
    {
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
    if (!ValidateRendererAndTexture("Texture::Draw(const RectangleInt&, const RectangleInt&)"))
    {
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

std::string Texture::GetLoadedFilePath() const
{
    return m_filePath;
}

FPoint Texture::Size() const
{
    return *m_textureSize;
}

bool Texture::Remake(std::vector<std::string>& errors)
{
    if (m_textureDataOrigin == TextureDataOrigin::FromData)
    {
        return LoadImageFromData(m_textureData, m_filePath, errors);
    }

    return LoadImageFromFile(m_filePath, errors);
}

void Texture::UpdateTextureMetaData(SDL_Texture* texture) const
{
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    m_textureSize->SetXYValue(textureWidth, textureHeight);
}

bool Texture::ValidateRendererAndTexture(const std::string& methodName) const
{
    if (m_sdlRenderer->RendererState() != SDLRendererState::Active)
    {
        if (m_filePath.empty())
        {
            Log::Error("Attempting to draw texture but there is no renderer. "
                "Filepath (potentially old): " + m_filePath,
                methodName);
        }
        else
        {
            Log::Error("Attempting to draw texture but there is no renderer.", "Texture::Draw");
        }

        return false;
    }

    if (!m_texture)
    {
        if (m_filePath.empty())
        {
            Log::Error("Requested to draw Texture but it does not exist. "
                "Filepath (potentially old): " + m_filePath,
                methodName);
        }
        else
        {
            Log::Error("Requested to draw Texture but it does not exist.", "Texture::Draw");
        }

        return false;
    }

    return true;
}