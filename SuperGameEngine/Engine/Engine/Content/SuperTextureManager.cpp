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
        //TODO: Log this.
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
            // TODO: Log this.
#ifdef _DEBUG
            std::cout << "SuperTextureManager::GetTexture: Attempted to ReadFileContentsExplicitly and got nothing. File: " << path << "\n";
#endif

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
            // TODO: Log this.
        }
    }
    else
    {
        // TODO: Add zip loading here.
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
