#pragma once
#include <SDL.h>

#include "PrimitiveDrawableShapeTechnique.h"
#include "../../../Structural/Spatial/Area/Circle.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The method to draw Rectangles.
    /// </summary>
    class CircleDrawableTechnique : public PrimitiveDrawableShapeTechnique
    {
    public:
        CircleDrawableTechnique(std::weak_ptr<Circle> shape);
        virtual ~CircleDrawableTechnique();

        /// <summary>
        /// Draws rectangle to screen.
        /// </summary>
        /// <param name="renderer">Ability to render. </param>
        virtual void Draw(SDL_Renderer* renderer) override;

        /// <summary>
        /// Sets the colour for the Rectangle.
        /// </summary>
        /// <param name="red">Red Colour, 0-255. </param>
        /// <param name="green">Green Colour, 0-255. </param>
        /// <param name="blue">Blue Colour, 0-255.  </param>
        /// <param name="alpha">Alpha Value, 0-255. 255 is all Opaque. </param>
        virtual void SetColour(int r, int g, int b, int a);

    private:

        /// <summary>
        /// Shape to draw.
        /// </summary>
        std::weak_ptr<Circle> m_shape;

        /// <summary>
        /// Colour value Red.
        /// </summary>
        int red;

        /// <summary>
        /// Colour value Green.
        /// </summary>
        int green;

        /// <summary>
        /// Colour value blue.
        /// </summary>
        int blue;

        /// <summary>
        /// Alpha value, 255 is Opaque.
        /// </summary>
        int alpha;

        /// <summary>
        /// Draws a filled in circle.
        /// </summary>
        /// <param name="renderer">Renderer to use. </param>
        /// <param name="location">Location of the circle. </param>
        /// <param name="radius">Radius of the circle. </param>
        void DrawFilledIn(SDL_Renderer* renderer, FVector2D& location, int radius);

        /// <summary>
        /// Draws the outline of the circle.
        /// Consider the outline 1 thick or default thickness.
        /// </summary>
        /// <param name="renderer">Renderer to use. </param>
        /// <param name="location">Location of the circle. </param>
        /// <param name="radius">Radius of the circle. </param>
        void DrawOutline(SDL_Renderer* renderer, FVector2D& location, int radius);
    };
}