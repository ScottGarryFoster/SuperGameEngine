#include "ContentManager.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/Graphics/SuperTexture.h"
#include "../Basic/FilesAndFolders.h"
#include "../Loaders/Specific/UserInterface/Text/FontFaceLoader.h"
#include "../../UserInterface/Text/FontFace.h"

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
    m_textureLibrary = std::vector<std::shared_ptr<TextureWrapper>>();
    m_productsDirectory = FString(FilesAndFolders::GetProductsFolder());

    this->fontLoader = std::make_unique<FontFaceLoader>(this);
    this->fontFaceCache = std::make_unique<FList<std::pair<FString, std::shared_ptr<FontFaceAsset>>>>();
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
    std::shared_ptr<TextureWrapper> returnTexture = nullptr;
    for (std::shared_ptr<TextureWrapper>& texture : m_textureLibrary)
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
            returnTexture = std::make_shared<TextureWrapper>(newTexture);
            m_textureLibrary.push_back(returnTexture);
        }
    }

    return returnTexture;
}

std::shared_ptr<FontFaceAsset> ContentManager::GetFontFace(
    FString filePath,
    std::shared_ptr<bool>& didCreate)
{
    filePath.ConvertToLower();

    bool loaded = false;
    std::shared_ptr<FontFaceAsset> discoveredFontAsset;
    for (std::pair<FString, std::shared_ptr<FontFaceAsset>> entry: *this->fontFaceCache)
    {
        if (filePath == entry.first)
        {
            discoveredFontAsset = entry.second;
            loaded = true;
            break;
        }
    }

    if (!loaded)
    {
        std::shared_ptr<FontFace> fontFace = 
            std::make_shared<FontFace>(GetEmptySuperTexture());
        std::shared_ptr<Object> object = dynamic_pointer_cast<Object>(fontFace);
        if (!object)
        {
            Logger::Error(FString("ContentManager::GetFontFace: Object does not inherit fron Font"));
        }

        filePath = m_productsDirectory + "\\" + filePath;
        loaded = this->fontLoader->LoadAsset(object, filePath);
        discoveredFontAsset = dynamic_pointer_cast<FontFaceAsset>(object);
    }
    *didCreate = loaded;

    return discoveredFontAsset;
}

Texture* ContentManager::GetEmptyTexture()
{
    return new Texture(m_renderer);
}

std::shared_ptr<SuperTexture> ContentManager::GetEmptySuperTexture()
{
    return std::make_shared<TextureWrapper>(GetEmptyTexture());
}