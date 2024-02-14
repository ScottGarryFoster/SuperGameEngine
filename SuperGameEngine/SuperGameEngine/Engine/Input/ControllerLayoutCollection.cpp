#include "../../LibraryIncludes.h"

#include "ControllerLayoutCollection.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;

ControllerLayoutCollection::ControllerLayoutCollection()
{
    m_controllerLayout = new FList<ControllerLayout*>();
    m_controllerLayout->Add(ReturnXboxPadLayout());
    m_controllerLayout->Add(ReturnXboxPadLayout(true));
    m_controllerLayout->Add(ReturnSwitchProLayout());
}

ControllerLayoutCollection::~ControllerLayoutCollection()
{
    for (ControllerLayout* layout : *m_controllerLayout)
    {
        delete layout;
    }
    delete m_controllerLayout;
}

FList<ControllerLayout*>* ControllerLayoutCollection::GetControllerLayouts()
{
    return m_controllerLayout;
}

ControllerLayout* ControllerLayoutCollection::ReturnXboxPadLayout(bool xboxOne)
{
    ControllerLayout* xbox360 = new ControllerLayout();
    if (xboxOne)
    {
        xbox360->Controller = Controller::XboxSeriesController;
        xbox360->Name = FString("Controller (Xbox One For Windows)");
        xbox360->Buttons = 16;
        xbox360->Axis = 6;
    }
    else
    {
        xbox360->Controller = Controller::Xbox360Controller;
        xbox360->Name = FString("Xbox 360 Controller");
        xbox360->Buttons = 11;
        xbox360->Axis = 6;
    }


    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (0, UniversalControllerButton::FaceButtonDown));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (1, UniversalControllerButton::FaceButtonRight));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (2, UniversalControllerButton::FaceButtonLeft));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (3, UniversalControllerButton::FaceButtonUp));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (4, UniversalControllerButton::LeftShoulder));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (5, UniversalControllerButton::RightShoulder));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (6, UniversalControllerButton::Select));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (7, UniversalControllerButton::Start));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (8, UniversalControllerButton::LeftStickClick));
    xbox360->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (9, UniversalControllerButton::RightStickClick));

    ControllerAxisMappedToButton leftTrigger = ControllerAxisMappedToButton();
    leftTrigger.Axis = 4;
    leftTrigger.Button = UniversalControllerButton::LeftTrigger;
    leftTrigger.Evaluation = ControllerAxisMappingEvaluation();
    leftTrigger.Evaluation.Comparison = ControllerComparisonType::Greater;
    leftTrigger.Evaluation.Value = -30000;

    ControllerAxisMappedToButton rightTrigger = ControllerAxisMappedToButton();
    rightTrigger.Axis = 5;
    rightTrigger.Button = UniversalControllerButton::RightTrigger;
    rightTrigger.Evaluation = ControllerAxisMappingEvaluation();
    rightTrigger.Evaluation.Comparison = ControllerComparisonType::Greater;
    rightTrigger.Evaluation.Value = -30000;

    xbox360->AxisToButton.Add(leftTrigger);
    xbox360->AxisToButton.Add(rightTrigger);

    return xbox360;
}

ControllerLayout* ControllerLayoutCollection::ReturnSwitchProLayout()
{
    ControllerLayout* controller = new ControllerLayout();
    controller->Controller = Controller::NintendoSwitchProController;
    controller->Name = FString("Nintendo Switch Pro Controller");
    controller->Buttons = 20;
    controller->Axis = 6;

    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (0, UniversalControllerButton::FaceButtonRight));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (1, UniversalControllerButton::FaceButtonDown));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (2, UniversalControllerButton::FaceButtonUp));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (3, UniversalControllerButton::FaceButtonLeft));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (4, UniversalControllerButton::Select));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (6, UniversalControllerButton::Start));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (7, UniversalControllerButton::LeftStickClick));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (8, UniversalControllerButton::RightStickClick));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (9, UniversalControllerButton::LeftShoulder));
    controller->SDLToUniversalButton.Add(std::pair<int, UniversalControllerButton>
        (10, UniversalControllerButton::RightShoulder));

    ControllerAxisMappedToButton leftTrigger = ControllerAxisMappedToButton();
    leftTrigger.Axis = 4;
    leftTrigger.Button = UniversalControllerButton::LeftTrigger;
    leftTrigger.Evaluation = ControllerAxisMappingEvaluation();
    leftTrigger.Evaluation.Comparison = ControllerComparisonType::Equals;
    leftTrigger.Evaluation.Value = 32767;

    ControllerAxisMappedToButton rightTrigger = ControllerAxisMappedToButton();
    rightTrigger.Axis = 5;
    rightTrigger.Button = UniversalControllerButton::RightTrigger;
    rightTrigger.Evaluation = ControllerAxisMappingEvaluation();
    rightTrigger.Evaluation.Comparison = ControllerComparisonType::Equals;
    rightTrigger.Evaluation.Value = 32767;

    controller->AxisToButton.Add(leftTrigger);
    controller->AxisToButton.Add(rightTrigger);

    return controller;
}
