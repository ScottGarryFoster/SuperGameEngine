#include "SuperTextureManager.h"
#include "../../FatedQuestReferences.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperTextureManager::SuperTextureManager(
    const std::shared_ptr<SDLRendererReader>& renderer,
    const std::shared_ptr<GamePackage>& gamePackage)
{
    m_renderer = renderer;
    m_storedTextures = std::make_shared<std::unordered_map<std::string, std::shared_ptr<SuperTextureWrapper>>>();
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
