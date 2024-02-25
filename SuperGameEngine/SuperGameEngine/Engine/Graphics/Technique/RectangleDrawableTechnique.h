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

    private:

        /// <summary>
        /// Shape to draw.
        /// </summary>
        std::weak_ptr<Rectangle> m_shape;
    };
}