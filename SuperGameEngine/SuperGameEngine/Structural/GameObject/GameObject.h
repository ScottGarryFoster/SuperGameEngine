#pragma once
#include <type_traits>

#include "../../Engine/Basic/GameTime.h"
#include "GameComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class GameObject
    {
    public:
        GameObject();
        virtual ~GameObject();

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

        template<typename T> 
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, T*>::type
        AddComponent();
    };
}