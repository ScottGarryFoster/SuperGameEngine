#pragma once
#include "Engine/KeyCode.h"

namespace SuperGameInput
{
    /// <summary>
    /// Given to Tools and Engine to provide Input.
    /// </summary>
    class InputHandler
    {
    public:
        /// <summary>
        /// Is the given key down.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means currently down. Will fire until up. </returns>
        virtual bool GetKeyDown(const KeyCode& keyCode) const = 0;

        /// <summary>
        /// Was the key just pressed.
        /// Fires once.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means was just pressed. </returns>
        virtual bool GetKeyPressed(const KeyCode& keyCode) const = 0;

        /// <summary>
        /// Is the given key just been released.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means key was just released. </returns>
        virtual bool GetKeyUp(const KeyCode& keyCode) const = 0;
    };
}
