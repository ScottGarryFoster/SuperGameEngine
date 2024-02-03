#pragma once

namespace SuperGameEngine
{
    /// <summary>
    /// Describes the timespan within the update loop.
    /// </summary>
    struct GameTime
    {
        /// <summary>
        /// The ticks since the last non-physics based updated loop.
        /// </summary>
        int TicksSinceLastFrame;
    };
}