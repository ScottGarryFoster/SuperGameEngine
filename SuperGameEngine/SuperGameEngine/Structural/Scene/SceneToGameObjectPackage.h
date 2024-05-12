#pragma once

namespace SuperGameEngine
{
    class CollisionDectectionSubscription;
    class GrandScene;

    /// <summary>
    /// Objects for the GameObject to operate which GameComponents do not need
    /// to worry about. Things like Collision which the GameObject should help
    /// manage but the Components should feel like are 'managed' by the GameObject.
    /// </summary>
    class SceneToGameObjectPackage
    {
    public:
        SceneToGameObjectPackage(CollisionDectectionSubscription* collisionDection, GrandScene* scene);
        ~SceneToGameObjectPackage();

        /// <summary>
        /// Handles Collision Detection on a high level.
        /// </summary>
        CollisionDectectionSubscription* GetCollisionDectection();

        /// <summary>
        /// GrandScene owner.
        /// Only used for particular functions.
        /// </summary>
        /// <returns>Scene the Game Object is apart of. </returns>
        GrandScene* GetScene();
    private:

        /// <summary>
        /// Handles Collision Detection on a high level.
        /// </summary>
        CollisionDectectionSubscription* m_collisionDectection;

        /// <summary>
        /// GrandScene owner.
        /// Only used for particular functions.
        /// </summary>
        GrandScene* m_scene;
    };
}

