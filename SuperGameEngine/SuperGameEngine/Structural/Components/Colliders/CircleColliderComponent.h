#pragma once
#include "ColliderComponent.h"
#include "../../Spatial/Area/Circle.h"
#include "../../../Engine/Graphics/Technique/CircleDrawableTechnique.h"

namespace SuperGameEngine
{
    class TransformComponent;

    /// <summary>
    /// A circle collider.
    /// </summary>
    class CircleColliderComponent : public ColliderComponent, public FEventObserver
    {
    public:
        CircleColliderComponent();
        virtual ~CircleColliderComponent();

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
        /// <param name="previousLocation">The previous location of the collider.</param>
        /// <remark>
        /// Passing previousLocation ensures that the collider does not 'phase' through the other collider
        /// because the only information it would have go off otherwise is the current frame
        /// which could be a situation in which the direction of least resitance means moving
        /// through the object and not bouncing off it.
        /// </remark>
        virtual void MoveOutOfOverlapRangeOf(const Collider& other, const FVector2D& previousLocation) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(const GameTime gameTime) override;

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
        int GetColliderSize() const;

        /// <summary>
        /// Set the Size of the collider before Transform.
        /// </summary>
        /// <param name="size">New size of the collider. </param>
        void SetColliderSize(int size);

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
        /// <returns>The Circle in the location it should be in. </returns>
        Circle GetArea() const;

    private:
        /// <summary>
        /// Area for the circle without taking into account the transform of the object.
        /// </summary>
        std::shared_ptr<Circle> m_circle;

        /// <summary>
        /// The actual rendered location for the collision.
        /// </summary>
        std::shared_ptr<Circle> m_circleActual;

        /// <summary>
        /// Allows us to draw a circle.
        /// </summary>
        std::shared_ptr<CircleDrawableTechnique> m_circleDrawableTechnique;

        /// <summary>
        /// Location of the object.
        /// </summary>
        std::shared_ptr<TransformComponent> m_transform;
    };

    REGISTER_COMPONENT(CircleColliderComponent)
}