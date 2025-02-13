#pragma once
#include "Engine/KeyCode.h"
#include "Engine/MouseState.h"
#include "Engine/UniversalControllerAxis.h"
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
        /// Determines if button was just released.
        /// Fires the first frame a button was released.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        virtual bool ButtonPressed(UniversalControllerButton button) const = 0;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -32767 to 32767 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axis value. </returns>
        virtual int AxisValue(UniversalControllerAxis axis) const = 0;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -1 to 1 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axis value. </returns>
        virtual float AxisValueNormalised(UniversalControllerAxis axis) const = 0;

        /// <summary>
        /// Describes the state of a mouse, where it is, what button is pressed.
        /// Technically you can have more than one mouse, this will be the last mouse that had an event.
        /// </summary>
        /// <returns>The state of a mouse. </returns>
        virtual MouseState GetMouseState() const = 0;
    };
}
