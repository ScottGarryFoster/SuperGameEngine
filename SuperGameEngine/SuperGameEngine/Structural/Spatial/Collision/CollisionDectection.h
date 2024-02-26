#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "CollisionDectectionSubscription.h"
#include "CollisionDectectionUpdate.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Handles Collision Detection on a high level.
    /// </summary>
    class CollisionDectection : 
        public CollisionDectectionSubscription, 
        public CollisionDectectionUpdate, 
        public Object
    {
    public:
        CollisionDectection();
        virtual ~CollisionDectection();

        /// <summary>
        /// Give an active collider.
        /// Active colliders are collided against and collided with.
        /// They take collision and give collision.
        /// </summary>
        /// <param name="collider">An active collision. </param>
        virtual void GiveActiveCollider(std::weak_ptr<Collider> collider) override;

        /// <summary>
        /// Run Collision Update.
        /// </summary>
        virtual void RunCollisionUpdate() override;

    private:
        /// <summary>
        /// A pointer to all the colliders in memory.
        /// </summary>
        FList<std::weak_ptr<Collider>>* m_colliders;
    };
}