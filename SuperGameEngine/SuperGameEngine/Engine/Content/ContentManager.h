#pragma once
#include "../Graphics/SuperTexture.h"
#include "../../LibraryIncludes.h"
#include <vector>
#include <SDL.h>
#include "../Graphics/TextureWrapper.h"
#include "../Loaders/AssetLoader.h"
#include "../../UserInterface/Text/FontFaceAsset.h"

using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class SuperGameEngine_UserInterface::FontFaceAsset;

    /// <summary>
    /// Manages the data (content) in the game meaning game elements do not need to continually
    /// create and delete resources causing spikes in memory.
    /// </summary>
    class ContentManager : public Object
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

        /// <summary>
        /// Loads (creates object wise) or gets a previously loaded font asset of the given
        /// source.
        /// </summary>
        /// <param name="filePath">File path to the Asset Meta File. </param>
        /// <param name="didCreate">
        /// True means created and returned.
        /// False means something went wrong, this could be file related or parsing the file.
        /// </param>
        /// <returns>
        /// If loaded successfully this is the FontFaceAsset.
        /// </returns>
        std::shared_ptr<SuperGameEngine_UserInterface::FontFaceAsset> GetFontFace(
            FString filePath,
            std::shared_ptr<bool>& didCreate);

    private:
        /// <summary>
        /// Allows us to render to the screen.
        /// </summary>
        SDL_Renderer* m_renderer;

        /// <summary>
        /// All the textures currently loaded.
        /// </summary>
        std::vector<std::shared_ptr<TextureWrapper>> m_textureLibrary;

        /// <summary>
        /// The directory products are stored.
        /// </summary>
        FString m_productsDirectory;

        /// <summary>
        /// Loads font faces from Meta files.
        /// </summary>
        std::unique_ptr<AssetLoader> fontLoader;

        /// <summary>
        /// All of the Fonts currently loaded.
        /// </summary>
        std::unique_ptr<FList
            <std::pair<FString, std::shared_ptr
                <SuperGameEngine_UserInterface::FontFaceAsset>>>> 
                    fontFaceCache;

        /// <summary>
        /// Creates an Empty Texture.
        /// </summary>
        /// <return>Empty texture. </return>
        Texture* GetEmptyTexture();

        /// <summary>
        /// Create Empty Super Texture.
        /// </summary>
        /// <returns>Empty super texture with no image. </returns>
        std::shared_ptr<SuperTexture> GetEmptySuperTexture();
    };
}