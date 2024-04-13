#pragma once
#include "../../GameObject/GameComponent.h"
#include "../../Scene/SceneLoadPackage.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A simple rigidbody able to create basic platformers or top down games.
    /// Does not have complete Physics or reactions.
    /// </summary>
    class SimpleRigidbodyComponent : public GameComponent
    {
    public:
        SimpleRigidbodyComponent();
        virtual ~SimpleRigidbodyComponent();

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        virtual void FixedUpdate(GameTime gameTime) override;

        /// <summary>
        /// A collision with something else has begin.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionBegin(Collision& collision);

        /// <summary>
        /// A collision has ended with something.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionEnd(Collision& collision);

        /// <summary>
        /// Adds Velocity in direction.
        /// </summary>
        /// <param name="x">X direction. </param>
        /// <param name="y">Y direction. </param>
        void AddVelocity(float x, float y);

        /// <summary>
        /// Set Velocity in a direction.
        /// Overrides any current Velocity.
        /// </summary>
        /// <param name="x">X direction. </param>
        /// <param name="y">Y direction. </param>
        void SetVelocity(float x, float y);
    private:
        /// <summary>
        /// The previous known location.
        /// </summary>
        FVector2D* m_previousLocation;

        /// <summary>
        /// True when a Fixed update loop has ever occured.
        /// Ensures setup occurs.
        /// </summary>
        bool m_haveEverUpdated;

        /// <summary>
        /// How many objects you are colliding with;
        /// </summary>
        int m_numberOfCollisions;

        /// <summary>
        /// Last time we ran the fixed update the number of collisions we had;
        /// </summary>
        int m_numberOfCollisionsLastFixedUpdate;

        /// <summary>
        /// True means we are not colliding so run physics
        /// </summary>
        bool m_canRunPhysics;

        /// <summary>
        /// True means did move last frame.
        /// </summary>
        bool m_didMoveLastFrame;

        /// <summary>
        /// Current Velocity.
        /// </summary>
        FVector2D* m_currentVelocity;

        /// <summary>
        /// The collider on the GameObject we care about.
        /// </summary>
        /// <remark>
        /// This is what binds this rigidbody to a single collider
        /// per rigidbody.
        /// </remark>
        std::shared_ptr<Collider> m_colliderOnUs;

        /// <summary>
        /// Detirmines based on collisions if now is a good time to run the physics system.
        /// </summary>
        void DetirmineIfCanRunPhysics();

        /// <summary>
        /// Runs the Physics Loop.
        /// </summary>
        void RunPhysicsLoop();
    };
}