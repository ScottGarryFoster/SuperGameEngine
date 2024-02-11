#include "ControllerResolver.h"
#include <string>

using namespace SuperGameEngine;
Controller ControllerResolver::GetControllerFromJoyStick(SDL_Joystick* joystick) const
{
    if (JoystickIsXbox360Controller(joystick))
    {
        return Controller::Xbox360Controller;
    }

    if (JoystickIsXboxSeriesController(joystick))
    {
        return Controller::XboxSeriesController;
    }

    if (JoystickIsNintendoSwitchProController(joystick))
    {
        return Controller::NintendoSwitchProController;
    }

    return Controller::Unknown;
}

bool ControllerResolver::JoystickIsXbox360Controller(SDL_Joystick* joystick) const
{
    std::string name = SDL_JoystickName(joystick);
    int axes = SDL_JoystickNumAxes(joystick);
    int button = SDL_JoystickNumButtons(joystick);

    if (name != "Xbox 360 Controller")
    {
        return false;
    }

    if (SDL_JoystickNumAxes(joystick) != 6)
    {
        return false;
    }

    if (SDL_JoystickNumButtons(joystick) != 11)
    {
        return false;
    }

    return true;
}

bool SuperGameEngine::ControllerResolver::JoystickIsXboxSeriesController(SDL_Joystick* joystick) const
{
    std::string name = SDL_JoystickName(joystick);
    int axes = SDL_JoystickNumAxes(joystick);
    int button = SDL_JoystickNumButtons(joystick);

    if (name != "Controller (Xbox One For Windows)")
    {
        return false;
    }

    if (axes != 6)
    {
        return false;
    }

    if (button != 16)
    {
        return false;
    }

    return true;
}

bool SuperGameEngine::ControllerResolver::JoystickIsNintendoSwitchProController(SDL_Joystick* joystick) const
{
    std::string name = SDL_JoystickName(joystick);
    int axes = SDL_JoystickNumAxes(joystick);
    int button = SDL_JoystickNumButtons(joystick);

    if (name != "Nintendo Switch Pro Controller")
    {
        return false;
    }

    if (axes != 6)
    {
        return false;
    }

    if (button != 20)
    {
        return false;
    }

    return true;
}
