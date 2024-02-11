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

    m_controllerResolver = new ControllerResolver();
    m_controllerMapper = new ControllerMapper();
}

DirectControllerInput::~DirectControllerInput()
{
    delete m_keyState;
    delete m_keyStateLastFrame;
    delete m_currentState;
    delete m_controllerResolver;
    delete m_controllerMapper;
}

void DirectControllerInput::Update()
{
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

            //int numberOfAxis = m_controllerMapper->GetSDLAxisOnController(controller);
            //int axisValue = SDL_JoystickGetAxis(joystick, 5);
            //Logger::Info(FString("5: ") + axisValue);
            //for (int a = 0; a < numberOfAxis; ++a)
            //{

            //}

            std::vector<std::pair<int, UniversalControllerButton>> buttonsToAxis = 
                m_controllerMapper->GetUniversalControllerButtonMappedToAxis(controller);
            for (std::pair<int, UniversalControllerButton> buttonToAxis : buttonsToAxis)
            {
                int axisValue = SDL_JoystickGetAxis(joystick, buttonToAxis.first);
                if (m_controllerMapper->IsGivenAxisValueAPressedValueForButton(controller, buttonToAxis.second, buttonToAxis.first, axisValue))
                {
                    m_keyState->at(buttonToAxis.second) = true;
               }
            }
        }

        // Do not run for other controllers
        break;
    }
}