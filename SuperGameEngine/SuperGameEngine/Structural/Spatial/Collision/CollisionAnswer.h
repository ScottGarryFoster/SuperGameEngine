#pragma once
#include "CollisionAnswerState.hpp"
#include "Collision.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a single collision.
    /// </summary>
    struct CollisionAnswer
    {
        /// <summary>
        /// Describes the collision responce in an answer.
        /// </summary>
        CollisionAnswerState Answer = CollisionAnswerState::Unknown;

        /// <summary>
        /// Describes the data during a collision
        /// </summary>
        Collision Collision = Collision;
    };
}