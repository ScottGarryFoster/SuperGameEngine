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
        /// Moves rectangle out of range of other Collider.
        /// </summary>
        /// <param name="other">Other to move out of range of. </param>
        virtual void MoveOutOfOverlapRangeOf(const Collider& other) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime) override;

        /// <summary>
        /// Reacts to events.
        /// </summary>
        /// <param name="arguments">Arguments for the events. </param>
        virtual void Invoke(FEventArguments* arguments) override;

        /// <summary>
        /// Get the location of the Collider.
        /// This is the Location of the Box Relative to the Transform.
        /// </summary>
        /// <returns>Location of the Collider. </returns>
        FVector2D GetColliderLocation() const;

        /// <summary>
        /// Set Collider location, relative to the transform.
        /// </summary>
        /// <param name="location">Location of the Collider. </param>
        void SetColliderLocation(FVector2D& location);

        /// <summary>
        /// Get the size of the Collider in both directions.
        /// This is before scaling.
        /// </summary>
        /// <returns>Size of the Collider. </returns>
        FVector2D GetColliderSize() const;

        /// <summary>
        /// Set the Size of the collider before Transform.
        /// </summary>
        /// <param name="size">New size of the collider. </param>
        void SetColliderSize(FVector2D& size);

        /// <summary>
        /// A collision with something else has begin.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionBegin(Collision& collision) override;

        /// <summary>
        /// A collision is on going with another object.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionOccuring(Collision& collision) override;

        /// <summary>
        /// A collision has ended with something.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionEnd(Collision& collision) override;

        /// <summary>
        /// Get the area which represents the main portion of the component.
        /// </summary>
        /// <returns>The Rectangle in the location it should be in. </returns>
        Rectangle GetArea() const;

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
        std::shared_ptr<TransformComponent> m_transform;
    };
}