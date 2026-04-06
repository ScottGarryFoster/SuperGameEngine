#pragma once
#include <string>
#include <vector>

namespace FatedQuestLibraries
{
    class FPoint;
}

namespace SuperGameEngine
{
    class RectangleInt;

    /// <summary>
    /// The lowest texture for rendering.
    /// </summary>
    class PureTexture
    {
    public:

        /// <summary>
        /// Loads the given Texture into this class from the File Path.
        /// </summary>
        /// <param name="filePath">File path to the texture. </param>
        /// <param name="errors">If there are errors this is the reason why the texture could not be created. </param>
        /// <returns>True means created, false means not. </returns>
        virtual bool LoadImageFromFile(const std::string& filePath, std::vector<std::string>& errors) = 0;

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
        virtual bool LoadImageFromData(std::vector<unsigned char>& data, const std::string& filepath, std::vector<std::string>& errors) = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FColour& tintColour) const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location) const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location, const FatedQuestLibraries::FColour& tintColour) const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location, const FatedQuestLibraries::FPoint& size) const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location, const FatedQuestLibraries::FPoint& size, const FatedQuestLibraries::FColour& tintColour) const = 0;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const = 0;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle, const FatedQuestLibraries::FColour& tintColour) const = 0;

        /// <summary>
        /// Get the Filepath of the loaded texture.
        /// </summary>
        /// <returns>The filepath of the texture loaded. </returns>
        [[nodiscard]] virtual std::string GetLoadedFilePath() const = 0;

        /// <summary>
         /// Get the size of the Texture in Pixels.
         /// </summary>
         /// <returns>Returns the size of the Texture. </returns>
        virtual FatedQuestLibraries::FPoint Size() const = 0;

        /// <summary>
        /// Remakes the texture if possible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last successfully attempted.
        /// </summary>
        virtual bool Remake(std::vector<std::string>& errors) = 0;
    };
}
