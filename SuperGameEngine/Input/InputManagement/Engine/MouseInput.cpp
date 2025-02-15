#include "MouseInput.h"

#include "../../FatedQuestLibraries.h"
#include <ranges>
#include <stdexcept>

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
        UpdateMiceFromMouseButtonEvent(event.MouseButton);
        break;
    case WindowEventType::SDL_MOUSEMOTION:
        UpdateMiceFromMouseMotionEvent(event.MouseMotion);
        break;
    case WindowEventType::SDL_WINDOWEVENT:
        UpdateMiceWhenMouseHasLeftOrReturned(event.WindowUpdate);
        break;
    case WindowEventType::SDL_MOUSEWHEEL:
        UpdateMiceForWheelPosition(event.MouseWheel);
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

FPoint MouseInput::GetMousePosition() const
{
    auto defaultPoint = FPoint(-1, -1);
    if (m_mice.empty())
    {
        return defaultPoint;
    }

    if (m_instanceToUse != 4294967295)
    {
        if (m_mice.contains(m_instanceToUse))
        {
            return {m_mice.at(m_instanceToUse).X, m_mice.at(m_instanceToUse).Y};
        }
    }

    for (const auto& val : m_mice | std::views::values)
    {
        return {val.X, val.Y};
    }

    return defaultPoint;
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

void MouseInput::UpdateMiceFromMouseMotionEvent(const MouseMotionEvent& event)
{
    EnsureInstanceIsCreated(event.InstanceID);

    m_mice.at(event.InstanceID).X = event.X;
    m_mice.at(event.InstanceID).Y = event.Y;
}

void MouseInput::UpdateMiceWhenMouseHasLeftOrReturned(const WindowUpdateEvent& event)
{
    if (event.EventID == WindowUpdateEventID::SDL_WINDOWEVENT_LEAVE)
    {
        for (const auto& val : m_mice | std::views::keys)
        {
            m_mice.at(val).X = -1;
            m_mice.at(val).Y = -1;
        }
    }
}

void MouseInput::UpdateMiceForWheelPosition(const MouseWheelEvent& event)
{
    EnsureInstanceIsCreated(event.InstanceID);

    m_mice.at(event.InstanceID).X = event.MouseX;
    m_mice.at(event.InstanceID).Y = event.MouseY;

    if (event.Direction == MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL)
    {
        m_mice.at(event.InstanceID).WheelX = event.X;
        m_mice.at(event.InstanceID).WheelY = event.Y;
    }
    else
    {
        m_mice.at(event.InstanceID).WheelX = -event.X;
        m_mice.at(event.InstanceID).WheelY = -event.Y;
    }

    try
    {
        m_mice.at(event.InstanceID).ConsistentWheelX = 
            IntHelpers::SafeAddition(m_mice.at(event.InstanceID).ConsistentWheelX, event.X);
        m_mice.at(event.InstanceID).ConsistentWheelY = 
            IntHelpers::SafeAddition(m_mice.at(event.InstanceID).ConsistentWheelY, event.Y);
    }
    catch (const std::overflow_error& e)
    {
        std::string what = e.what();
        Log::Error("ConsistentWheelX or ConsistentWheelY overflowed. " + what,
            "MouseInput::UpdateMiceForWheelPosition(const MouseWheelEvent)");
    }
    catch (const std::exception& e)
    {
        std::string what = e.what();
        Log::Error("Caught an unknown exception! " + what,
            "MouseInput::UpdateMiceForWheelPosition(const MouseWheelEvent)");
    }
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
    mouseState.WheelY = 0;
    mouseState.WheelX = 0;
    mouseState.ConsistentWheelX = 0;
    mouseState.ConsistentWheelY = 0;

    return mouseState;
}