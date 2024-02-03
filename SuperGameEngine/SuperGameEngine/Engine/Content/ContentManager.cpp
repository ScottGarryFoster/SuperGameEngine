#include "ContentManager.h"


using namespace SuperGameEngine;
using namespace StandardCLibrary;

ContentManager::ContentManager(SDL_Renderer* renderer)
{
    if (renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "ContentManager::ContentManager: ", "renderer is null.");
        Logger::Error(error);
    }

    m_renderer = renderer;
    m_textureLibrary = std::vector<SuperTexture*>();
}

ContentManager::~ContentManager()
{
    for (SuperTexture* texture : m_textureLibrary)
    {
        delete texture;
    }
}

/// <summary>
/// Creates or gets the given Texture.
/// </summary>
/// <param name="filePath">File Path releative to the products folder. </param>
/// <returns>The texture or <c>nullptr</c> if not found. </returns>
SuperTexture* ContentManager::GetTexture(FString filePath)
{
    if (m_renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "ContentManager::GetTexture: ", "renderer is null.");
        Logger::Error(error);
        return nullptr;
    }

    filePath.ConvertToLower();

    bool foundTexture = false;
    SuperTexture* returnTexture = nullptr;
    for (SuperTexture*& texture : m_textureLibrary)
    {
        if (texture->RepresentSameImage(filePath))
        {
            returnTexture = texture;
            foundTexture = true;
            break;
        }
    }

    if (!foundTexture)
    {
        // Make texture

        // Add it to vector.
    }

    return returnTexture;
}