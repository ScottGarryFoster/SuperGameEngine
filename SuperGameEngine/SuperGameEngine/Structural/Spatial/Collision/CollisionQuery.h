#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "CollisionAnswer.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Queries for the colliders in the scene.
    /// </summary>
    /// <remark>
    /// These are expensive commands so use them wisely!
    /// </remark>
    class CollisionQuery
    {
    public:
        /// <summary>
        /// Checks for collisions, for the given GameObject.
        /// </summary>
        /// <param name="gameObjectGuid">The GUID of the game object. </param>
        /// <returns>A list of all of the collisions.</returns>
        virtual std::shared_ptr<FList<CollisionAnswer>> QueryCollisionForGameObject(Guid& gameObjectGuid) const = 0;
    };
}