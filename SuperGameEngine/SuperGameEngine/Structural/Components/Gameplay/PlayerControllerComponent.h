#pragma once
#include "../../GameObject/GameComponent.h"
#include "../Physics/SimpleRigidbodyComponent.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Controls a given GameObject using Gameplay Inputs.
    /// </summary>
    class PlayerControllerComponent : public GameComponent
    {
    public:
        PlayerControllerComponent();
        virtual ~PlayerControllerComponent();

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

        /// <summary>
        /// Temp method to make player use only keyboard.
        inline void UseKeyboard(bool trueToUseKeyboard)
        {
            m_useKeyboard = trueToUseKeyboard;
        }

        /// <summary>
        /// Updates the speed.
        /// </summary>
        /// <param name="newValue">New speed value.</param>
        void SetSpeed(float newValue);

    private:
        void MoveByKeyboard(float speed, SuperGameEngine::GameTime& gameTime, StandardCLibrary::FVector2D* location);
        void MoveByController(StandardCLibrary::FVector2D* location, float speed);

        bool m_useKeyboard;

        std::shared_ptr<SimpleRigidbodyComponent> m_simpleRigidbodyComponent;

        float m_speed;
    };
}