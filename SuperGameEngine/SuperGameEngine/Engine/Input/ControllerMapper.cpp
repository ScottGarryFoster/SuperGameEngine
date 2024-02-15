#include "ControllerMapper.h"

using namespace SuperGameEngine;

ControllerMapper::ControllerMapper(ControllerLayoutCollection* controllerCollection)
{
    if (!controllerCollection)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Construction"),
            FString("controllerCollection is nullptr. Ensure this is given."));
    }

    m_controllerCollection = controllerCollection;
}

UniversalControllerButton ControllerMapper::GetUniversalControllerButtonFromSDLButton(Controller controller, int SDLButton) const
{
    FList<ControllerLayout*>* collection = m_controllerCollection->GetControllerLayouts();
    FList<ControllerLayout*> found =
        collection->Where([controller](const ControllerLayout* c) { return c->Controller == controller; });
    if (found.Any())
    {
        // Controller Layout found.
        FList<std::pair<int, UniversalControllerButton>> buttons = found[0]->SDLToUniversalButton.Where(
            [SDLButton](const std::pair<int, UniversalControllerButton> p) { return p.first == SDLButton; });
        if (buttons.Any())
        {
            // Button found
            return buttons[0].second;
        }

        return UniversalControllerButton::Unknown;
    }

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetUniversalControllerButtonFromSDLButton"),
        FString("Controller mapping not found for ") + EController::ToString(controller));
    return UniversalControllerButton::Unknown;
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

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetSDLButtonsOnController"),
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

    Logger::Exception(NotImplementedException(), GetTypeName(), FString("GetSDLAxisOnController"),
        FString("Controller requested which was not valid. Requested: ") + EController::ToString(controller));
    return -1;
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