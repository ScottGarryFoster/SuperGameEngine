#include "SuperInputManager.h"

#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/ControllerInput.h"
#include "Engine/KeyInput.h"
#include "Engine/MouseInput.h"

using namespace SuperGameInput;

SuperInputManager::SuperInputManager()
{
    m_keyInput = std::make_shared<KeyInput>();
    m_controllerInput = std::make_shared<ControllerInput>();
    m_mouseInput = std::make_shared<MouseInput>();
}

void SuperInputManager::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_controllerInput->Setup(gamePackage);
}

void SuperInputManager::Update()
{
    m_keyInput->Update();
    m_controllerInput->Update();
    m_mouseInput->Update();
}

void SuperInputManager::EventUpdate(WindowEvent event)
{
    switch (event.EventType)
    {
        case WindowEventType::SDL_KEYDOWN:
        case WindowEventType::SDL_KEYUP:
            m_keyInput->EventUpdate(event);
            break;
        case WindowEventType::SDL_CONTROLLERDEVICEADDED:
        case WindowEventType::SDL_CONTROLLERDEVICEREMOVED:
        case WindowEventType::SDL_JOYBUTTONDOWN:
        case WindowEventType::SDL_JOYBUTTONUP:
        case WindowEventType::SDL_JOYHATMOTION:
        case WindowEventType::SDL_JOYAXISMOTION:
            m_controllerInput->EventUpdate(event);
            break;
        case WindowEventType::SDL_MOUSEBUTTONDOWN:
        case WindowEventType::SDL_MOUSEBUTTONUP:
        case WindowEventType::SDL_MOUSEMOTION:
        case WindowEventType::SDL_MOUSEWHEEL:
        case WindowEventType::SDL_WINDOWEVENT:
            m_mouseInput->EventUpdate(event);
            break;
    }
}

bool SuperInputManager::GetKeyDown(const KeyCode& keyCode) const
{
    return m_keyInput->GetKeyDown(keyCode);
}

bool SuperInputManager::GetKeyPressed(const KeyCode& keyCode) const
{
    return m_keyInput->GetKeyPressed(keyCode);
}

bool SuperInputManager::GetKeyUp(const KeyCode& keyCode) const
{
    return m_keyInput->GetKeyUp(keyCode);
}

bool SuperInputManager::ButtonDown(UniversalControllerButton button) const
{
    return m_controllerInput->ButtonDown(button);
}

bool SuperInputManager::ButtonUp(UniversalControllerButton button) const
{
    return m_controllerInput->ButtonUp(button);
}

bool SuperInputManager::ButtonPressed(UniversalControllerButton button) const
{
    return m_controllerInput->ButtonPressed(button);
}

int SuperInputManager::AxisValue(UniversalControllerAxis axis) const
{
    return m_controllerInput->AxisValue(axis);
}

float SuperInputManager::AxisValueNormalised(UniversalControllerAxis axis) const
{
    return m_controllerInput->AxisValueNormalised(axis);
}

MouseState SuperInputManager::GetMouseState() const
{
    return m_mouseInput->GetMouseState();
}

FPoint SuperInputManager::GetMousePosition() const
{
    return m_mouseInput->GetMousePosition();
}
