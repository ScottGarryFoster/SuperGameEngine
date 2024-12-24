#pragma once
#include <memory>
#include <string>

#include "../../../Engine/Engine/Content/SuperTextureManager.h"

namespace SuperGameEngine
{
    class SuperTexture;
}

using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ImGuiSuperTextureWrapper;
    class ImGuiTexture;

    class ImGuiTextureManager : public SuperTextureManager
    {
    public:
        explicit ImGuiTextureManager(
            const std::shared_ptr<SDLRendererReader>& renderer,
            const std::shared_ptr<GamePackage>& gamePackage);
        virtual ~ImGuiTextureManager() override = default;

        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path relative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        virtual std::shared_ptr<SuperTexture> GetTexture(const std::string& filePath) override;

    private:

        /// <summary>
        /// All textures stored as filepath names and pointers to the wrappers.
        /// </summary>
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<ImGuiSuperTextureWrapper>>> m_storedTextures;

        /// <summary>
        /// Adds a texture to the cache.
        /// </summary>
        /// <param name="path">Path of the Texture. </param>
        /// <param name="texture">Texture. </param>
        /// <returns>A Super Texture. </returns>
        std::shared_ptr<ImGuiSuperTextureWrapper> AddTextureToStore(
            const std::string& path,
            const std::shared_ptr<ImGuiTexture>& texture) const;
    };
}
