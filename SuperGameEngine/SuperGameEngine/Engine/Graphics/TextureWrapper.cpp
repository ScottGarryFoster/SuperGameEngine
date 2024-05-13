#include "TextureWrapper.h"
#include "Texture.h"

using namespace SuperGameEngine;

TextureWrapper::TextureWrapper(std::shared_ptr<Texture> texture)
{
    m_actualTexture = texture;
}

TextureWrapper::~TextureWrapper()
{
}

void TextureWrapper::Draw()
{
    m_actualTexture->Draw();
}

void TextureWrapper::Draw(const FPoint& location)
{
    m_actualTexture->Draw(location);
}

void TextureWrapper::Draw(const FPoint& location, const FPoint& size)
{
    m_actualTexture->Draw(location, size);
}

void TextureWrapper::Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle)
{
    m_actualTexture->Draw(textureRectangle, screenRectangle);
}

/// <summary>
/// Detirmines if the two textures are the same image.
/// </summary>
/// <param name="texture">Texture to test. </param>
/// <returns>True means are the same. </returns>
bool TextureWrapper::RepresentSameImage(SuperTexture* texture)
{
    if (texture == nullptr)
    {
        return false;
    }

    if (typeid(texture) != typeid(TextureWrapper))
    {
        return false;
    }

    TextureWrapper* textureWrapper = dynamic_cast<TextureWrapper*>(texture);
    if (textureWrapper->m_actualTexture == nullptr)
    {
        return false;
    }

    if (m_actualTexture == nullptr)
    {
        return false;
    }

    FString other = textureWrapper->m_actualTexture->GetLoadedFilePath().ToLower();
    FString self = m_actualTexture->GetLoadedFilePath().ToLower();

    return self == other;
}

/// <summary>
/// Determines if the texture uses this file path.
/// </summary>
/// <param name="filePath">File path to text. </param>
/// <returns>True means this uses the same file path. </returns>
bool TextureWrapper::RepresentSameImage(FString filePath)
{
    if (m_actualTexture == nullptr)
    {
        return false;
    }

    FString self = m_actualTexture->GetLoadedFilePath().ToLower();
    return self == filePath.ToLower();
}

FPoint SuperGameEngine::TextureWrapper::Size() const
{
    return m_actualTexture->Size();
}
