#include <SDL.h>

#include "DirectKeyInput.h"
#include "../../LibraryIncludes.h"
#include "InputKeyCode.hpp"

using namespace SuperGameEngine;
DirectKeyInput::DirectKeyInput()
{
    m_keyState = new std::unordered_map<InputKeyCode, bool>();
    m_keyStateLastFrame = new std::unordered_map<InputKeyCode, bool>();
    m_currentState = new std::unordered_map<InputKeyCode, KeyState>();
    for (InputKeyCode key : EInputKeyCode::ToVector())
    {
        m_keyState->insert(std::make_pair(key, false));
        m_keyStateLastFrame->insert(std::make_pair(key, false));
        m_currentState->insert(std::make_pair(key, KeyState::Unpressed));
    }
}

DirectKeyInput::~DirectKeyInput()
{
    delete m_keyState;
    delete m_keyStateLastFrame;
}

void DirectKeyInput::EventUpdate(SDL_Event& e)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    UpdateKeyState(currentKeyStates, m_keyState);

    for (InputKeyCode key : EInputKeyCode::ToVector())
    {
        if (m_keyState->at(key) && m_keyStateLastFrame->at(key))
        {
            m_currentState->at(key) = KeyState::Down;
        }
        else if (m_keyState->at(key) && !m_keyStateLastFrame->at(key))
        {
            m_currentState->at(key) = KeyState::Down;
            m_currentState->at(key) |= KeyState::Pressed;
        }
        else if (!m_keyState->at(key) && m_keyStateLastFrame->at(key))
        {
            m_currentState->at(key) = KeyState::Up;
        }
        else if (!m_keyState->at(key) && !m_keyStateLastFrame->at(key))
        {
            m_currentState->at(key) = KeyState::Unpressed;
        }
    }

    UpdateKeyState(currentKeyStates, m_keyStateLastFrame);
}

bool DirectKeyInput::KeyDown(InputKeyCode key) const
{
    return m_currentState->at(key) == (KeyState::Unpressed | KeyState::Down);
}

bool DirectKeyInput::KeyPressed(InputKeyCode key) const
{
    return m_currentState->at(key) == (KeyState::Down | KeyState::Pressed);
}

bool DirectKeyInput::KeyUp(InputKeyCode key) const
{
    return m_currentState->at(key) == (KeyState::Unpressed | KeyState::Up);
}

void DirectKeyInput::UpdateKeyState(const Uint8* keyboardStates, std::unordered_map<InputKeyCode, bool>* statesToUpdate)
{
    for (InputKeyCode key : EInputKeyCode::ToVector())
    {
        SDL_Scancode scanCode = EInputKeyCode::ToSDLScanKeycode(key);
        if (scanCode != SDL_SCANCODE_UNKNOWN)
        {
            statesToUpdate->at(key) = keyboardStates[scanCode];
        }
    }
}