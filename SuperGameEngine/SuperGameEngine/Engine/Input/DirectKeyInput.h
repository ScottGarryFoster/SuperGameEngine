#pragma once
#include <unordered_map>
#include <SDL.h>

#include "../../LibraryIncludes.h"
#include "InputKeyCode.hpp"
#include "KeyState.hpp"

namespace SuperGameEngine
{
    /// <summary>
    /// Keyboard input from the User.
    /// </summary>
    class DirectKeyInput : public Object
    {
    public:
        DirectKeyInput();
        virtual ~DirectKeyInput();

        /// <summary>
        /// Updates all the objects which require knowleadge from an SDL level.
        /// This would be Key Input for instance.
        /// This is sent directly before the GrandScene Update.
        /// </summary>
        /// <param name="e">Event last sent from the update loop.</param>
        void EventUpdate(SDL_Event& e);

        /// <summary>
        /// Determines if key is down.
        /// Fires every frame the key is pressed.
        /// </summary>
        /// <param name="key">Key to test. </param>
        /// <returns>True means key is down. </returns>
        bool KeyDown(InputKeyCode key) const;

        /// <summary>
        /// Determines if key is pressed.
        /// Fires the first frame key is pressed.
        /// </summary>
        /// <param name="key">Key to test. </param>
        /// <returns>True means key was just pressed. </returns>
        bool KeyPressed(InputKeyCode key) const;

        /// <summary>
        /// Determines if key is was just released.
        /// Fires the first frame a key was released.
        /// </summary>
        /// <param name="key">Key to test. </param>
        /// <returns>True means key was down and now is released. </returns>
        bool KeyUp(InputKeyCode key) const;
    private:

        /// <summary>
        /// The current state of the Key.
        /// </summary>
        std::unordered_map<InputKeyCode, bool>* m_keyState;

        /// <summary>
        /// The state of the Key last frame.
        /// Used to figure out key up/down/pressed.
        /// </summary>
        std::unordered_map<InputKeyCode, bool>* m_keyStateLastFrame;

        /// <summary>
        /// The evaluated state of the key.
        /// </summary>
        std::unordered_map<InputKeyCode, KeyState>* m_currentState;

        /// <summary>
        /// Update the Keystate for the given Dictionary.
        /// </summary>
        /// <param name="keyboardStates">Keystate from SDL to use when updating.</param>
        /// <param name="statesToUpdate">
        /// State to update. 
        /// True will be pressed and false will be not pressed.
        /// </param>
        void UpdateKeyState(const Uint8* keyboardStates, std::unordered_map<InputKeyCode, bool>* statesToUpdate);
    };
}

