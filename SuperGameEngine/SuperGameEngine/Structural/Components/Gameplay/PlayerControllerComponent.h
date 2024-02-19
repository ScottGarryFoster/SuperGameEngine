#pragma once
#include "../../GameObject/GameComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Controls a given GameObject using Gameplay Inputs.
    /// </summary>
    class PlayerControllerComponent : public GameComponent
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
    private:
        void MoveByKeyboard(float speed, SuperGameEngine::GameTime& gameTime, StandardCLibrary::FVector2D* location);
        void MoveByController(StandardCLibrary::FVector2D* location, float speed);
    };
}