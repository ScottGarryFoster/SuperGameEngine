#pragma once
#include <SDL.h>

namespace SuperGameEngine
{
    /// <summary>
    /// Holds everything in the entire game.
    /// </summary>
    class GrandScene
    {
    public:
        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        bool Update(Uint32 tick);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();
    };
}