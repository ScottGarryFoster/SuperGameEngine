#include "SuperTexture.h"
#include "Texture.h"

using namespace SuperGameEngine;

SuperTexture::SuperTexture(Texture* texture)
{
    m_actualTexture = texture;
}

SuperTexture::~SuperTexture()
{
    delete m_actualTexture;
}

void SuperTexture::Draw()
{
    m_actualTexture->Draw();
}

void SuperTexture::Draw(const FPoint& location)
{
    m_actualTexture->Draw(location);
}

void SuperTexture::Draw(FPoint location, FPoint size)
{
    m_actualTexture->Draw(location, size);
}

/// <summary>
/// Detirmines if the two textures are the same image.
/// </summary>
/// <param name="texture">Texture to test. </param>
/// <returns>True means are the same. </returns>
bool SuperTexture::RepresentSameImage(SuperTexture* texture)
{
    if (texture == nullptr)
    {
        return false;
    }

    if (texture->m_actualTexture == nullptr)
    {
        return false;
    }

    if (m_actualTexture == nullptr)
    {
        return false;
    }

    FString other = texture->m_actualTexture->GetLoadedFilePath().ToLower();
    FString self = m_actualTexture->GetLoadedFilePath().ToLower();

    return self == other;
}

/// <summary>
/// Determines if the texture uses this file path.
/// </summary>
/// <param name="filePath">File path to text. </param>
/// <returns>True means this uses the same file path. </returns>
bool SuperTexture::RepresentSameImage(FString filePath)
{
    if (m_actualTexture == nullptr)
    {
        return false;
    }

    FString self = m_actualTexture->GetLoadedFilePath().ToLower();
    return self == filePath;
}

FPoint SuperGameEngine::SuperTexture::Size() const
{
    return m_actualTexture->Size();
}
