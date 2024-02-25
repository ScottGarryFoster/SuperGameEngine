#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Handles Collision Detection on a high level.
    /// </summary>
    class CollisionDectection : public Object
    {
    public:
        CollisionDectection();
        virtual ~CollisionDectection();

        void GiveActiveCollider(Collider* collider);

        // TODO: Add a way to remove colliders from the pool.
        //void TakeCollider(std::weak_ptr<Collider> collider);

        void RunCollisionUpdate();

    private:
        /// <summary>
        /// A pointer to all the colliders in memory.
        /// </summary>
        //FList<std::weak_ptr<Collider>>* m_colliders;
        FList<Collider*>* m_colliders;
    };
}