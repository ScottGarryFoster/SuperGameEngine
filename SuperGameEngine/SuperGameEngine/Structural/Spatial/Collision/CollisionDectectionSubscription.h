#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Allows colliders to react and act upon other colliders.
    /// </summary>
    class CollisionDectectionSubscription
    {
    public:

        /// <summary>
        /// Give an active collider.
        /// Active colliders are collided against and collided with.
        /// They take collision and give collision.
        /// </summary>
        /// <param name="collider">An active collision. </param>
        virtual void GiveActiveCollider(std::weak_ptr<Collider> collider) = 0;
    };
}