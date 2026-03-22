#pragma once
#include "../../../../../FatedQuest.Libraries/StandardObjects/Position/FVector2F.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A render-able debug shape.
    /// </summary>
    class PrimitiveShape
    {
    public:

        /// <summary>
        /// Move the shapes origin to the given location.
        /// </summary>
        /// <param name="newLocation">
        /// New location to move the shape.
        /// </param>
        virtual void Move(const FatedQuestLibraries::FVector2F& newLocation) = 0;

        /// <summary>
        /// Draw the shape.
        /// </summary>
        virtual void Draw() const = 0;
    };
}
