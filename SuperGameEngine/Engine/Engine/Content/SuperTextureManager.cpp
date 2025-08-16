#include "SuperTextureManager.h"
#include "../../FatedQuestReferences.h"
#include "../../Structural/Assets/Texture/SuperTextureAsset.h"
#include "../../FatedQuest.Libraries/XmlDocument/AllReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTextureManager::SuperTextureManager(
    const std::shared_ptr<SDLRendererReader>& renderer,
    const std::shared_ptr<GamePackage>& gamePackage)
{
    m_renderer = renderer;
    m_storedTextures = std::make_shared<std::unordered_map<std::string, std::shared_ptr<SuperTextureWrapper>>>();
    m_storedTextureAssets = std::make_shared<std::unordered_map<std::string, std::shared_ptr<SuperTextureAsset>>>();
    m_gamePackage = gamePackage;
}

SuperTextureManager::~SuperTextureManager() = default;

std::shared_ptr<SuperTexture> SuperTextureManager::GetTexture(const std::string& filePath)
{
    if (!m_renderer)
    {
        Log::Error("Requested texture but renderer was not given.", "SuperTextureManager::GetTexture");
        return nullptr;
    }

    if (m_renderer->RendererState() != SDLRendererState::Active)
    {
        Log::Error("Requested texture but renderer was destroyed.", "SuperTextureManager::GetTexture");
        return nullptr;
    }

    std::string path = File::Sanitize(filePath);

    // Attempt to find the texture already created.
    auto it = m_storedTextures->find(path);
    if (it != m_storedTextures->end())
    {
        return it->second;
    }

    if (m_gamePackage->File()->Exists(path))
    {
        std::vector<unsigned char> fileData = m_gamePackage->File()->ReadFileContentsExplicitly(path);
        if (fileData.empty())
        {
            Log::Error("Attempted to ReadFileContentsExplicitly and got nothing. File: " + path, "SuperTextureManager::GetTexture");
            return nullptr;
        }

        std::vector<std::string> errors;
        auto texture = std::make_shared<Texture>(m_renderer);
        if (texture->LoadImageFromData(fileData, path, errors))
        {
            return AddTextureToStore(path, texture);
        }
        else
        {
            std::string errorsAsLine = StringHelpers::Join("\n", errors);
            Log::Error("Attempted to load texture from data and failed. \n" + errorsAsLine, "SuperTextureManager::GetTexture");
            return nullptr;
        }
    }

    return nullptr;
}

std::shared_ptr<TextureAsset> SuperTextureManager::GetTextureAsset(const std::string& filepath)
{
    if (GetWeakDistributed().lock() == nullptr)
    {
        Log::Error("No weak pointer provided for Super Texture Manager.",
            "SuperTextureManager::GetTextureAsset(const std::string&)");
        return nullptr;
    }

    // Clean the path such that there is no asset or binary suffix.
    std::string path = File::Sanitize(filepath);
    for (int i = 0; i < 2; ++i)
    {
        std::string extension = File::GetExtension(filepath);
        if (extension == m_assetExtension || extension == m_binaryExtension)
        {
            path = File::RemoveLastExtension(path);
        }
    }

    // Attempt to find the texture asset already created.
    auto it = m_storedTextureAssets->find(path);
    if (it != m_storedTextureAssets->end())
    {
        return it->second;
    }

    // Firstly we need the actual texture to exist.
    if (GetTexture(filepath) == nullptr)
    {
        Log::Error("Could not make texture asset because the texture could not be found.", 
            "SuperTextureManager::GetTextureAsset(const std::string&)");
        return nullptr;
    }

    std::string appendedAsset = filepath + m_assetExtension;
    if (m_gamePackage->File()->Exists(appendedAsset))
    {
        std::string fileData = m_gamePackage->File()->ReadFileContents(appendedAsset);
        if (fileData.empty())
        {
            Log::Error("Attempted to ReadFileContents and got nothing. File: " + appendedAsset, 
                "SuperTextureManager::GetTextureAsset(const std::string&)");
            return nullptr;
        }

        std::shared_ptr<StoredDocument> document = std::make_shared<RapidXMLDocument>();
        if (!document->Load(fileData))
        {
            Log::Error("Could not load the XML for the texture asset. File: " + appendedAsset,
                "SuperTextureManager::GetTextureAsset(const std::string&)");
            return nullptr;
        }

        std::shared_ptr<SuperTextureAsset> textureAsset = AddTextureAssetsToStore(filepath, document);
        if (textureAsset == nullptr)
        {
            Log::Error("Could not create new Super Texture Asset. File: " + appendedAsset,
                "SuperTextureManager::GetTextureAsset(const std::string&)");
            return nullptr;
        }

        return textureAsset;
    }

    std::string appendedBinary = appendedAsset + m_binaryExtension;
    if (m_gamePackage->File()->Exists(appendedBinary))
    {

    }

    return {};
}

bool SuperTextureManager::RemakeAllTextures(std::vector<std::string>& errors)
{
    for (auto it = m_storedTextures->begin(); it != m_storedTextures->end(); ++it)
    {
        if (!it->second->Remake(errors))
        {
            return false;
        }
    }

    return true;
}

std::shared_ptr<SuperTextureWrapper> SuperTextureManager::AddTextureToStore(
    const std::string& path, const std::shared_ptr<Texture>& texture) const
{
    auto textureWrapper = std::make_shared<SuperTextureWrapper>(texture);
    m_storedTextures->insert_or_assign(path, textureWrapper);
    return textureWrapper;
}

std::shared_ptr<SuperTextureAsset> SuperTextureManager::AddTextureAssetsToStore(
    const std::string& path,
    const std::shared_ptr<StoredDocument> document) const
{
    auto textureWrapper = std::make_shared<SuperTextureAsset>(document, path, GetWeakDistributed());
    m_storedTextureAssets->insert_or_assign(path, textureWrapper);
    return textureWrapper;
}
