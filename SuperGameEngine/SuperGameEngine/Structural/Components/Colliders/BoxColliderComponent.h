#pragma once
#include "ColliderComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A collider of a box shape.
    /// </summary>
    class BoxColliderComponent : public ColliderComponent
    {
    public:
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
    };
}