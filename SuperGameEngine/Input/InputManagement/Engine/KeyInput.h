#pragma once
#include <unordered_map>

#include "KeyCode.h"
#include "KeyState.h"
#include "../Event/WindowEvent.h"

namespace SuperGameInput
{
    /// <summary>
    /// Handles input for Keyboard keys.
    /// </summary>
    class KeyInput
    {
    public:
        KeyInput();
        virtual ~KeyInput();

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update();

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(WindowEvent event);

        /// <summary>
        /// Is the given key down.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means currently down. Will fire continually. </returns>
        virtual bool GetKeyDown(const KeyCode& keyCode) const;

        /// <summary>
        /// Was the key just pressed.
        /// Fires once.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means was just pressed. </returns>
        virtual bool GetKeyPressed(const KeyCode& keyCode) const;

        /// <summary>
        /// Is the given key just been released.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means key was just released. </returns>
        virtual bool GetKeyUp(const KeyCode& keyCode) const;

    private:
        /// <summary>
        /// All keys by key state.
        /// </summary>
        std::unordered_map<KeyCode, KeyState> m_keys;
    };
}
