#pragma once
#include "../../LibraryIncludes.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class Texture;

    /// <summary>
    /// A texture owned by the content manager.
    /// </summary>
    class SuperTexture
    {
    public:
        SuperTexture(Texture* texture);

        /// <summary>
        /// Draws to screen.
        /// </summary>
        void Draw();

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        void Draw(const FPoint& location);

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        void Draw(FPoint location, FPoint size);

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        bool RepresentSameImage(SuperTexture* texture);

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        bool RepresentSameImage(FString filePath);

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        FPoint Size() const;

    private:

        Texture* m_actualTexture;
    };
}
