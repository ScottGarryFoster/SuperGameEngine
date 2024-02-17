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

    if (ButtonPressed(UniversalControllerButton::FaceButtonDown))
    {
        Logger::Info(FString("0 A FaceButtonDown"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonRight))
    {
        Logger::Info(FString("1 B FaceButtonRight"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonLeft))
    {
        Logger::Info(FString("2 X FaceButtonLeft"));
    }

    if (ButtonPressed(UniversalControllerButton::FaceButtonUp))
    {
        Logger::Info(FString("3 Y FaceButtonUp"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftShoulder))
    {
        Logger::Info(FString("4 LeftShoulder LeftShoulder"));
    }

    if (ButtonPressed(UniversalControllerButton::RightShoulder))
    {
        Logger::Info(FString("5 RightShoulder RightShoulder"));
    }

    if (ButtonPressed(UniversalControllerButton::Select))
    {
        Logger::Info(FString("6 Back Select"));
    }

    if (ButtonPressed(UniversalControllerButton::Start))
    {
        Logger::Info(FString("7 Start Start"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftStickClick))
    {
        Logger::Info(FString("8 LeftThumb LeftStickClick"));
    }

    if (ButtonPressed(UniversalControllerButton::RightStickClick))
    {
        Logger::Info(FString("9 RightThumb RightStickClick"));
    }

    if (ButtonPressed(UniversalControllerButton::LeftTrigger))
    {
        Logger::Info(FString("Axis 4 : LeftTrigger"));
    }

    if (ButtonPressed(UniversalControllerButton::RightTrigger))
    {
        Logger::Info(FString("Axis 5 : RightTrigger"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadDown))
    {
        Logger::Info(FString("DPadDown"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadLeft))
    {
        Logger::Info(FString("DPadLeft"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadRight))
    {
        Logger::Info(FString("DPadRight"));
    }

    if (ButtonPressed(UniversalControllerButton::DPadUp))
    {
        Logger::Info(FString("DPadUp"));
    }

    
    //{
    //    int axis = AxisValue(UniversalControllerAxis::RightTrigger);
    //    Logger::Info(FString("RightTriggerX: ") + axis);
    //}
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
            UniversalControllerAxis universalAxis = 
                m_controllerMapper->GetUniversalAxisFromSDLAxis(controller, axis);
            if (universalAxis != UniversalControllerAxis::Unknown)
            {
                int axisValue = SDL_JoystickGetAxis(joystick, axis);
                auto foundAxis = m_axisValueOnController->find(foundController);
                if (foundAxis == m_axisValueOnController->end())
                {
                    auto newMap = std::map<UniversalControllerAxis, int>();
                    newMap.insert(std::make_pair(universalAxis, axisValue));

                    m_axisValueOnController->insert(std::make_pair(foundController, newMap));
                }
                else
                {
                    int key = foundAxis->first;
                    std::map<UniversalControllerAxis, int> axisMap = foundAxis->second;
                    auto foundExactAxis = axisMap.find(universalAxis);
                    if (foundExactAxis == axisMap.end())
                    {
                        foundAxis->second.insert(std::make_pair(universalAxis, axisValue));
                    }
                    else
                    {
                        foundAxis->second[universalAxis] = axisValue;
                    }
                }

                // This method is an example of why I need a wrapper for Dictionaries like FList
                // To make things cleaner.
                // TODO: [#27] Make a Dictionary / Keypair collection structure
            }
        }

        
    }
}