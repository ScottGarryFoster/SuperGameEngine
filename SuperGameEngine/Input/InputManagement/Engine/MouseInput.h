#pragma once
#include <unordered_map>

#include "MouseState.h"
#include "../Event/WindowEvent.h"
#include "../../FatedQuestLibraries.h"

using namespace FatedQuestLibraries;

namespace SuperGameInput
{
    /// <summary>
    /// Handles input for Mouse buttons and location.
    /// </summary>
    class MouseInput
    {
    public:
        MouseInput();
        virtual ~MouseInput();

        /// <summary>
        /// Called once after Tools or Game to reset states of keys.
        /// </summary>
        virtual void Update();

        /// <summary>
        /// Called upon every event to handle key and controller changes.
        /// </summary>
        /// <param name="event">Event to inspect. </param>
        virtual void EventUpdate(WindowEvent event);

        /// <summary>
        /// Describes the state of a mouse, where it is, what button is pressed.
        /// Technically you can have more than one mouse, this will be the last mouse that had an event.
        /// </summary>
        /// <returns>The state of a mouse. </returns>
        virtual MouseState GetMouseState() const;

        /// <summary>
        /// Gets the current mouse position.
        /// This will be the last mouse to click position.
        /// </summary>
        /// <returns>The position of the current mouse. </returns>
        virtual FPoint GetMousePosition() const;

    private:
        /// <summary>
        /// Instance ID which is set when invalid.
        /// This is the default value for instance to use.
        /// </summary>
        uint32_t m_invalidInstanceID = 4294967295;

        /// <summary>
        /// All mice states.
        /// </summary>
        std::unordered_map<uint32_t, MouseState> m_mice;

        /// <summary>
        /// Instance to use on get.
        /// If 4294967295 the first found will be used.
        /// </summary>
        uint32_t m_instanceToUse;

        /// <summary>
        /// State used when nothing is found.
        /// </summary>
        MouseState m_defaultState;

        /// <summary>
        /// Update the mouse state on a button click.
        /// </summary>
        /// <param name="event">Mouse button event. </param>
        void UpdateMiceFromMouseButtonEvent(const MouseButtonEvent& event);

        /// <summary>
        /// Update mouse position from motion event.
        /// </summary>
        /// <param name="event">Mouse motion event. </param>
        void UpdateMiceFromMouseMotionEvent(const MouseMotionEvent& event);

        /// <summary>
        /// Update the X and Y positions when the mouse leaves the window.
        /// </summary>
        /// <param name="event">Window Update event. </param>
        void UpdateMiceWhenMouseHasLeftOrReturned(const WindowUpdateEvent& event);

        /// <summary>
        /// Update the mouse wheel position.
        /// </summary>
        /// <param name="event">Mouse wheel event. </param>
        void UpdateMiceForWheelPosition(const MouseWheelEvent& event);

        /// <summary>
        /// Ensures mouse is found in <see cref="m_mice"/>.
        /// </summary>
        /// <param name="instanceID">Instance to add. </param>
        void EnsureInstanceIsCreated(uint32_t instanceID);

        /// <summary>
        /// Create an empty Mouse State.
        /// </summary>
        /// <returns>Empty mouse state.</returns>
        MouseState CreateBaseState();
    };
}