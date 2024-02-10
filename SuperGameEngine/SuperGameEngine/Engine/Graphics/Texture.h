#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../../LibraryIncludes.h"

using namespace StandardCLibrary;

namespace SuperGameEngine
{
    /// <summary>
    /// Contains a renderable 2D Texture.
    /// </summary>
    class Texture : public Object
    {
    public:
        Texture(SDL_Renderer* renderer);

        /// <summary>
        /// Loads the given Texture into this class from the File Path.
        /// </summary>
        /// <param name="filePath">File path to the texture. </param>
        /// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
        /// <returns>True means created, false means not. </returns>
        bool LoadImageFromFile(FString filePath, std::vector<FString>& errors);

        /// <summary>
        /// Draws to screen.
        /// </summary>
        void Draw();

        /// <summary>
        /// Get the Filepath of the loaded texture.
        /// </summary>
        /// <returns>The filepath of the texture loaded. </returns>
        FString GetLoadedFilePath();

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        FPoint Size() const;

    private:
        /// <summary>
        /// Allows us to render to the screen.
        /// </summary>
        SDL_Renderer* m_renderer;

        /// <summary>
        /// The actual texture.
        /// </summary>
        SDL_Texture* m_texture;

        /// <summary>
        /// File path of the texture loaded.
        /// </summary>
        FString m_filePath;

        /// <summary>
        /// The size of the Texture.
        /// </summary>
        FPoint m_textureSize;

        /// <summary>
        /// Extracts the meta data from the texture.
        /// </summary>
        /// <param name="texture">Texture to extract metadata. </param>
        void UpdateTextureMetaData(SDL_Texture* texture);
    };

}
