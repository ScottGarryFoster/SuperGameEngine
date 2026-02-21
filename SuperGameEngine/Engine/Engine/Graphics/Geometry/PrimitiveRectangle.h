#pragma once
#include "PrimitiveShape.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Draws a rectangle debug primitive shape.
    /// </summary>
    class PrimitiveRectangle : public virtual PrimitiveShape
    {
    public:

        /// <summary>
        /// Update the size of the rectangle.
        /// </summary>
        /// <param name="newSize">New size of the rectangle. </param>
        virtual void SetSize(const FatedQuestLibraries::FVector2F& newSize) = 0;

        /// <summary>
        /// Draw rectangle in the position.
        /// </summary>
        /// <param name="x">X location. </param>
        /// <param name="y">Y location. </param>
        /// <param name="width">Width of the rectangle. </param>
        /// <param name="height">Height of the rectangle. </param>
        virtual void DrawInPlace(int x, int y, int width, int height) const = 0;
    };
}
