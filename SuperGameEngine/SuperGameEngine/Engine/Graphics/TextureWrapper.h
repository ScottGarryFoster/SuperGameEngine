#pragma once
#include "../../LibraryIncludes.h"
#include "SuperTexture.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class Texture;

    /// <summary>
    /// A texture owned by the content manager.
    /// </summary>
    class TextureWrapper : public SuperTexture
    {
    public:
        /// <summary>
        /// Constructs a SuperTexture from a texture.
        /// The texture given is SuperTextures responsiblity to delete,
        /// it is cleaned up by the SuperTexture.
        /// </summary>
        /// <param name="texture">Texture to use. </param>
        TextureWrapper(Texture* texture);

        virtual ~TextureWrapper();

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FPoint& location) override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FPoint& location, const FPoint& size) override;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) override;

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        virtual bool RepresentSameImage(SuperTexture* texture) override;

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        virtual bool RepresentSameImage(FString filePath) override;

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        virtual FPoint Size() const override;

    private:
        /// <summary>
        /// The lowest level of texture. This is a wrapper for the Render level.
        /// </summary>
        Texture* m_actualTexture;
    };
}
