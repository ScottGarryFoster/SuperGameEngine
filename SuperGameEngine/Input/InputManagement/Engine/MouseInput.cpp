#include "MouseInput.h"

#include <ranges>

using namespace SuperGameInput;

MouseInput::MouseInput()
{
    m_instanceToUse = m_invalidInstanceID;
    m_defaultState = CreateBaseState();
}

MouseInput::~MouseInput()
{
}

void MouseInput::Update()
{
    for (const std::pair<const uint32_t, MouseState>& pairState : m_mice)
    {
        for (const MouseButton& keyCode : EMouseButton::ToVector())
        {
            if (EKeyOrButtonState::HasFlag(pairState.second.ButtonState.at(keyCode), KeyOrButtonState::Pressed))
            {
                m_mice.at(pairState.first).ButtonState.at(keyCode) = KeyOrButtonState::Down;
            }
            else if (EKeyOrButtonState::HasFlag(pairState.second.ButtonState.at(keyCode), KeyOrButtonState::Up))
            {
                m_mice.at(pairState.first).ButtonState.at(keyCode) = KeyOrButtonState::Unpressed;
            }
        }
    }

}

void MouseInput::EventUpdate(WindowEvent event)
{
    switch (event.EventType)
    {
    case WindowEventType::SDL_MOUSEBUTTONDOWN:
    case WindowEventType::SDL_MOUSEBUTTONUP:
    //case WindowEventType::SDL_MOUSEMOTION:
    //case WindowEventType::SDL_MOUSEWHEEL:
        UpdateMiceFromMouseButtonEvent(event.MouseButton);
        break;
    }
}

MouseState MouseInput::GetMouseState() const
{
    if (m_mice.empty())
    {
        return m_defaultState;
    }

    if (m_instanceToUse != 4294967295)
    {
        if (m_mice.contains(m_instanceToUse))
        {
            return m_mice.at(m_instanceToUse);
        }
    }

    for (const auto& val : m_mice | std::views::values)
    {
        return val;
    }

    return m_defaultState;
}

void MouseInput::UpdateMiceFromMouseButtonEvent(const MouseButtonEvent& event)
{
    EnsureInstanceIsCreated(event.InstanceID);

    m_mice.at(event.InstanceID).X = event.X;
    m_mice.at(event.InstanceID).Y = event.Y;

    // Handle clicks in here but this is probably going to need to be done differently.
    // As clicks are likely going to need to be a boolean thing.

    KeyOrButtonState keyState = m_mice.at(event.InstanceID).ButtonState.at(event.Button);
    if (event.Type == WindowEventType::SDL_MOUSEBUTTONDOWN)
    {
        if (keyState == KeyOrButtonState::Unpressed)
        {
            m_mice.at(event.InstanceID).ButtonState.at(event.Button) = KeyOrButtonState::Down | KeyOrButtonState::Pressed;
        }
    }
    else if (event.Type == WindowEventType::SDL_MOUSEBUTTONUP)
    {
        if (EKeyOrButtonState::HasFlag(keyState, KeyOrButtonState::Down))
        {
            m_mice.at(event.InstanceID).ButtonState.at(event.Button) = KeyOrButtonState::Up | KeyOrButtonState::Unpressed;
        }
    }

    m_instanceToUse = event.InstanceID;
}

void MouseInput::EnsureInstanceIsCreated(uint32_t instanceID)
{
    if (!m_mice.contains(instanceID))
    {
        m_mice.try_emplace(instanceID, CreateBaseState());
    }
}

MouseState MouseInput::CreateBaseState()
{
    auto mouseState = MouseState();
    mouseState.ButtonState.try_emplace(MouseButton::Left, KeyOrButtonState::Unpressed);
    mouseState.ButtonState.try_emplace(MouseButton::Right, KeyOrButtonState::Unpressed);
    mouseState.ButtonState.try_emplace(MouseButton::Middle, KeyOrButtonState::Unpressed);
    mouseState.ButtonState.try_emplace(MouseButton::Back, KeyOrButtonState::Unpressed);
    mouseState.ButtonState.try_emplace(MouseButton::Forward, KeyOrButtonState::Unpressed);
    mouseState.X = -1;
    mouseState.Y = -1;

    return mouseState;
}