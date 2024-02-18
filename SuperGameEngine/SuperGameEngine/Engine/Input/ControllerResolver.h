#pragma once
#include <SDL.h>
#include "Controller.hpp"
#include "ControllerLayoutCollection.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Figures out what controller an SDL Joystick is likely to be.
    /// </summary>
    class ControllerResolver : public Object
    {
    public:
        ControllerResolver(ControllerLayoutCollection* controllerCollection);

        /// <summary>
        /// Get what we believe the joystick is.
        /// This might fail because controllers are difficult.
        /// </summary>
        /// <param name="joystick">Joystick to test. </param>
        /// <returns>The controller we believe this joystick is or Unknown if we have no idea.</returns>
        Controller GetControllerFromJoyStick(SDL_Joystick* joystick) const;

    private:

        /// <summary>
        /// Contains the Controller Layouts for the game.
        /// </summary>
        ControllerLayoutCollection* m_controllerCollection;
    };
}