#pragma once

#include "../../../../Engine/Engine/Graphics/Texture/SuperTexture.h"

namespace SuperGameEngineTests_Stubs
{
    class SuperTextureStub : public SuperGameEngine::SuperTexture
    {
    public:
        SuperTextureStub(const std::string& path, const FatedQuestLibraries::FPoint& size)
        {
            // Default XY 0, Width Height 0. Needs to be pointers as const is used.
            m_lastDrawnTexture = std::make_shared<SuperGameEngine::RectangleInt>(0,0);
            m_lastDrawnScreen = std::make_shared<SuperGameEngine::RectangleInt>(0,0);

            m_size = size;
            m_path = FatedQuestLibraries::File::Sanitize(path);

            m_timesDrawn = std::make_shared<int>(0);

            // We would only do this in a test situation.
            m_lastColour = std::make_shared<FatedQuestLibraries::FColour>();
            m_lastColour->Red = 0;
            m_lastColour->Green = 0;
            m_lastColour->Blue = 0;
            m_lastColour->Alpha = 0;

            m_lastTransform = std::shared_ptr<SuperGameEngine::TextureTransformationDetails>();
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        virtual void Draw() const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(0, 0);
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(0, 0);
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="transformation">Defines the transformation of a given texture. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location, 
            const SuperGameEngine::TextureTransformationDetails& transformation) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            SaveTransformToLastDrawn(transformation);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location, 
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="transformation">Defines the transformation of a given texture. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location, 
            const SuperGameEngine::TextureTransformationDetails& transformation, 
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(m_size.GetX(), m_size.GetY());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            SaveTransformToLastDrawn(transformation);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        virtual void Draw(const FatedQuestLibraries::FPoint& location, const FatedQuestLibraries::FPoint& size) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(size.GetX(), size.GetY());

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        /// <param name="transformation">Defines the rotation of a given texture. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location, 
            const FatedQuestLibraries::FPoint& size, 
            const SuperGameEngine::TextureTransformationDetails& transformation) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(size.GetX(), size.GetY());

            SaveTransformToLastDrawn(transformation);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location,
            const FatedQuestLibraries::FPoint& size,
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(size.GetX(), size.GetY());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to screen.
        /// </summary>
        /// <param name="location">Location on screen to draw. </param>
        /// <param name="size">Size on the screen to draw. </param>
        /// <param name="transformation">Defines the rotation of a given texture. </param>
        /// <param name="tintColour">Tint colour. </param>
        virtual void Draw(
            const FatedQuestLibraries::FPoint& location,
            const FatedQuestLibraries::FPoint& size,
            const SuperGameEngine::TextureTransformationDetails& transformation,
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(0, 0);
            m_lastDrawnTexture->SetSize(m_size.GetX(), m_size.GetY());

            m_lastDrawnScreen->SetLocation(location.GetX(), location.GetY());
            m_lastDrawnScreen->SetSize(size.GetX(), size.GetY());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            SaveTransformToLastDrawn(transformation);

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
        /// Draws to the screen.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        /// <param name="transformation">Defines the rotation of a given texture. </param>
        virtual void Draw(
            const SuperGameEngine::RectangleInt& textureRectangle,
            const SuperGameEngine::RectangleInt& screenRectangle,
            const SuperGameEngine::TextureTransformationDetails& transformation) const override
        {
            m_lastDrawnTexture->SetLocation(textureRectangle.GetLeft(), textureRectangle.GetTop());
            m_lastDrawnTexture->SetSize(textureRectangle.GetWidth(), textureRectangle.GetHeight());

            m_lastDrawnScreen->SetLocation(screenRectangle.GetLeft(), screenRectangle.GetTop());
            m_lastDrawnScreen->SetSize(screenRectangle.GetWidth(), screenRectangle.GetHeight());

            SaveTransformToLastDrawn(transformation);

            ++*m_timesDrawn;
        }

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
        virtual void Draw(
            const SuperGameEngine::RectangleInt& textureRectangle, 
            const SuperGameEngine::RectangleInt& screenRectangle, 
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(textureRectangle.GetLeft(), textureRectangle.GetTop());
            m_lastDrawnTexture->SetSize(textureRectangle.GetWidth(), textureRectangle.GetHeight());

            m_lastDrawnScreen->SetLocation(screenRectangle.GetLeft(), screenRectangle.GetTop());
            m_lastDrawnScreen->SetSize(screenRectangle.GetWidth(), screenRectangle.GetHeight());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Draws to the screen with tint.
        /// </summary>
        /// <param name="textureRectangle">Where on the texture to render. </param>
        /// <param name="screenRectangle">Where on the screen to render. </param>
        /// <param name="tintColour">Tint colour. </param>
        /// <param name="transformation">Defines the rotation of a given texture. </param>
        /// <remarks>
        /// Tint here will work fine for things like fonts or a white image you are colouring.
        /// This will not work particularly well for full colour images.
        /// </remarks>
        virtual void Draw(
            const SuperGameEngine::RectangleInt& textureRectangle,
            const SuperGameEngine::RectangleInt& screenRectangle,
            const SuperGameEngine::TextureTransformationDetails& transformation,
            const FatedQuestLibraries::FColour& tintColour) const override
        {
            m_lastDrawnTexture->SetLocation(textureRectangle.GetLeft(), textureRectangle.GetTop());
            m_lastDrawnTexture->SetSize(textureRectangle.GetWidth(), textureRectangle.GetHeight());

            m_lastDrawnScreen->SetLocation(screenRectangle.GetLeft(), screenRectangle.GetTop());
            m_lastDrawnScreen->SetSize(screenRectangle.GetWidth(), screenRectangle.GetHeight());

            m_lastColour->Red = tintColour.Red;
            m_lastColour->Blue = tintColour.Blue;
            m_lastColour->Green = tintColour.Green;
            m_lastColour->Alpha = tintColour.Alpha;

            SaveTransformToLastDrawn(transformation);

            ++*m_timesDrawn;
        }

        /// <summary>
        /// Determines if the two textures are the same image.
        /// </summary>
        /// <param name="texture">Texture to test. </param>
        /// <returns>True means are the same. </returns>
        virtual bool RepresentSameImage(std::shared_ptr<SuperTexture> texture) const override
        {
            FatedQuestLibraries::Log::Error("Cannot detect whether texture is the same because path is private in tests.");
            return false;
        }

        /// <summary>
        /// Determines if the texture uses this file path.
        /// </summary>
        /// <param name="filePath">File path to text. </param>
        /// <returns>True means this uses the same file path. </returns>
        virtual bool RepresentSameImage(std::string filePath) const override
        {
            return m_path == FatedQuestLibraries::File::Sanitize(filePath);
        }

        /// <summary>
        /// Get the size of the Texture in Pixels.
        /// </summary>
        /// <returns>Returns the size of the Texture. </returns>
        virtual FatedQuestLibraries::FPoint Size() const override
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

        /// <summary>
        /// If a draw call has occured, this is the rectangle upon the texture attempted.
        /// </summary>
        /// <returns>If a draw call has occured, this is the rectangle upon the texture attempted. </returns>
        std::shared_ptr<SuperGameEngine::RectangleInt> LastDrawnTextureLocation()
        {
            return m_lastDrawnTexture;
        }

        /// <summary>
        /// If a draw call has occured, this is the location and size which was used.
        /// </summary>
        /// <returns>If a draw call has occured, this is the location and size which was used.</returns>
        std::shared_ptr<SuperGameEngine::RectangleInt> LastDrawnScrrenLocation()
        {
            return m_lastDrawnScreen;
        }

        /// <summary>
        /// The last colour drawn to screen.
        /// </summary>
        /// <returns>The last colour drawn to screen. </returns>
        std::shared_ptr<FatedQuestLibraries::FColour> LastColour()
        {
            return m_lastColour;
        }

        SuperGameEngine::TextureTransformationDetails LastTransform()
        {
            return *m_lastTransform;
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
        FatedQuestLibraries::FPoint m_size;

        /// <summary>
        /// Keeps a count of the times drawn.
        /// </summary>
        std::shared_ptr<int> m_timesDrawn;

        /// <summary>
        /// The last colour drawn.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FColour> m_lastColour;

        /// <summary>
        /// Last transformation drawn.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextureTransformationDetails> m_lastTransform;

        void SaveTransformToLastDrawn(const SuperGameEngine::TextureTransformationDetails& other) const
        {
            m_lastTransform->Orientation = other.Orientation;
            m_lastTransform->Angle = other.Angle;
            m_lastTransform->CenterX = other.CenterX;
            m_lastTransform->CenterY = other.CenterY;
        }
    };
}
