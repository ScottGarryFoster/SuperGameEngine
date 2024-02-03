#pragma once
#include "../../Engine/Basic/GameTime.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class GameObject
    {
    public:
        /// <summary>
        /// Sets up the GameObject.
        /// </summary>
        void Setup();

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