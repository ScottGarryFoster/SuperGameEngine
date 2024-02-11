#pragma once
#include <SDL.h>
#include "Controller.hpp"

namespace SuperGameEngine
{
    /// <summary>
    /// Figures out what controller an SDL Joystick is likely to be.
    /// </summary>
    class ControllerResolver
    {
    public:
        /// <summary>
        /// Get what we believe the joystick is.
        /// This might fail because controllers are difficult.
        /// </summary>
        /// <param name="joystick">Joystick to test. </param>
        /// <returns>The controller we believe this joystick is or Unknown if we have no idea.</returns>
        Controller GetControllerFromJoyStick(SDL_Joystick* joystick) const;

    private:
        /// <summary>
        /// Detirmines if Joystick is Xbox 360.
        /// </summary>
        /// <param name="joystick">Joystick to test. </param>
        /// <returns>True means it is. </returns>
        bool JoystickIsXbox360Controller(SDL_Joystick* joystick) const;

        /// <summary>
        /// Detirmines if Joystick is Xbox Series Controller.
        /// </summary>
        /// <param name="joystick">Joystick to test. </param>
        /// <returns>True means it is. </returns>
        bool JoystickIsXboxSeriesController(SDL_Joystick* joystick) const;
        
        /// <summary>
        /// Detirmines if Joystick is Nintendo Switch Pro Controller.
        /// </summary>
        /// <param name="joystick">Joystick to Test. </param>
        /// <returns>True means it is. </returns>
        bool JoystickIsNintendoSwitchProController(SDL_Joystick* joystick) const;
    };
}