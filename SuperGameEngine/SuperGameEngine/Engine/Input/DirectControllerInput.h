#pragma once
#include <SDL.h>

#include "../../LibraryIncludes.h"
#include "DirectXButton.hpp"
#include "KeyState.hpp"
#include "Controller.hpp"
#include "ControllerResolver.h"
#include "UniversalControllerButton.hpp"
#include "ControllerMapper.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Access to input on a XInput controller.
    /// Will only work on Windows or Xbox.
    /// </summary>
    class DirectControllerInput : public Object
    {
    public:
        DirectControllerInput();
        virtual ~DirectControllerInput();

        virtual void Update();

        bool ButtonDown(UniversalControllerButton button) const;

        bool ButtonUp(UniversalControllerButton button) const;

        bool ButtonPressed(UniversalControllerButton button) const;

        /// <summary>
        /// Gets the controller plugged in.
        /// Will get the first controller found which is not 'unknown'.
        /// The first not 'Unknown' controller is the one which is used
        /// for input for the Buttons.
        /// </summary>
        /// <returns></returns>
        Controller GetCurrentController() const;
    private:
        /// <summary>
        /// The current state of the Key.
        /// </summary>
        std::unordered_map<UniversalControllerButton, bool>* m_keyState;

        /// <summary>
        /// The state of the Key last frame.
        /// Used to figure out key up/down/pressed.
        /// </summary>
        std::unordered_map<UniversalControllerButton, bool>* m_keyStateLastFrame;

        /// <summary>
        /// The evaluated state of the key.
        /// </summary>
        std::unordered_map<UniversalControllerButton, KeyState>* m_currentState;

        /// <summary>
        /// Helps figure out what controller we are dealing with.
        /// </summary>
        ControllerResolver* m_controllerResolver;

        /// <summary>
        /// Helps map controls on many controllers.
        /// </summary>
        ControllerMapper* m_controllerMapper;

        /// <summary>
        /// Update the Keystate for the given Dictionary.
        /// </summary>
        /// <param name="keyboardStates">Keystate from SDL to use when updating.</param>
        /// <param name="statesToUpdate">
        /// State to update. 
        /// True will be pressed and false will be not pressed.
        /// </param>
        void UpdateKeyState(std::unordered_map<UniversalControllerButton, bool>* statesToUpdate);
    };
}