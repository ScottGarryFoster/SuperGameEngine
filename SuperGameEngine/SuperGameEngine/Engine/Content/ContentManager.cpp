#include "ContentManager.h"
#include "../../Engine/Graphics/Texture.h"
#include "../Basic/FilesAndFolders.h"

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
    m_textureLibrary = std::vector<std::shared_ptr<SuperTexture>>();
    m_productsDirectory = FString(FilesAndFolders::GetProductsFolder());
}

ContentManager::~ContentManager()
{

}

/// <summary>
/// Creates or gets the given Texture.
/// </summary>
/// <param name="filePath">File Path releative to the products folder. </param>
/// <returns>The texture or <c>nullptr</c> if not found. </returns>
std::shared_ptr<SuperTexture> ContentManager::GetTexture(FString filePath)
{
    if (m_renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "ContentManager::GetTexture: ", "renderer is null.");
        Logger::Error(error);
        return nullptr;
    }

    filePath.ConvertToLower();
    filePath = m_productsDirectory + "\\" + filePath;

    bool foundTexture = false;
    std::shared_ptr<SuperTexture> returnTexture = nullptr;
    for (std::shared_ptr<SuperTexture>& texture : m_textureLibrary)
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
        Texture* newTexture = new Texture(m_renderer);
        std::vector<FString> errors = std::vector<FString>();
        if (newTexture->LoadImageFromFile(filePath, errors))
        {
            returnTexture = std::make_shared<SuperTexture>(newTexture);
            m_textureLibrary.push_back(returnTexture);
        }
    }

    return returnTexture;
}