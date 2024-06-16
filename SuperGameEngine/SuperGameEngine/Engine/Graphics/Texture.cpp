#include "Texture.h"
#include "../../Structural/Spatial/Area/RectangleInt.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

Texture::Texture(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "Texture::Texture: ", "renderer is null.");
        Logger::Error(error);
    }

    m_renderer = renderer;
    m_texture = nullptr;
    m_textureSize = new FPoint();
    m_screenRect = new SDL_Rect();
    m_textureRect = new SDL_Rect();
}

Texture::~Texture()
{
    delete m_textureSize;
    delete m_screenRect;
    delete m_textureRect;
    SDL_DestroyTexture(m_texture);
    delete m_texture;
}

/// <summary>
/// Loads the given Texture into this class from the File Path.
/// </summary>
/// <param name="filePath">File path to the texture. </param>
/// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
/// <returns>True means created, false means not. </returns>
bool Texture::LoadImageFromFile(const FString& filePath, std::vector<FString>& errors)
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

    UpdateTextureMetaData(m_texture);

    m_filePath = filePath;
    return true;
}

bool Texture::LoadImageFromData(const std::vector<unsigned char>& data, const std::string& filepath, std::vector<FString>& errors)
{
    // TODO: IMPLEMENT THIS AS PART OF [#75]
    Logger::Assert(NotImplementedException(), GetTypeName(), FString("LoadFileFromData"),
        FString("Not implemented yet. To be implemented as part of ticket #75. "));
    return false;
}

/// <summary>
/// Draws to screen.
/// </summary>
void Texture::Draw()
{
    Draw(FPoint());
}

void Texture::Draw(const FPoint& location)
{
    Draw(location, *m_textureSize);
}

void Texture::Draw(const FPoint& location, const FPoint& size)
{
    if (m_renderer == nullptr)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Draw"), FString("m_renderer is null."));
        return;
    }

    if (m_renderer == nullptr)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Draw"), FString("m_texture is null."));
        return;
    }


    // Render texture
    m_screenRect->x = location.GetX();
    m_screenRect->y = location.GetY();
    m_screenRect->w = size.GetX();
    m_screenRect->h = size.GetY();

    double rotation = 0;
    SDL_RenderCopyEx(m_renderer, m_texture, NULL, m_screenRect, rotation, NULL, SDL_FLIP_NONE);
}

void Texture::Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle)
{
    if (m_renderer == nullptr)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Draw"), FString("m_renderer is null."));
        return;
    }

    if (m_renderer == nullptr)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Draw"), FString("m_texture is null."));
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
    SDL_RenderCopyEx(m_renderer, m_texture, m_textureRect, m_screenRect, rotation, NULL, SDL_FLIP_NONE);
}

/// <summary>
/// Get the Filepath of the loaded texture.
/// </summary>
/// <returns>The filepath of the texture loaded. </returns>
FString Texture::GetLoadedFilePath()
{
    return m_filePath;
}

FPoint Texture::Size() const
{
    if (m_textureSize == nullptr)
    {
        Logger::Assert(SystemNullReference(), GetTypeName(), FString("Size"), FString("Size is called without a Texture."));
        return FPoint();
    }

    return FPoint(m_textureSize->GetX(), m_textureSize->GetY());
}

void Texture::UpdateTextureMetaData(SDL_Texture* texture)
{
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    m_textureSize->SetXYValue(textureWidth, textureHeight);
}
