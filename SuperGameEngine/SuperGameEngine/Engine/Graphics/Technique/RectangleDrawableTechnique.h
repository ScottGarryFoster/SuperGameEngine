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

        virtual void UpdateColour(int r, int g, int b, int a);

    private:

        /// <summary>
        /// Shape to draw.
        /// </summary>
        std::weak_ptr<Rectangle> m_shape;

        int red;
        int green;
        int blue;
        int alpha;
    };
}