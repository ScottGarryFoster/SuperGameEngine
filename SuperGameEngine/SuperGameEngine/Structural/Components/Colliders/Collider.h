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
    };
}