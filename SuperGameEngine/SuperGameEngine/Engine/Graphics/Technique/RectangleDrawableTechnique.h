#pragma once
#include <SDL.h>

#include "PrimitiveDrawableShapeTechnique.h"
#include "../../../Structural/Spatial/Area/Rectangle.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The method to draw Rectangles.
    /// </summary>
    class RectangleDrawableTechnique : public PrimitiveDrawableShapeTechnique
    {
    public:
        RectangleDrawableTechnique(std::weak_ptr<Rectangle> shape);
        virtual ~RectangleDrawableTechnique();

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
        virtual void SetColour(int red, int green, int blue, int alpha);

    private:

        /// <summary>
        /// Shape to draw.
        /// </summary>
        std::weak_ptr<Rectangle> m_shape;

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
    };
}