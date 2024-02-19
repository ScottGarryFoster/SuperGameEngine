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

        /// <summary>
        /// Updates button presses.
        /// </summary>
        virtual void Update();

        /// <summary>
        /// Determines if button is down.
        /// Fires every frame the buttons is pressed.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button is down this frame. </returns>
        bool ButtonDown(UniversalControllerButton button) const;

        /// <summary>
        /// Determines if button is pressed.
        /// Fires the first frame button is pressed.
        /// </summary>
        /// <param name="button">Universal Controller Button. </param>
        /// <returns>True means button was just pressed. </returns>
        bool ButtonUp(UniversalControllerButton button) const;

        /// <summary>
        /// Determines if button is was just released.
        /// Fires the first frame a button was released.
        /// </summary>
        /// <param name="button">button to test. </param>
        /// <returns>True means button was down and now is released. </returns>
        bool ButtonPressed(UniversalControllerButton button) const;

        /// <summary>
        /// Gets the values on the given Axis.
        /// This is a value -32767 to 32767 with 0 in the middle.
        /// </summary>
        /// <param name="axis">Axis to get the value of. </param>
        /// <returns>Axix value. </returns>
        int AxisValue(UniversalControllerAxis axis) const;

        /// <summary>
        /// Gets the controller plugged in.
        /// Will get the first controller found which is not 'unknown'.
        /// The first not 'Unknown' controller is the one which is used
        /// for input for the Buttons.
        /// </summary>
        /// <returns>Gets a Valid controller plugged in or 'Unknown' if none found (or recognised). </returns>
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
        /// The current axis value on the given controller.
        /// </summary>
        //std::map<int, std::pair<UniversalControllerAxis, int>>* m_axisValueOnController;
        std::map<int, std::map<UniversalControllerAxis, int>>* m_axisValueOnController;

        /// <summary>
        /// Helps figure out what controller we are dealing with.
        /// </summary>
        ControllerResolver* m_controllerResolver;

        /// <summary>
        /// Helps map controls on many controllers.
        /// </summary>
        ControllerMapper* m_controllerMapper;

        /// <summary>
        /// Contains the Controller Layouts for the game.
        /// </summary>
        ControllerLayoutCollection* m_controllerLayoutCollection;

        /// <summary>
        /// Update the Keystate for the given Dictionary.
        /// </summary>
        /// <param name="keyboardStates">Keystate from SDL to use when updating.</param>
        /// <param name="statesToUpdate">
        /// State to update. 
        /// True will be pressed and false will be not pressed.
        /// </param>
        void UpdateKeyState(std::unordered_map<UniversalControllerButton, bool>* statesToUpdate);

        /// <summary>
        /// Update the Axis Values.
        /// </summary>
        void UpdateAxisValue();

        /// <summary>
        /// Returns true if in the deadzone.
        /// Deadzone meaning the area to disregard as too minor to be a considered position.
        /// </summary>
        /// <param name="axisValue">Axis value to test. </param>
        /// <param name="deadzone">Deadzone to use. </param>
        /// <returns>True means in deadzone. </returns>
        bool AxisValueIsInDeadzone(int axisValue, int deadzone) const;

        /// <summary>
        /// Little method which just outputs Controller outputs for testing.
        /// </summary>
        void Tester() const;
    };
}