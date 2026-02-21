#pragma once
#include "PrimitiveRectangle.h"
#include "Structural/Spatial/Area/Rectangle.h"

namespace SuperGameEngine
{
    class SDLRendererReader;

    /// <summary>
    /// Draws a rectangle debug primitive shape.
    /// </summary>
    class SuperPrimitiveRectangle : public virtual PrimitiveRectangle
    {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="renderer">Gives access to the SDL renderer. Note it might not exist however this gives access to it.</param>
        /// <param name="location">Where the rectangle should go. This is in absolute terms in the viewport. </param>
        /// <param name="size">How big the rectangle should be. </param>
        SuperPrimitiveRectangle(
            const std::shared_ptr<SDLRendererReader>& renderer,
            const FatedQuestLibraries::FVector2F& location, 
            const FatedQuestLibraries::FVector2F& size);

        /// <summary>
        /// Move the shapes origin to the given location.
        /// </summary>
        /// <param name="newLocation">
        /// New location to move the shape.
        /// </param>
        virtual void Move(const FatedQuestLibraries::FVector2F& newLocation) override;

        /// <summary>
        /// Draw the shape.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Update the size of the rectangle.
        /// </summary>
        /// <param name="newSize">New size of the rectangle. </param>
        virtual void SetSize(const FatedQuestLibraries::FVector2F& newSize) override;

        /// <summary>
        /// Draw rectangle in the position.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y location. </param>
        /// <param name="width">Width of the rectangle. </param>
        /// <param name="height">Height of the rectangle. </param>
        virtual void DrawInPlace(int x, int y, int width, int height) const override;

    private:

        /// <summary>
        /// Represents the shape of the primitive.
        /// </summary>
        Rectangle m_rectangle;

        /// <summary>
        /// Provides the ability to draw to the screen.
        /// </summary>
        std::shared_ptr<SDLRendererReader> m_renderer;
    };
}
