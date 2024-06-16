#include "ContentManager.h"
#include "../../Engine/Graphics/Texture.h"
#include "../../Engine/Graphics/SuperTexture.h"
#include "../Basic/FilesAndFolders.h"
#include "../Loaders/Specific/UserInterface/Text/FontFaceLoader.h"
#include "../../UserInterface/Text/FontFace.h"
#include "../Graphics/EmptyTexture.hpp"
#include "../../../FatedQuest.Libraries/BinaryOperations/BinaryZip/StandardBinaryZip.h"

#include <string>
#include <algorithm>

using namespace SuperGameEngine;
using namespace StandardCLibrary;
using namespace BinaryOperations;

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

    m_fontLoader = std::make_unique<FontFaceLoader>(this);
    m_fontFaceCache = std::make_unique<FList<std::pair<FString, std::shared_ptr<FontFaceAsset>>>>();
    m_binaryZip = std::make_unique<StandardBinaryZip>();

    LoadArchiveFilesIntoCache();
}

ContentManager::~ContentManager()
{

}

std::shared_ptr<SuperTexture> ContentManager::GetTexture(FString filePath)
{
    if (m_renderer == nullptr)
    {
        FString error = FString("ARGUMENTNULLEXPCETION: ", "ContentManager::GetTexture: ", "renderer is null.");
        Logger::Error(error);
        return nullptr;
    }

    std::string filePathInsideProducts = filePath.AsStdString();
    filePath = m_productsDirectory + "\\" + filePathInsideProducts;
    filePath.ConvertToLower();

    FString filePathZip = m_productsDirectory + ".zip\\" + filePathInsideProducts;
    filePathZip.ConvertToLower();

    std::string binaryFilePathInsideProducts = filePathInsideProducts + ".gz";
    FString binaryFilePathZip = m_productsDirectory + ".zip\\" + binaryFilePathInsideProducts;
    binaryFilePathZip.ConvertToLower();

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
        else if (texture->RepresentSameImage(filePathZip))
        {
            returnTexture = texture;
            foundTexture = true;
            break;
        }
        else if (texture->RepresentSameImage(binaryFilePathInsideProducts))
        {
            returnTexture = texture;
            foundTexture = true;
            break;
        }
    }


    if (!foundTexture)
    {
        std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(m_renderer);
        std::vector<FString> errors = std::vector<FString>();

        if (File::Exists(filePath))
        {
            if (newTexture->LoadImageFromFile(filePath, errors))
            {
                returnTexture = std::make_shared<TextureWrapper>(newTexture);
                m_textureLibrary.push_back(returnTexture);
            }
        }
        else
        {
            // Ensure to use the correct path when loading the texture.
            // This means if another texture is used it will be reloaded.
            FString* zipPathToStore = nullptr;

            std::string fileToLoad = filePathInsideProducts;
            bool shouldLoad = false;
            if (FileIsInArchive(filePathInsideProducts))
            {
                zipPathToStore = &filePathZip;
                shouldLoad = true;
            }
            else if (FileIsInArchive(binaryFilePathInsideProducts))
            {
                zipPathToStore = &binaryFilePathZip;
                fileToLoad = binaryFilePathInsideProducts;
                shouldLoad = true;
            }

            if (shouldLoad)
            {
                std::string zipName = m_productsDirectory.AsStdString() + ".zip";
                std::vector<unsigned char> outputData = std::vector<unsigned char>();
                if (LoadFileFromData(zipName, fileToLoad, outputData, errors))
                {
                    if (newTexture->LoadImageFromData(outputData, zipPathToStore->AsStdString(), errors))
                    {
                        returnTexture = std::make_shared<TextureWrapper>(newTexture);
                        m_textureLibrary.push_back(returnTexture);
                    }
                }
            }
        }
    }

    return returnTexture;
}

std::shared_ptr<FontFaceAsset> ContentManager::GetFontFace(
    FString filePath,
    std::shared_ptr<bool>& didCreate)
{
    std::string filePathInsideProducts = filePath.AsStdString();
    filePath = m_productsDirectory + "\\" + filePathInsideProducts;
    filePath.ConvertToLower();

    FString filePathZip = m_productsDirectory + ".zip\\" + filePathInsideProducts;
    filePathZip.ConvertToLower();

    std::string binaryFilePathInsideProducts = filePathInsideProducts + ".gz";
    FString binaryFilePathZip = m_productsDirectory + ".zip\\" + binaryFilePathInsideProducts;
    binaryFilePathZip.ConvertToLower();

    bool loaded = false;
    std::shared_ptr<FontFaceAsset> discoveredFontAsset;

    for (const std::pair<FString, std::shared_ptr<FontFaceAsset>>& entry : *m_fontFaceCache)
    {
        if (filePath == entry.first)
        {
            discoveredFontAsset = entry.second;
            loaded = true;
            break;
        }
        else if (filePathZip == entry.first)
        {
            discoveredFontAsset = entry.second;
            loaded = true;
            break;
        }
        else if (binaryFilePathZip == entry.first)
        {
            discoveredFontAsset = entry.second;
            loaded = true;
            break;
        }
    }

    if (!loaded)
    {
        std::shared_ptr<FontFace> fontFace = std::make_shared<FontFace>(GetEmptySuperTexture());
        std::shared_ptr<Object> object = dynamic_pointer_cast<Object>(fontFace);
        if (!object)
        {
            Logger::Error(FString("ContentManager::GetFontFace: Object does not inherit fron Font"));
        }

        if (File::Exists(filePath))
        {
            // This is not ideal. There is a decent amount of casting here.
            // Caching will likely save us but we should avoid this.
            loaded = m_fontLoader->LoadAsset(object, filePath);
            discoveredFontAsset = dynamic_pointer_cast<FontFaceAsset>(object);
        }
        else
        {
            std::string fileToLoad = filePathInsideProducts;
            bool shouldLoad = false;
            if (FileIsInArchive(filePathInsideProducts))
            {
                shouldLoad = true;
            }
            else if(FileIsInArchive(binaryFilePathInsideProducts))
            {
                fileToLoad = binaryFilePathInsideProducts;
                shouldLoad = true;
            }

            if (shouldLoad)
            {
                std::string zipName = m_productsDirectory.AsStdString() + ".zip";
                std::string filePathAsString = filePath.AsStdString();
                std::vector<FString> errors;
                std::vector<unsigned char> outputData = std::vector<unsigned char>();
                if (LoadFileFromData(zipName, fileToLoad, outputData, errors))
                {
                    if (m_fontLoader->LoadAssetFromData(object, outputData))
                    {
                        discoveredFontAsset = dynamic_pointer_cast<FontFaceAsset>(object);
                        loaded = true;
                    }
                }
            }
        }

        m_fontFaceCache->Add(std::pair<FString, std::shared_ptr<FontFaceAsset>>(filePath, discoveredFontAsset));
    }
    *didCreate = loaded;

    return discoveredFontAsset;
}

std::shared_ptr<Texture> ContentManager::GetEmptyTexture()
{
    return std::make_shared<Texture>(m_renderer);
}

std::shared_ptr<SuperTexture> ContentManager::GetEmptySuperTexture()
{
    return std::make_shared<EmptyTexture>();
}

void ContentManager::LoadArchiveFilesIntoCache()
{
    std::vector<std::string> loadingZipErrors;
    m_productArchiveFiles = m_binaryZip->ListFilesInArchive(m_productsDirectory.AsStdString() + ".zip", loadingZipErrors);
    for (std::string error : loadingZipErrors)
    {
        Logger::Error("Loading Products Zip error: " + error);
    }

    // Standardise all paths in lookup to forward slashes.
    for (std::string& path : m_productArchiveFiles)
    {
        std::replace(path.begin(), path.end(), '\\', '/');
    }
}

bool ContentManager::LoadFileFromData(
    const std::string zipName,
    const std::string innerFile,
    std::vector<unsigned char>& data,
    std::vector<FString>& errors)
{
    std::vector<std::string> errorsAsString = std::vector<std::string>();

    bool created = false;
    if (File::EndInExtension(innerFile, ".gz"))
    {
        created = m_binaryZip->ExtractSingleBinaryFileToData(zipName, innerFile, data, errorsAsString);
    }
    else
    {
        created = m_binaryZip->ExtractSingleFileToData(zipName, innerFile, data, errorsAsString);
    }

    for (std::string error : errorsAsString)
    {
        errors.push_back(FString(error));
    }

    return created;
}

bool ContentManager::FileIsInArchive(const std::string& filename)
{
    std::string adjustedName = filename;
    std::replace(adjustedName.begin(), adjustedName.end(), '\\', '/');
    return VectorHelpers::ContainsString(m_productArchiveFiles, adjustedName);
}