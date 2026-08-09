#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class FVector2F;
}

namespace SuperGameEngine
{
    class PrimitiveRectangle;

    /// <summary>
    /// Provides render-able debug primitive shapes.
    /// </summary>
    class PrimitiveShapeProvider
    {
    public:

        /// <summary>
        /// Creates a primitive rectangle.
        /// </summary>
        /// <param name="location">The location to place the rectangle. </param>
        /// <param name="size">The size of the rectangle. </param>
        /// <returns>The created rectangle. </returns>
        virtual std::shared_ptr<PrimitiveRectangle> CreateRectangle(
            const FatedQuestLibraries::FVector2F& location, 
            const FatedQuestLibraries::FVector2F& size) const = 0;
    };
}
