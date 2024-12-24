#include "ImGuiTextureManager.h"
#include "../Graphics/ImGuiTexture.h"
#include "../Graphics/ImGuiSuperTextureWrapper.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ImGuiTextureManager::ImGuiTextureManager(
    const std::shared_ptr<SDLRendererReader>& renderer,
    const std::shared_ptr<GamePackage>& gamePackage)
    : SuperTextureManager(renderer, gamePackage)
{
    m_storedTextures = std::make_shared<std::unordered_map<std::string, std::shared_ptr<ImGuiSuperTextureWrapper>>>();
}

std::shared_ptr<SuperTexture> ImGuiTextureManager::GetTexture(const std::string& filePath)
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
            std::cout << "ImGuiTextureManager::GetTexture: Attempted to ReadFileContentsExplicitly and got nothing. File: " << path << "\n";
#endif

            return nullptr;
        }

        std::vector<std::string> errors;
        auto texture = std::make_shared<ImGuiTexture>(m_renderer);
        if (texture->LoadImageFromData(fileData, path, errors))
        {
            return AddTextureToStore(path, texture);
        }
        else
        {
            // TODO: Log this.
        }
    }

    return nullptr;
}

std::shared_ptr<ImGuiSuperTextureWrapper> ImGuiTextureManager::AddTextureToStore(
    const std::string& path,
    const std::shared_ptr<ImGuiTexture>& texture) const
{
    auto textureWrapper = std::make_shared<ImGuiSuperTextureWrapper>(texture);
    m_storedTextures->insert_or_assign(path, textureWrapper);
    return textureWrapper;
}
