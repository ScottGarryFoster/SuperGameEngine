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
        m_keys.insert_or_assign(keyCode, KeyState::Unpressed);
    }
}

KeyInput::~KeyInput()
{
}

void KeyInput::Update()
{
    for (const KeyCode& keyCode : EKeyCode::ToVector())
    {
        if (EKeyState::HasFlag(m_keys[keyCode], KeyState::Pressed))
        {
            m_keys[keyCode] = KeyState::Down;
        }
        else if (EKeyState::HasFlag(m_keys[keyCode], KeyState::Up))
        {
            m_keys[keyCode] = KeyState::Unpressed;
        }
    }
}

void KeyInput::EventUpdate(WindowEvent event)
{
    KeyCode keyCode = KeyboardKeycodeConversion::FromKeyCode(event.Keyboard.Key.Keycode);
    KeyState keyState = m_keys[keyCode];
    if (event.EventType == WindowEventType::SDL_KEYDOWN)
    {
        if (keyState == KeyState::Unpressed)
        {
            m_keys[keyCode] = KeyState::Down | KeyState::Pressed;
        }
    }
    else if (event.EventType == WindowEventType::SDL_KEYUP)
    {
        if (EKeyState::HasFlag(keyState, KeyState::Down))
        {
            m_keys[keyCode] = KeyState::Up;
        }
    }
}

bool KeyInput::GetKeyDown(const KeyCode& keyCode) const
{
    KeyState keystate = m_keys.at(keyCode);
    return EKeyState::HasFlag(keystate, KeyState::Down);
}

bool KeyInput::GetKeyPressed(const KeyCode& keyCode) const
{
    KeyState keystate = m_keys.at(keyCode);
    return EKeyState::HasFlag(keystate, KeyState::Pressed);
}

bool KeyInput::GetKeyUp(const KeyCode& keyCode) const
{
    KeyState keystate = m_keys.at(keyCode);
    return EKeyState::HasFlag(keystate, KeyState::Up);
}