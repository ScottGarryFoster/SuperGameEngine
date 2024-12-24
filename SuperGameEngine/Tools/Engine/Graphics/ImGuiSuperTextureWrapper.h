#pragma once
#include "ImGuiSuperTexture.h"

using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ImGuiTexture;

    /// <summary>
    /// An Imgui Texture
    /// </summary>
    class ImGuiSuperTextureWrapper : public ImGuiSuperTexture
    {
    public:
        ImGuiSuperTextureWrapper(const std::shared_ptr<ImGuiTexture>& texture);
        virtual ~ImGuiSuperTextureWrapper() override = default;

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

    private:
        /// <summary>
        /// The actual texture.
        /// </summary>
        std::shared_ptr<ImGuiTexture> m_texture;
    };
}


