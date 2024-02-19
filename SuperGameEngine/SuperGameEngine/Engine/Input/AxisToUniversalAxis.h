#pragma once
#include "../../LibraryIncludes.h"
#include "UniversalControllerAxis.hpp"

namespace SuperGameEngine
{
    /// <summary>
    /// Maps SDLAxis to Universal Axis.
    /// </summary>
    struct AxisToUniversalAxis
    {
        /// <summary>
        /// SDL Axis number.
        /// </summary>
        int SDLAxis = -1;

        /// <summary>
        /// Axis upon a controller.
        /// </summary>
        UniversalControllerAxis UniversalAxis = UniversalControllerAxis::Unknown;

        /// <summary>
        /// True means has a deadzone.
        /// If False no deadzone is applied.
        /// </summary>
        bool HasDeadzone = false;

        /// <summary>
        /// Deadzone to use if applied.
        /// </summary>
        int Deadzone = 0;
    };
}