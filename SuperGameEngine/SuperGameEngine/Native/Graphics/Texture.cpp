#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "Texture::Texture: ", "renderer is null.");
        Logger::Error(error);
    }

    m_renderer = renderer;
    m_texture = nullptr;
}

/// <summary>
/// Loads the given Texture into this class from the File Path.
/// </summary>
/// <param name="filePath">File path to the texture. </param>
/// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
/// <returns>True means created, false means not. </returns>
bool Texture::LoadImageFromFile(FString filePath, std::vector<FString>& errors)
{
    errors.clear();
    if (!File::Exists(filePath))
    {
        FString error = FString("File not found: ") + filePath;
        Logger::Error(error);
        errors.push_back(error);
        return false;
    }

    // Load image
    SDL_Surface* surface = IMG_Load(filePath.AsCharArr());
    if (surface == nullptr)
    {
        FString error = FString("Unable to load image! SDL_Error: ", IMG_GetError());
        Logger::Error(error);
        errors.push_back(error);
        return false;
    }

    // Create texture
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    // Free surface as it's no longer needed
    SDL_FreeSurface(surface);
    surface = NULL;
    if (!m_texture)
    {
        FString error = FString("Error creating texture: ", SDL_GetError());
        Logger::Error(error);
        errors.push_back(error);
        return false;
    }

    return true;
}

/// <summary>
/// Draws to screen.
/// </summary>
void Texture::Draw()
{
    if (m_renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "Texture::Draw(): ", "m_renderer is null.");
        Logger::Error(error);
        return;
    }

    if (m_renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "Texture::Draw(): ", "m_texture is null.");
        Logger::Error(error);
        return;
    }


    SDL_Rect dest;

    // Render texture
    dest.x = 240;
    dest.y = 180;
    dest.w = 160;
    dest.h = 120;

    double rotation = 0;
    SDL_RenderCopyEx(m_renderer, m_texture, NULL, &dest, rotation, NULL, SDL_FLIP_NONE);
}