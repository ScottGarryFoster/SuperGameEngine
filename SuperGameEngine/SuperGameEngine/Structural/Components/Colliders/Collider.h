#pragma once
#include "../../../LibraryIncludes.h"
#include "../../GameObject/GameComponent.h"


using namespace StandardCLibrary;
namespace SuperGameEngine
{
    /// <summary>
    /// The basics of a Collider.
    /// </summary>
    /// <remark> The dirt flag goes here </remark>
    class Collider
    {
    public:
        Collider()
        {
            m_guid = GUIDHelpers::CreateGUID();
        }

        /// <summary>
        /// Gets the parent gameobject.
        /// </summary>
        /// <returns>The gameobject the collider belongs to. </returns>
        virtual GameObject* GetParentObject() = 0;

        /// <summary>
        /// Other collider Overlaps this.
        /// </summary>
        /// <param name="other">Other to test. </param>
        /// <returns>True means does overlap. </returns>
        virtual bool Overlaps(Collider& other) const = 0;

        /// <summary>
        /// I contain other meaning I as a collider, contain the other object.
        /// I am the bigger object and contain the other (or we match in size).
        /// </summary>
        /// <param name="other">Other to test. </param>
        /// <returns>True means I contain other. </returns>
        virtual bool Contain(Collider& other) const = 0;

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
        virtual void MoveOutOfOverlapRangeOf(const Collider& other, const FVector2D& previousLocation) = 0;

        /// <summary>
        /// Get a unique identifier for the collider.
        /// This is unique per collider instance and it could be attached to a collection
        /// of colliders, it could be a collection.
        /// The uniquness of the identifier is used to establish this collider is different
        /// from another collider.
        /// </summary>
        /// <returns></returns>
        inline std::shared_ptr<Guid> GetColliderGuid()
        {
            return m_guid;
        }

    private:
        /// <summary>
        /// A unique identifer.
        /// </summary>
        std::shared_ptr<Guid> m_guid;
    };
}