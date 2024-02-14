#include "ControllerResolver.h"
#include <string>

using namespace SuperGameEngine;
ControllerResolver::ControllerResolver(ControllerLayoutCollection* controllerCollection)
{
    if (!controllerCollection)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Construction"),
            FString("controllerCollection is nullptr. Ensure this is given."));
    }

    m_controllerCollection = controllerCollection;
}

Controller ControllerResolver::GetControllerFromJoyStick(SDL_Joystick* joystick) const
{
    if (!m_controllerCollection)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Construction"),
            FString("controllerCollection is nullptr. Ensure this is given."));
        return Controller::Unknown;
    }

    std::string name = SDL_JoystickName(joystick);
    int axes = SDL_JoystickNumAxes(joystick);
    int button = SDL_JoystickNumButtons(joystick);

    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    for (ControllerLayout* controller : *collection)
    {
        if (name != controller->Name)
        {
            continue;
        }

        if (axes != controller->Axis)
        {
            continue;
        }

        if (button != controller->Buttons)
        {
            continue;
        }

        return controller->Controller;
    }

    return Controller::Unknown;
}