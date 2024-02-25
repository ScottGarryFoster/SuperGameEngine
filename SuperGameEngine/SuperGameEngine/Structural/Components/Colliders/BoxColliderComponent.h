#pragma once
#include "ColliderComponent.h"
#include "../../Spatial/Area/Rectangle.h"
#include "../../../Engine/Graphics/Technique/RectangleDrawableTechnique.h"

namespace SuperGameEngine
{
    class TransformComponent;

    /// <summary>
    /// A collider of a box shape.
    /// </summary>
    class BoxColliderComponent : public ColliderComponent, public FEventObserver
    {
    public:
        BoxColliderComponent();
        virtual ~BoxColliderComponent();

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

        /// <summary>
        /// Other collider Overlaps this.
        /// </summary>
        /// <param name="other">Other to test. </param>
        /// <returns>True means does overlap. </returns>
        virtual bool Overlaps(Collider& other) const override;

        /// <summary>
        /// I contain other meaning I as a collider, contain the other object.
        /// I am the bigger object and contain the other (or we match in size).
        /// </summary>
        /// <param name="other">Other to test. </param>
        /// <returns>True means I contain other. </returns>
        virtual bool Contain(Collider& other) const override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime) override;

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Reacts to events.
        /// </summary>
        /// <param name="arguments">Arguments for the events. </param>
        virtual void Invoke(FEventArguments* arguments) override;

        FVector2D GetColliderLocation() const;

        void SetColliderLocation(FVector2D& location);

        FVector2D GetColliderSize() const;

        void SetColliderSize(FVector2D& size);

        /// <summary>
        /// A collision is on going with another object.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionOccuring(Collision& collision) override;

    private:
        /// <summary>
        /// Area for the box without taking into account the transform of the object.
        /// </summary>
        std::shared_ptr<Rectangle> m_retangle;

        /// <summary>
        /// The actual rendered location for the collision.
        /// </summary>
        std::shared_ptr<Rectangle> m_retangleActual;

        /// <summary>
        /// Allows the Rectangle bounds to be drawn. Used for debug.
        /// </summary>
        std::shared_ptr<RectangleDrawableTechnique> m_rectangleDrawableTechnique;

        /// <summary>
        /// Location of the object.
        /// </summary>
        TransformComponent* m_transform;
    };
}