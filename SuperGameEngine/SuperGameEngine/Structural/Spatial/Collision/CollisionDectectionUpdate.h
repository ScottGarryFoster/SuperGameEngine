#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Allows colliders to react and act upon other colliders.
    /// </summary>
    class CollisionDectectionUpdate
    {
    public:

        /// <summary>
        /// Run Collision Update.
        /// </summary>
        virtual void RunCollisionUpdate() = 0;
    };
}