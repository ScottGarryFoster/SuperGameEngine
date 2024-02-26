#pragma once

namespace SuperGameEngine
{
    class CollisionDectectionSubscription;

    /// <summary>
    /// Objects for the GameObject to operate which GameComponents do not need
    /// to worry about. Things like Collision which the GameObject should help
    /// manage but the Components should feel like are 'managed' by the GameObject.
    /// </summary>
    class SceneToGameObjectPackage
    {
    public:
        SceneToGameObjectPackage(CollisionDectectionSubscription* collisionDection);
        ~SceneToGameObjectPackage();

        /// <summary>
        /// Handles Collision Detection on a high level.
        /// </summary>
        CollisionDectectionSubscription* GetCollisionDectection();
    private:

        /// <summary>
        /// Handles Collision Detection on a high level.
        /// </summary>
        CollisionDectectionSubscription* m_collisionDectection;
    };
}

