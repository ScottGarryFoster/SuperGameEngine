#pragma once
#include "Engine/KeyCode.h"
#include "Engine/UniversalControllerButton.h"

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

        /// <summary>
        /// Determines if button is down.
        /// Fires every frame the buttons is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button is down this frame. </returns>
        virtual bool ButtonDown(UniversalControllerButton button) const = 0;

        /// <summary>
        /// Determines if button is pressed.
        /// Fires the first frame button is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button was just pressed. </returns>
        virtual bool ButtonUp(UniversalControllerButton button) const = 0;

        /// <summary>
        /// Determines if button is was just released.
        /// Fires the first frame a button was released.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        virtual bool ButtonPressed(UniversalControllerButton button) const = 0;
    };
}
