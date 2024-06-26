#include "DirectControllerInput.h"

using namespace SuperGameEngine;

DirectControllerInput::DirectControllerInput()
{
    m_keyState = new std::unordered_map<UniversalControllerButton, bool>();
    m_keyStateLastFrame = new std::unordered_map<UniversalControllerButton, bool>();
    m_currentState = new std::unordered_map<UniversalControllerButton, KeyState>();
    for (UniversalControllerButton key : EUniversalControllerButton::ToVector())
    {
        m_keyState->insert(std::make_pair(key, false));
        m_keyStateLastFrame->insert(std::make_pair(key, false));
        m_currentState->insert(std::make_pair(key, KeyState::Unpressed));
    }

    m_controllerLayoutCollection = new ControllerLayoutCollection();
    m_controllerResolver = new ControllerResolver(m_controllerLayoutCollection);
    m_controllerMapper = new ControllerMapper(m_controllerLayoutCollection);

    m_axisValueOnController = new std::map<int, std::map<UniversalControllerAxis, int>>();
}

DirectControllerInput::~DirectControllerInput()
{
    delete m_keyState;
    delete m_keyStateLastFrame;
    delete m_currentState;
    delete m_controllerResolver;
    delete m_controllerMapper;
    delete m_controllerLayoutCollection;
}

void DirectControllerInput::Update()
{
    UpdateAxisValue();
    UpdateKeyState(m_keyState);

    for (UniversalControllerButton button : EUniversalControllerButton::ToVector())
    {
        if (m_keyState->at(button) && m_keyStateLastFrame->at(button))
        {
            m_currentState->at(button) = KeyState::Down;
        }
        else if (m_keyState->at(button) && !m_keyStateLastFrame->at(button))
        {
            m_currentState->at(button) = KeyState::Down;
            m_currentState->at(button) |= KeyState::Pressed;
        }
        else if (!m_keyState->at(button) && m_keyStateLastFrame->at(button))
        {
            m_currentState->at(button) = KeyState::Up;
        }
        else if (!m_keyState->at(button) && !m_keyStateLastFrame->at(button))
        {
            m_currentState->at(button) = KeyState::Unpressed;
        }
    }

    UpdateKeyState(m_keyStateLastFrame);

    // Used for testing.
    //Tester();
}

bool DirectControllerInput::ButtonDown(UniversalControllerButton button) const
{
    return m_currentState->at(button) == (KeyState::Unpressed | KeyState::Down);
}

bool DirectControllerInput::ButtonUp(UniversalControllerButton button) const
{
    return m_currentState->at(button) == (KeyState::Unpressed | KeyState::Up);
}

bool DirectControllerInput::ButtonPressed(UniversalControllerButton button) const
{
    return m_currentState->at(button) == (KeyState::Down | KeyState::Pressed);
}

int DirectControllerInput::AxisValue(UniversalControllerAxis axis) const
{
    auto controllerValues = m_axisValueOnController->find(0);
    if (controllerValues == m_axisValueOnController->end())
    {
        return 0;
    }

    std::map<UniversalControllerAxis, int> axisMap = controllerValues->second;
    auto axisValue = axisMap.find(axis);
    if (axisValue != axisMap.end())
    {
        return axisValue->second;
    }

    return 0;
}

Controller SuperGameEngine::DirectControllerInput::GetCurrentController() const
{
    int numJoysticks = SDL_NumJoysticks();
    for (int j = 0; j < numJoysticks; ++j)
    {
        SDL_Joystick* joystick = SDL_JoystickOpen(j);
        Controller controller = m_controllerResolver->GetControllerFromJoyStick(joystick);
        if (controller != Controller::Unknown)
        {
            return controller;
        }
    }

    return Controller::Unknown;
}

void DirectControllerInput::UpdateKeyState(std::unordered_map<UniversalControllerButton, bool>* statesToUpdate)
{
    for (UniversalControllerButton key : EUniversalControllerButton::ToVector())
    {
        m_keyState->at(key) = false;
    }

    int numJoysticks = SDL_NumJoysticks();
    for (int j = 0; j < numJoysticks; ++j)
    {
        // For some reason Closing the joystick breaks everything.
        // Look into openning joystick on connect maybe?
        // Either way SDL appears to handle this resource well.
        SDL_Joystick* joystick = SDL_JoystickOpen(j);
        Controller controller = m_controllerResolver->GetControllerFromJoyStick(joystick);
        if (controller == Controller::Unknown)
        {
            continue;
        }

        int numberOfButtons = m_controllerMapper->GetSDLButtonsOnController(controller);
        for (int b = 0; b < numberOfButtons; ++b)
        {
            UniversalControllerButton universalButton =
                m_controllerMapper->GetUniversalControllerButtonFromSDLButton(controller, b);
            if (SDL_JoystickGetButton(joystick, b))
            {
                if (universalButton == UniversalControllerButton::Unknown)
                {
                    Logger::Info(FString("Unknown was pressed. Index: ") + b);
                }
                else
                {
                    m_keyState->at(universalButton) = true;
                }
            }
        }

        std::vector<std::pair<int, UniversalControllerButton>> buttonsToAxis = 
            m_controllerMapper->GetUniversalControllerButtonMappedToAxis(controller);
        for (std::pair<int, UniversalControllerButton> buttonToAxis : buttonsToAxis)
        {
            int axisValue = SDL_JoystickGetAxis(joystick, buttonToAxis.first);
            if (m_controllerMapper->IsGivenAxisValueAPressedValueForButton(
                controller, buttonToAxis.second, buttonToAxis.first, axisValue))
            {
                m_keyState->at(buttonToAxis.second) = true;
            }
        }

        int hat = m_controllerMapper->GetSDLHatMappedToDPad(controller);
        if (hat > -1)
        {
            UniversalControllerButton dpadButton =
                m_controllerMapper->GetHatStateMappedToDPad(SDL_JoystickGetHat(joystick, hat));
                
            // It is important that we only claim these as release if a hat is mapped
            // as sometimes buttons are mapped not hats.
            m_keyState->at(UniversalControllerButton::DPadDown) = false;
            m_keyState->at(UniversalControllerButton::DPadLeft) = false;
            m_keyState->at(UniversalControllerButton::DPadRight) = false;
            m_keyState->at(UniversalControllerButton::DPadUp) = false;

            if (dpadButton != UniversalControllerButton::Unknown)
            {
                m_keyState->at(dpadButton) = true;
            }
        }

        // Do not run for other controllers
        break;
    }
}

void DirectControllerInput::UpdateAxisValue()
{
    int foundController = -1;
    int numJoysticks = SDL_NumJoysticks();
    for (int j = 0; j < numJoysticks; ++j)
    {
        SDL_Joystick* joystick = SDL_JoystickOpen(j);
        Controller controller = m_controllerResolver->GetControllerFromJoyStick(joystick);
        if (controller == Controller::Unknown)
        {
            continue;
        }
        ++foundController;

        for (int axis = 0; axis < m_controllerMapper->GetSDLAxisOnController(controller); ++axis)
        {
            AxisToUniversalAxis axisMapping =
                m_controllerMapper->GetUniversalAxisMapping(controller, axis);
            if (axisMapping.UniversalAxis != UniversalControllerAxis::Unknown)
            {
                int axisValue = SDL_JoystickGetAxis(joystick, axis);
                if (axisMapping.HasDeadzone && 
                    AxisValueIsInDeadzone(axisValue, axisMapping.Deadzone))
                {
                    axisValue = 0;
                }

                auto foundAxis = m_axisValueOnController->find(foundController);
                if (foundAxis == m_axisValueOnController->end())
                {
                    auto newMap = std::map<UniversalControllerAxis, int>();
                    newMap.insert(std::make_pair(axisMapping.UniversalAxis, axisValue));

                    m_axisValueOnController->insert(std::make_pair(foundController, newMap));
                }
                else
                {
                    int key = foundAxis->first;
                    std::map<UniversalControllerAxis, int> axisMap = foundAxis->second;
                    auto foundExactAxis = axisMap.find(axisMapping.UniversalAxis);
                    if (foundExactAxis == axisMap.end())
                    {
                        foundAxis->second.insert(std::make_pair(axisMapping.UniversalAxis, axisValue));
                    }
                    else
                    {
                        foundAxis->second[axisMapping.UniversalAxis] = axisValue;
                    }
                }

                // This method is an example of why I need a wrapper for Dictionaries like FList
                // To make things cleaner.
                // TODO: [#27] Make a Dictionary / Keypair collection structure
            }
        }
    }
}

bool DirectControllerInput::AxisValueIsInDeadzone(int axisValue, int deadzone) const
{
    return std::abs(axisValue) <= deadzone;
}

void DirectControllerInput::Tester() const
{
    if (ButtonPressed(UniversalControllerButton::FaceButtonRight))
    {
        Logger::Info(FString("0 A FaceButtonRight"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonDown))
    {
        Logger::Info(FString("1 B FaceButtonDown"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonUp))
    {
        Logger::Info(FString("2 X FaceButtonUp"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonLeft))
    {
        Logger::Info(FString("3 Y FaceButtonLeft"));
    }

    if (ButtonPressed(UniversalControllerButton::Select))
    {
        Logger::Info(FString("4 LeftShoulder Select"));
    }

    if (ButtonPressed(UniversalControllerButton::Start))
    {
        Logger::Info(FString("6 RightShoulder Start"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftStickClick))
    {
        Logger::Info(FString("7 Back LeftStickClick"));
    }

    if (ButtonPressed(UniversalControllerButton::RightStickClick))
    {
        Logger::Info(FString("8 Start RightStickClick"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftShoulder))
    {
        Logger::Info(FString("9 LeftThumb LeftShoulder"));
    }

    if (ButtonPressed(UniversalControllerButton::RightShoulder))
    {
        Logger::Info(FString("10 RightThumb RightShoulder"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadUp))
    {
        Logger::Info(FString("11 : DPadUp"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadDown))
    {
        Logger::Info(FString("12 : DPadDown"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadLeft))
    {
        Logger::Info(FString("13: DPadLeft"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadRight))
    {
        Logger::Info(FString("5: DPadRight"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftTrigger))
    {
        Logger::Info(FString("4: LeftTrigger"));
    }

    if (ButtonPressed(UniversalControllerButton::RightTrigger))
    {
        Logger::Info(FString("5: RightTrigger"));
    }


    {
        int axisX = AxisValue(UniversalControllerAxis::LeftStickX);
        int axisY = AxisValue(UniversalControllerAxis::LeftStickY);
        int axisXRight = AxisValue(UniversalControllerAxis::RightStickX);
        int axisYRight = AxisValue(UniversalControllerAxis::RightStickY);
        Logger::Info(
            FString("L(") + axisX + FString(",") + axisY + FString(")") +
            FString(" R(") + axisXRight + FString(",") + axisYRight + FString(")"));
    }
}
