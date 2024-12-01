#include "SuperTextureManager.h"

using namespace SuperGameEngine;

SuperTextureManager::SuperTextureManager(const std::shared_ptr<SDLRendererReader>& renderer)
{
    m_renderer = renderer;
    m_storedTextures = std::make_shared<std::unordered_map<std::string, std::shared_ptr<SuperTextureWrapper>>>();
}

SuperTextureManager::~SuperTextureManager() = default;

std::shared_ptr<SuperTexture> SuperTextureManager::GetTexture(const std::string& filePath)
{
    if (!m_renderer)
    {
        //TODO: Log this.
        return nullptr;
    }

    // TODO: Path this from Products folder.
    std::string path = StringHelpers::ToLower(filePath);

    // Attempt to find the texture already created.
    auto it = m_storedTextures->find(path);
    if (it != m_storedTextures->end())
    {
        return it->second;
    }

    if (File::Exists(path))
    {
        std::vector<std::string> errors;
        auto texture = std::make_shared<Texture>(m_renderer);
        if (texture->LoadImageFromFile(path, errors))
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

std::shared_ptr<SuperTextureWrapper> SuperTextureManager::AddTextureToStore(std::string path, std::shared_ptr<Texture> texture)
{
    auto textureWrapper = std::make_shared<SuperTextureWrapper>(texture);
    m_storedTextures->insert_or_assign(path, textureWrapper);
    return textureWrapper;
}