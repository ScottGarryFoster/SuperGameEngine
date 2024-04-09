#pragma once
#include "../../../LibraryIncludes.h"
#include "../../../Structural/Components/Colliders/Collider.h"
#include "CollisionDectectionSubscription.h"
#include "CollisionDectectionUpdate.h"
#include "CollisionQuery.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Handles Collision Detection on a high level.
    /// </summary>
    class CollisionDectection : 
        public CollisionDectectionSubscription, 
        public CollisionDectectionUpdate,
        public CollisionQuery,
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

        /// <summary>
        /// Checks for collisions, for the given GameObject.
        /// </summary>
        /// <param name="gameObjectGuid">The GUID of the game object. </param>
        /// <returns>A list of all of the collisions.</returns>
        virtual std::shared_ptr<FList<CollisionAnswer>> QueryCollisionForGameObject(Guid& gameObjectGuid) const override;
    private:
        /// <summary>
        /// A pointer to all the colliders in memory.
        /// </summary>
        FList<std::weak_ptr<Collider>>* m_colliders;

        /// <summary>
        /// The last state of collider on collider action.
        /// First number is the outter active collider guid as a number.
        /// Inside is another dictionary of the colliders it has ever been tested against.
        /// First number in this is the number of the testing collider (GUID number)
        /// Second bool is true when the last time we checked the collision it was colliding.
        /// We use this to figure out Start, Happening and End.
        /// </summary>
        std::shared_ptr<
            FDictionary<uint64_t, 
                std::shared_ptr<FDictionary<uint64_t, bool>>>> m_colliderCollisionHistory;

        /// <summary>
        /// Ensures we are tracking the active colliders.
        /// Active colliders are ones which can react to collisions.
        /// </summary>
        /// <param name="guid">GUID of the Active collider. </param>
        void EnsureActiveColliderInteractionExists(uint64_t guid);

        /// <summary>
        /// Get the active collider interactions.
        /// This is all the unactive colliders and their interactions.
        /// </summary>
        /// <param name="guid">Active collider guid. </param>
        /// <returns>Active Collider Interaction. </returns>
        std::shared_ptr<FDictionary<uint64_t, bool>> GetActiveColliderInteraction(uint64_t guid) const;

        /// <summary>
        /// Ensure we are tracking unactive collider interactions for this active collider.
        /// Unactive colliders are collided upon and could be static. 
        /// </summary>
        /// <param name="activeCollection">Active collider interactions to add to if not tracking. </param>
        /// <param name="guid">GUID of the unactive collider. </param>
        void EnsureUnactiveColliderInteractionExists(
            std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, 
            uint64_t guid);

        /// <summary>
        /// Get the value of the interaction between the active and unactive collider.
        /// True means last time we checked collision, these two were colliding.
        /// </summary>
        /// <param name="activeCollection">Collection of collider interactions. </param>
        /// <param name="guid">GUID of the unactive collider. </param>
        /// <returns>True means last time we checked collision, these two were colliding. </returns>
        bool GetUnactiveColliderValue(
            std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, 
            uint64_t guid) const;
        
        /// <summary>
        /// Sets the value of the interaction between the active and unactive collider.
        /// True means last time we checked collision, these two were colliding.
        /// </summary>
        /// <param name="activeCollection">Collection of collider interactions. </param>
        /// <param name="guid">GUID of the unactive collider. </param>
        /// <param name="newValue">The new value to set. True means last time we checked collision, these two were colliding. </param>
        void SetUnactiveColliderValue(
            std::shared_ptr<FDictionary<uint64_t, bool>>& activeCollection, 
            uint64_t guid, bool newValue);

        /// <summary>
        /// Creates a collision object which is used as information about the collision.
        /// </summary>
        /// <param name="parent">The object the parent collider was apart of.</param>
        /// <param name="other">The collider of the other collider. </param>
        /// <returns>Collision information. </returns>
        Collision CreateCollision(GameObject* parent, Collider* other) const;
    };
}