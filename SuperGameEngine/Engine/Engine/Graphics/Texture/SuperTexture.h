#pragma once
#include <string>
#include "../../../FatedQuestReferences.h"
#include "../../../Structural/Spatial/Area/RectangleInt.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    /// <summary>
    /// The interface for rendering a texture for the majority of the engine.
    /// </summary>
    class SuperTexture
    {
    public:
        virtual ~SuperTexture() = default;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FPoint& location) const = 0;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FPoint& location, const FPoint& size) const = 0;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const = 0;

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        virtual bool RepresentSameImage(std::shared_ptr<SuperTexture> texture) const = 0;

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        virtual bool RepresentSameImage(std::string filePath) const = 0;

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        virtual FPoint Size() const = 0;
    };

}
