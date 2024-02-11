#include "ControllerMapper.h"

using namespace SuperGameEngine;

UniversalControllerButton ControllerMapper::GetUniversalControllerButtonFromSDLButton(Controller controller, int SDLButton) const
{
    if (controller == Controller::Xbox360Controller ||
        controller == Controller::XboxSeriesController)
    {
        return GetButtonForXbox360Controller(SDLButton);
    }

    if (controller == Controller::NintendoSwitchProController)
    {
        return GetButtonForNintendoSwitchProController(SDLButton);
    }

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetUniversalControllerButtonFromSDLButton"),
        FString("Controller mapping not found for ") + EController::ToString(controller));
    return UniversalControllerButton::Unknown;
}

int SuperGameEngine::ControllerMapper::GetSDLButtonsOnController(Controller controller) const
{
    switch (controller)
    {
        case Controller::Xbox360Controller: return 11;
        case Controller::XboxSeriesController: return 16;
        case Controller::NintendoSwitchProController: return 20;
    }

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetSDLButtonsOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
}

std::vector<std::pair<int, UniversalControllerButton>> SuperGameEngine::ControllerMapper::GetUniversalControllerButtonMappedToAxis(Controller controller) const
{
    switch (controller)
    {
    case Controller::Xbox360Controller: return GetButtonsForXboxControllerMappedToAxis();
    case Controller::XboxSeriesController: return GetButtonsForXboxControllerMappedToAxis();
    case Controller::NintendoSwitchProController: return GetButtonsForXboxControllerMappedToAxis();
    }

    return std::vector<std::pair<int, UniversalControllerButton>>();
}

int SuperGameEngine::ControllerMapper::GetSDLAxisOnController(Controller controller) const
{
    switch (controller)
    {
    case Controller::Xbox360Controller: return 6;
    case Controller::XboxSeriesController: return 6;
    case Controller::NintendoSwitchProController: return 6;
    }

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetSDLAxisOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
}

bool SuperGameEngine::ControllerMapper::IsGivenAxisValueAPressedValueForButton(Controller controller, UniversalControllerButton button, int SDLAxis, int axisValue) const
{
    if (controller == Controller::Xbox360Controller || controller == Controller::XboxSeriesController)
    {
        return IsGivenAxisValueAPressedValueForButtonForXboxController(button, SDLAxis, axisValue);
    }

    if (controller == Controller::NintendoSwitchProController)
    {
        return UsePureAxisValueForTriggerButtons(button, SDLAxis, axisValue);
    }

    return false;
}

UniversalControllerButton ControllerMapper::GetButtonForXbox360Controller(int SDLButton) const
{
    switch (SDLButton)
    {
        case 0: return UniversalControllerButton::FaceButtonDown;
        case 1: return UniversalControllerButton::FaceButtonRight;
        case 2: return UniversalControllerButton::FaceButtonLeft;
        case 3: return UniversalControllerButton::FaceButtonUp;
        case 4: return UniversalControllerButton::LeftShoulder;
        case 5: return UniversalControllerButton::RightShoulder;
        case 6: return UniversalControllerButton::Select;
        case 7: return UniversalControllerButton::Start;
        case 8: return UniversalControllerButton::LeftStickClick;
        case 9: return UniversalControllerButton::RightStickClick;
    }

    //Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetUniversalControllerButtonFromSDLButton"),
    //    FString("No button mapping found ") + EController::ToString(Controller::Xbox360Controller) + 
    //    FString(" SDLButton: ") + SDLButton);
    return UniversalControllerButton::Unknown;
}

std::vector<std::pair<int, UniversalControllerButton>> ControllerMapper::GetButtonsForXboxControllerMappedToAxis() const
{
    std::vector<std::pair<int, UniversalControllerButton>> returnVector =
    {
        std::pair<int, UniversalControllerButton>(4, UniversalControllerButton::LeftTrigger),
        std::pair<int, UniversalControllerButton>(5, UniversalControllerButton::RightTrigger),
    };
    return returnVector;
}

UniversalControllerButton ControllerMapper::GetButtonForNintendoSwitchProController(int SDLButton) const
{
    switch (SDLButton)
    {
    case 0: return UniversalControllerButton::FaceButtonRight;
    case 1: return UniversalControllerButton::FaceButtonDown;
    case 2: return UniversalControllerButton::FaceButtonUp;
    case 3: return UniversalControllerButton::FaceButtonLeft;
    case 4: return UniversalControllerButton::Select;
        // Resolves to the Screenshot button.
    case 5: return UniversalControllerButton::Unknown;
    case 6: return UniversalControllerButton::Start;
    case 7: return UniversalControllerButton::LeftStickClick;
    case 8: return UniversalControllerButton::RightStickClick;
    case 9: return UniversalControllerButton::LeftShoulder;
    case 10: return UniversalControllerButton::RightShoulder;
    case 11: return UniversalControllerButton::LeftTrigger;
    case 12: return UniversalControllerButton::RightTrigger;
    case 13: return UniversalControllerButton::DPadUp;
    case 14: return UniversalControllerButton::DPadDown;
    case 15: return UniversalControllerButton::DPadLeft;
    case 16: return UniversalControllerButton::DPadRight;
    }

    return UniversalControllerButton::Unknown;
}

bool SuperGameEngine::ControllerMapper::IsGivenAxisValueAPressedValueForButtonForXboxController(UniversalControllerButton button, int SDLAxis, int axisValue) const
{
    if (SDLAxis == 4 && button == UniversalControllerButton::LeftTrigger)
    {
        return axisValue > -30000;
    }
    else if (SDLAxis == 5 && button == UniversalControllerButton::RightTrigger)
    {
        return axisValue > -30000;
    }

    return false;
}

bool SuperGameEngine::ControllerMapper::UsePureAxisValueForTriggerButtons(UniversalControllerButton button, int SDLAxis, int axisValue) const
{
    if (SDLAxis == 4 && button == UniversalControllerButton::LeftTrigger)
    {
        return axisValue == 32767;
    }
    else if (SDLAxis == 5 && button == UniversalControllerButton::RightTrigger)
    {
        return axisValue == 32767;
    }

    return false;
}
