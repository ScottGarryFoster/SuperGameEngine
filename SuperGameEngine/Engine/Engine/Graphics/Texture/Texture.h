#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "SDLRendererReader.h"


namespace SuperGameEngine
{
    /// <summary>
    /// Contains texture data and the raw ability to render a texture.
    /// </summary>
    class Texture
    {
    public:
        Texture(std::shared_ptr<SDLRendererReader> renderer);
        virtual ~Texture();

        /// <summary>
        /// Loads the given Texture into this class from the File Path.
        /// </summary>
        /// <param name="filePath">File path to the texture. </param>
        /// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
        /// <returns>True means created, false means not. </returns>
        bool LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors);

        /// <summary>
        /// Loads a texture from raw data.
        /// </summary>
        /// <param name="data">Data to load the texture from. </param>
        /// <param name="filepath">
        /// Filepath to store when making the texture -
        /// this does not exist and is used to create the texture as part of the comparer.
        /// </param>
        /// <param name="errors">Errors if not created. </param>
        /// <returns>True means created. </returns>
        bool LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors);

        /// <summary>
        /// Draws to screen.
        /// </summary>
        void Draw() const;

        /// <summary>
        /// Get the Filepath of the loaded texture.
        /// </summary>
        /// <returns>The filepath of the texture loaded. </returns>
        std::string GetLoadedFilePath();

        /// <summary>
        /// Remakes the texture if posible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last scuessfully attempted.
        /// </summary>
        bool Remake(std::vector<std::string>& errors);

    private:
        /// <summary>
        /// Wraps the SDL Renderer such that upon the death of the
        /// SDL Window this becomes invalid and the textures wait for a
        /// new texture.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_sdlRenderer;

        /// <summary>
        /// The actual texture.
        /// </summary>
        SDL_Texture* m_texture;

        /// <summary>
        /// File path of the texture loaded.
        /// </summary>
        std::string m_filePath;
    };
}