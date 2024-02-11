#pragma once
#include "../../../LibraryIncludes.h"
#include "../../GameObject/GameComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Tests user input.
    /// </summary>
    class UserInputTestComponent : public GameComponent
    {
    public:

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime) override;
    };
}


