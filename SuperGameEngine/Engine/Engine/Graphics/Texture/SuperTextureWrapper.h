#pragma once
#include <memory>

#include "SuperTexture.h"
#include "Texture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture 
    /// </summary>
    class SuperTextureWrapper : public SuperTexture
    {
    public:
        SuperTextureWrapper(const std::shared_ptr<Texture>& texture);
        virtual ~SuperTextureWrapper();

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FPoint& location) const override;

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FPoint& location, const FPoint& size) const override;

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void Draw(const RectangleInt& textureRectangle, const RectangleInt& screenRectangle) const override;

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        virtual bool RepresentSameImage(std::shared_ptr<SuperTexture> texture) const override;

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        virtual bool RepresentSameImage(std::string filePath) const override;

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        virtual FPoint Size() const override;

        /// <summary>
        /// Remakes the texture if possible.
        /// Used when the window has just been torn apart and is now new,
        /// or if the filepath now have new data within it.
        /// Will remake in the same way it was last successfully attempted.
        /// </summary>
        virtual bool Remake(std::vector<std::string>& errors);

    private:
        /// <summary>
        /// Reference to the texture to render.
        /// </summary>
        std::shared_ptr<Texture> m_texture;
    };
}