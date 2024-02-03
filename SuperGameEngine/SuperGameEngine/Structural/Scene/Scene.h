#pragma once

namespace SuperGameEngine
{
    class Scene
    {
    public:
        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        bool Update();

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();
    };
}
