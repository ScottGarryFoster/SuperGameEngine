#pragma once

namespace SuperGameEngine
{
    class GameObject;
    class Collider;

    /// <summary>
    /// Describes the data during a collision
    /// </summary>
    class Collision
    {
    public:
        Collision(GameObject* gameObject, Collider* collider);

        /// <summary>
        /// The object you collided with.
        /// </summary>
        /// <returns>The object you collided with. </returns>
        GameObject* GetCollidedGameObject();

        /// <summary>
        /// The collider you collided with. 
        /// </summary>
        /// <returns>The collider you collided with. </returns>
        Collider* GetCollider();
    private:
        /// <summary>
        /// The object you collided with.
        /// </summary>
        GameObject* m_gameObject;

        /// <summary>
        /// The collider you collided with. 
        /// </summary>
        Collider* m_collider;
    };
}