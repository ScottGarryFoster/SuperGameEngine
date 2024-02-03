#pragma once
#include "../../Engine/Basic/GameTime.h"

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
        bool Update(GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();
    };
}
