#include "KeyInput.h"
#include "KeyboardKeycodeConversion.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameInput;
using namespace FatedQuestLibraries;

KeyInput::KeyInput()
{
    std::vector<KeyCode> keyCodes = EKeyCode::ToVector();
    for (const KeyCode& keyCode : keyCodes)
    {
        m_keys.insert_or_assign(keyCode, KeyOrButtonState::Unpressed);
    }
}

KeyInput::~KeyInput()
{
}

void KeyInput::Update()
{
    for (const KeyCode& keyCode : EKeyCode::ToVector())
    {
        if (EKeyOrButtonState::HasFlag(m_keys[keyCode], KeyOrButtonState::Pressed))
        {
            m_keys[keyCode] = KeyOrButtonState::Down;
        }
        else if (EKeyOrButtonState::HasFlag(m_keys[keyCode], KeyOrButtonState::Up))
        {
            m_keys[keyCode] = KeyOrButtonState::Unpressed;
        }
    }
}

void KeyInput::EventUpdate(WindowEvent event)
{
    KeyCode keyCode = KeyboardKeycodeConversion::FromKeyCode(event.Keyboard.Key.Keycode);
    KeyOrButtonState keyState = m_keys[keyCode];
    if (event.EventType == WindowEventType::SDL_KEYDOWN)
    {
        if (keyState == KeyOrButtonState::Unpressed)
        {
            m_keys[keyCode] = KeyOrButtonState::Down | KeyOrButtonState::Pressed;
        }
    }
    else if (event.EventType == WindowEventType::SDL_KEYUP)
    {
        if (EKeyOrButtonState::HasFlag(keyState, KeyOrButtonState::Down))
        {
            m_keys[keyCode] = KeyOrButtonState::Up;
        }
    }
}

bool KeyInput::GetKeyDown(const KeyCode& keyCode) const
{
    KeyOrButtonState keyState = m_keys.at(keyCode);
    return EKeyOrButtonState::HasFlag(keyState, KeyOrButtonState::Down);
}

bool KeyInput::GetKeyPressed(const KeyCode& keyCode) const
{
    KeyOrButtonState keyState = m_keys.at(keyCode);
    return EKeyOrButtonState::HasFlag(keyState, KeyOrButtonState::Pressed);
}

bool KeyInput::GetKeyUp(const KeyCode& keyCode) const
{
    KeyOrButtonState keyState = m_keys.at(keyCode);
    return EKeyOrButtonState::HasFlag(keyState, KeyOrButtonState::Up);
}