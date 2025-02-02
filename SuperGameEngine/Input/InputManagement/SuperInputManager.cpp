#include "SuperInputManager.h"

#include "../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/ControllerInput.h"
#include "Engine/KeyInput.h"

using namespace SuperGameInput;

SuperInputManager::SuperInputManager()
{
    m_keyInput = std::make_shared<KeyInput>();
    m_controllerInput = std::make_shared<ControllerInput>();
}

void SuperInputManager::Setup(const std::shared_ptr<GamePackage>& gamePackage)
{
    m_controllerInput->Setup(gamePackage);
}

void SuperInputManager::Update()
{
    m_keyInput->Update();
}

void SuperInputManager::EventUpdate(WindowEvent event)
{
    switch (event.EventType)
    {
        case WindowEventType::SDL_KEYDOWN:
        case WindowEventType::SDL_KEYUP:
            m_keyInput->EventUpdate(event);
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