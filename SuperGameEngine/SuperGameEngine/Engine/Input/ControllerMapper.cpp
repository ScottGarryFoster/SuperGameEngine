#include "ControllerMapper.h"
#include <SDL.h>

using namespace SuperGameEngine;

ControllerMapper::ControllerMapper(ControllerLayoutCollection* controllerCollection)
{
    if (!controllerCollection)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Construction"),
            FString("controllerCollection is nullptr. Ensure this is given."));
    }

    m_controllerCollection = controllerCollection;
}

UniversalControllerButton ControllerMapper::GetUniversalControllerButtonFromSDLButton(Controller controller, int SDLButton) const
{
    UniversalControllerButton returnButton = UniversalControllerButton::Unknown;

    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        FList<std::pair<int, UniversalControllerButton>> buttons =
            found[0]->SDLToUniversalButton.Where(
                [SDLButton](const std::pair<int, UniversalControllerButton> p)
                { return p.first == SDLButton; });
        if (buttons.Any())
        {
            return buttons[0].second;
        }
    }
    else
    {
        Logger::Assert(NotImplementedException(), GetTypeName(), FString("GetUniversalControllerButtonFromSDLButton"),
            FString("Controller mapping not found for ") + EController::ToString(controller));
    }

    return returnButton;
}

int ControllerMapper::GetSDLButtonsOnController(Controller controller) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Count() > 0)
    {
        return found[0]->Buttons;
    }

    Logger::Assert(NotImplementedException(), GetTypeName(), FString("GetSDLButtonsOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
}

std::vector<std::pair<int, UniversalControllerButton>> 
    ControllerMapper::GetUniversalControllerButtonMappedToAxis(Controller controller) const
{
    std::vector<std::pair<int, UniversalControllerButton>> returnVector;

    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        for (ControllerAxisMappedToButton axisToButton : found[0]->AxisToButton)
        {
            returnVector.push_back(
                std::pair<int, UniversalControllerButton>(
                    axisToButton.Axis, axisToButton.Button));
        }
    }

    return returnVector;
}

int ControllerMapper::GetSDLAxisOnController(Controller controller) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        return found[0]->Axis;
    }

    Logger::Assert(NotImplementedException(), GetTypeName(), FString("GetSDLAxisOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
}

AxisToUniversalAxis ControllerMapper::GetUniversalAxisMapping(Controller controller, int SDLAxis) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        FList<AxisToUniversalAxis> axis = found[0]->SDLAxisToUniversalAxis.Where(
            [SDLAxis](const AxisToUniversalAxis& c) { return c.SDLAxis == SDLAxis; });
        if (axis.Any())
        {
            return axis[0];
        }
    }

    return AxisToUniversalAxis();
}

int ControllerMapper::GetSDLHatMappedToDPad(Controller controller) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        return found[0]->HatMappedToDpad;
    }

    Logger::Assert(NotImplementedException(), GetTypeName(), FString("GetSDLAxisOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
}

UniversalControllerButton ControllerMapper::GetHatStateMappedToDPad(int hatState)
{
    UniversalControllerButton pressed = UniversalControllerButton::Unknown;
    if (hatState == SDL_HAT_CENTERED)
    {
        // Included for completeness.
        pressed = UniversalControllerButton::Unknown;
    }
    else if (hatState & SDL_HAT_UP)
    {
        pressed = UniversalControllerButton::DPadUp;
    }
    else if (hatState & SDL_HAT_DOWN)
    {
        pressed = UniversalControllerButton::DPadDown;
    }
    else if (hatState & SDL_HAT_LEFT)
    {
        pressed = UniversalControllerButton::DPadLeft;
    }
    else if (hatState & SDL_HAT_RIGHT)
    {
        pressed = UniversalControllerButton::DPadRight;
    }

    return pressed;
}

bool ControllerMapper::IsGivenAxisValueAPressedValueForButton(
        Controller controller, UniversalControllerButton button, int SDLAxis, int axisValue) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {

        FList<ControllerAxisMappedToButton> axisMapped = found[0]->AxisToButton.Where(
            [SDLAxis, button](const ControllerAxisMappedToButton& c)
            { return c.Axis == SDLAxis && c.Button == button; });
        if (axisMapped.Any())
        {
            ControllerAxisMappingEvaluation evaluation = axisMapped[0].Evaluation;
            switch (evaluation.Comparison)
            {
                case ControllerComparisonType::Equals: return axisValue == evaluation.Value;
                case ControllerComparisonType::Greater: return axisValue > evaluation.Value;
                case ControllerComparisonType::Less: return axisValue < evaluation.Value;
            }
        }
    }

    return false;
}