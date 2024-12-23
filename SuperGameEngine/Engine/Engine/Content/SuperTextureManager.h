#pragma once
#include <unordered_map>

#include "TextureManager.h"
#include "../Graphics/Texture/SDLRendererReader.h"
#include "../Graphics/Texture/SuperTextureWrapper.h"

namespace FatedQuestLibraries
{
    class GamePackage;
}

namespace SuperGameEngine
{
    /// <summary>
    /// Creates, stores and manages all textures in the engine.
    /// </summary>
    class SuperTextureManager : public TextureManager
    {
    public:
        explicit SuperTextureManager(
            const std::shared_ptr<SDLRendererReader>& renderer,
            const std::shared_ptr<GamePackage>& gamePackage);
        virtual ~SuperTextureManager() override;

        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path relative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        virtual std::shared_ptr<SuperTexture> GetTexture(const std::string& filePath) override;

        /// <summary>
        /// Remakes all textures the manager holds.
        /// Used after the window has just been destroyed.
        /// Will stop after a single error.
        /// </summary>
        /// <param name="errors">Any errors which occured after remaking textures. </param>
        /// <returns>True means there were not errors. </returns>
        virtual bool RemakeAllTextures(std::vector<std::string>& errors);
    private:
        /// <summary>
        /// Wraps the SDL Renderer such that upon the death of the
        /// SDL Window this becomes invalid and the textures wait for a
        /// new texture.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;

        /// <summary>
        /// All textures stored as filepath names and pointers to the wrappers.
        /// </summary>
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<SuperTextureWrapper>>> m_storedTextures;

        /// <summary>
        /// Gives us access to all the files the game cares about as these are 'on file'.
        /// </summary>
        std::shared_ptr<GamePackage> m_gamePackage;

        std::shared_ptr<SuperTextureWrapper> AddTextureToStore(const std::string& path, const std::shared_ptr<Texture>& texture) const;
    };

}
