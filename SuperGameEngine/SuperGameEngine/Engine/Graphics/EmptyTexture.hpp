#pragma once
#include "SuperTexture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture without an image.
    /// Used to create a dummy object only.
    /// </summary>
    class EmptyTexture : public SuperTexture
    {
    public:
        /// <summary>
        /// Draws to screen.
        /// </summary>
        inline virtual void Draw() override 
        {
            Logger::Info(FString("EmptyTexture::Draw: This Texture is empty. "));
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        inline virtual void Draw(const FPoint& location) override
        {
            Logger::Info(FString("EmptyTexture::Draw: This Texture is empty. "));
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        inline virtual void Draw(const FPoint& location, const FPoint& size) override
        {
            Logger::Info(FString("EmptyTexture::Draw: This Texture is empty. "));
        }

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        inline virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) override
        {
            Logger::Info(FString("EmptyTexture::Draw: This Texture is empty. "));
        }

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        inline virtual bool RepresentSameImage(SuperTexture* texture) override
        {
            return false;
        }

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        inline virtual bool RepresentSameImage(FString filePath) override
        {
            return false;
        }

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        inline virtual FPoint Size() const override
        {
            return FPoint();
        }
    };
}