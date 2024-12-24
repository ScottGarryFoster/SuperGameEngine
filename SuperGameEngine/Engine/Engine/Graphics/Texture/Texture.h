#pragma once
#include <SDL.h>
#include <memory>
#include "SDLRendererReader.h"
#include "TextureDataOrigin.h"
#include "../../../FatedQuestReferences.h"
#include "../../../Structural/Spatial/Area/RectangleInt.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    /// <summary>
    /// Contains texture data and the raw ability to render a texture.
    /// </summary>
    class Texture
    {
    public:
        Texture(const std::shared_ptr<SDLRendererReader>& renderer);
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
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        void Draw(const FPoint& location) const;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        void Draw(const FPoint& location, const FPoint& size) const;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const;

        /// <summary>
        /// Get the Filepath of the loaded texture.
        /// </summary>
        /// <returns>The filepath of the texture loaded. </returns>
        [[nodiscard]] std::string GetLoadedFilePath() const;

        /// <summary>
         /// Get the size of the Texture in Pixels.
         /// </summary>
         /// <returns>Returns the size of the Texture. </returns>
        FPoint Size() const;

        /// <summary>
        /// Remakes the texture if possible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last successfully attempted.
        /// </summary>
        bool Remake(std::vector<std::string>& errors);

    protected:

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

    private:

        /// <summary>
        /// File path of the texture loaded.
        /// </summary>
        std::string m_filePath;

        /// <summary>
        /// If the texture was last loaded from data,
        /// this is the data to use to recreate it.
        /// </summary>
        std::vector<unsigned char> m_textureData;

        /// <summary>
        /// How the texture was loaded in last.
        /// This is used to understand how to recreate the texture
        /// if the renderer was ever torn down.
        /// </summary>
        TextureDataOrigin m_textureDataOrigin;

        /// <summary>
        /// The size of the Texture.
        /// </summary>
        std::shared_ptr<FPoint> m_textureSize;

        /// <summary>
        /// Reused draw screen rect location.
        /// Kept on the heap to reduce size.
        /// Might move dependent on performance.
        /// </summary>
        std::shared_ptr<SDL_Rect> m_screenRect;

        /// <summary>
        /// Reused texture rect.
        /// Used for the area to draw on the texture.
        /// </summary>
        std::shared_ptr<SDL_Rect> m_textureRect;

        /// <summary>
        /// Extracts the metadata from the texture.
        /// </summary>
        /// <param name="texture">Texture to extract metadata. </param>
        void UpdateTextureMetaData(SDL_Texture* texture) const;

        bool ValidateRendererAndTexture(const std::string& methodName) const;
    };
}