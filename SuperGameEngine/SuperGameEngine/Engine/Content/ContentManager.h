#pragma once
#include "../Graphics/SuperTexture.h"
#include "../../LibraryIncludes.h"
#include <vector>
#include <SDL.h>

using namespace StandardCLibrary;

namespace SuperGameEngine
{
    /// <summary>
    /// Manages the data (content) in the game meaning game elements do not need to continually
    /// create and delete resources causing spikes in memory.
    /// </summary>
    class ContentManager
    {
    public:
        ContentManager(SDL_Renderer* renderer);
        ~ContentManager();

        /// <summary>
        /// Creates or gets the given Texture.
        /// </summary>
        /// <param name="filePath">File Path releative to the products folder. </param>
        /// <returns>The texture or <c>nullptr</c> if not found. </returns>
        std::shared_ptr<SuperTexture> GetTexture(FString filePath);

    private:
        /// <summary>
        /// Allows us to render to the screen.
        /// </summary>
        SDL_Renderer* m_renderer;

        /// <summary>
        /// All the textures currently loaded.
        /// </summary>
        std::vector<std::shared_ptr<SuperTexture>> m_textureLibrary;

        /// <summary>
        /// The directory products are stored.
        /// </summary>
        FString m_productsDirectory;
    };
}