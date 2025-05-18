#pragma once

#include "../../../../Engine/Engine/Graphics/Texture/SuperTexture.h"

namespace SuperGameEngineTests_Stubs
{
    class SuperTextureStub : public SuperGameEngine::SuperTexture
    {
    public:
        ~SuperTextureStub() override = default;
        SuperTextureStub(const std::string& path, const FatedQuestLibraries::FPoint& size)
        {
            // Default XY 0, Width Height 0. Needs to be pointers as const is used.
            m_lastDrawnTexture = std::make_shared<SuperGameEngine::RectangleInt>(0,0);
            m_lastDrawnScreen = std::make_shared<SuperGameEngine::RectangleInt>(0,0);

            m_size = size;
            m_path = File::Sanitize(path);

            m_timesDrawn = std::make_shared<int>(0);
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(0, 0);
            m_lastDrawnScreen->SetSize(0, 0);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FPoint& location) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(0, 0);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FPoint& location, const FPoint& size) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(size.GetX(), size.GetY());

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        virtual void Draw(const SuperGameEngine::RectangleInt& textureRectangle, const SuperGameEngine::RectangleInt& screenRectangle) const override
        {
            m_lastDrawnTexture->SetLocation(textureRectangle.GetLeft(), textureRectangle.GetTop());
            m_lastDrawnTexture->SetSize(textureRectangle.GetWidth(), textureRectangle.GetHeight());

            m_lastDrawnScreen->SetLocation(screenRectangle.GetLeft(), screenRectangle.GetTop());
            m_lastDrawnScreen->SetSize(screenRectangle.GetWidth(), screenRectangle.GetHeight());

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        virtual bool RepresentSameImage(std::shared_ptr<SuperTexture> texture) const override
        {
            Log::Error("Cannot detect whether texture is the same because path is private in tests.");
            return false;
        }

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        virtual bool RepresentSameImage(std::string filePath) const override
        {
            return m_path == File::Sanitize(filePath);
        }

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        virtual FPoint Size() const override
        {
            return m_size;
        }

        /// <summary>
        /// Returns the number of times drawn.
        /// Useful to simply get the times any of the draw calls have occured.
        /// </summary>
        /// <returns>Returns the number of times drawn. </returns>
        int GetTheNumberOfTimesDrawn() const
        {
            return *m_timesDrawn;
        }

    private:
        /// <summary>
        /// The last position on the texture drawn.
        /// </summary>
        std::shared_ptr<SuperGameEngine::RectangleInt> m_lastDrawnTexture;

        /// <summary>
        /// The last position on the screen drawn.
        /// </summary>
        std::shared_ptr<SuperGameEngine::RectangleInt> m_lastDrawnScreen;

        /// <summary>
        /// The path this texture represents.
        /// </summary>
        std::string m_path;

        /// <summary>
        /// The size of the image.
        /// </summary>
        FPoint m_size;

        /// <summary>
        /// Keeps a count of the times drawn.
        /// </summary>
        std::shared_ptr<int> m_timesDrawn;
    };
}
