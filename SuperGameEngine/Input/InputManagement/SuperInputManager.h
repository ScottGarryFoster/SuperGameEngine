#pragma once
#include "InputManager.h"

namespace SuperGameInput
{
    class ControllerInput;
    class KeyInput;

    /// <summary>
    /// Handles and updates user input.
    /// </summary>
    class SuperInputManager : public InputManager
    {
    public:
        SuperInputManager();
        virtual ~SuperInputManager() override = default;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="gamePackage">Game Package, used to load controller inputs. </param>
        virtual void Setup(const std::shared_ptr<GamePackage>& gamePackage) override;

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(WindowEvent event) override;

        /// <summary>
        /// Is the given key down.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means currently down. Will fire until up. </returns>
        virtual bool GetKeyDown(const KeyCode& keyCode) const override;

        /// <summary>
        /// Was the key just pressed.
        /// Fires once.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means was just pressed. </returns>
        virtual bool GetKeyPressed(const KeyCode& keyCode) const override;

        /// <summary>
        /// Is the given key just been released.
        /// </summary>
        /// <param name="keyCode">Keycode to test. </param>
        /// <returns>True means key was just released. </returns>
        virtual bool GetKeyUp(const KeyCode& keyCode) const override;

        /// <summary>
        /// Determines if button is down.
        /// Fires every frame the buttons is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button is down this frame. </returns>
        virtual bool ButtonDown(UniversalControllerButton button) const override;

        /// <summary>
        /// Determines if button is pressed.
        /// Fires the first frame button is pressed.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button was just pressed. </returns>
        virtual bool ButtonUp(UniversalControllerButton button) const override;

        /// <summary>
        /// Determines if button is was just released.
        /// Fires the first frame a button was released.
        /// This poll every controller, if any meet the requirements it returns true.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        virtual bool ButtonPressed(UniversalControllerButton button) const override;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -32767 to 32767 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axis value. </returns>
        virtual int AxisValue(UniversalControllerAxis axis) const override;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -1 to 1 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axis value. </returns>
        virtual float AxisValueNormalised(UniversalControllerAxis axis) const override;
    private:
        /// <summary>
        /// Handles input for Keyboard keys.
        /// </summary>
        std::shared_ptr<KeyInput> m_keyInput;

        /// <summary>
        /// Handles controller Input.
        /// </summary>
        std::shared_ptr<ControllerInput> m_controllerInput;
    };
}
