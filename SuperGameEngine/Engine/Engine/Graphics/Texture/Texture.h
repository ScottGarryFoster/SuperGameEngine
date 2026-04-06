#pragma once
#include <SDL.h>
#include <memory>
#include "SDLRendererReader.h"
#include "TextureDataOrigin.h"
#include "../../../FatedQuestReferences.h"
#include "../../../Structural/Spatial/Area/RectangleInt.h"
#include "Engine/Content/SuperTextureFactory.h"
#include "PureTexture.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    /// <summary>
    /// Contains texture data and the raw ability to render a texture.
    /// </summary>
    class Texture : public virtual PureTexture
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
        virtual bool LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors) override;

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
        virtual bool LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors) override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        void Draw() const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        void Draw(const FPoint& location) const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location, const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        void Draw(const FPoint& location, const FPoint& size) const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location, 
            const FatedQuestLibraries::FPoint& size, 
            const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const override;

        /// <summary>
        /// Draws to the screen with tint.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        /// <param name="tintColour">Tint colour. </param>
        /// <remarks>
        /// Tint here will work fine for things like fonts or a white image you are colouring.
        /// This will not work particularly well for full colour images.
        /// </remarks>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle, const FatedQuestLibraries::FColour& tintColour) const override;

        /// <summary>
        /// Get the Filepath of the loaded texture.
        /// </summary>
        /// <returns>The filepath of the texture loaded. </returns>
        [[nodiscard]] std::string GetLoadedFilePath() const override;

        /// <summary>
         /// Get the size of the Texture in Pixels.
         /// </summary>
         /// <returns>Returns the size of the Texture. </returns>
        [[nodiscard]] FPoint Size() const override;

        /// <summary>
        /// Remakes the texture if possible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last successfully attempted.
        /// </summary>
        bool Remake(std::vector<std::string>& errors) override;

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

        /// <summary>
        /// Validates the renderer and texture can be trusted and used.
        /// </summary>
        /// <param name="methodName">Method name used to better error reporting.</param>
        /// <returns>The renderer or nullptr if the renderer has been destroyed or texture is invalid.</returns>
        SDL_Renderer* ValidateRendererAndTexture(const std::string& methodName) const;

        /// <summary>
        /// Sets the colour for the renderer.
        /// This should be called before you draw.
        /// </summary>
        /// <param name="tintColour">Tint colour. </param>
        void SetColourForRenderer(const FatedQuestLibraries::FColour& tintColour) const;

        /// <summary>
        /// Unsets colour for the renderer back to default.
        /// This should be called after draw and after you have set a tint.
        /// </summary>
        void UnsetColourForRenderer() const;

        /// <summary>
        /// Draws to the screen.
        /// This is the inner logic for this action without any validation of the renderer.
        /// </summary>
        /// <param name="renderer">
        /// Renderer used to render the texture.
        /// Used explicitly! No further validation will be performed.
        /// </param>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        void DrawInnerLogic(SDL_Renderer* renderer, const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const;
    };
}