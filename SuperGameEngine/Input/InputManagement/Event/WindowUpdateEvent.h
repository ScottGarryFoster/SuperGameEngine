#pragma once
#include "WindowEventType.h"
#include "WindowUpdateEventID.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_WindowEvent"/> without the SDL.
    /// </summary>
    struct WindowUpdateEvent
    {
    public:
        /// <summary>
        /// The types of events that can be delivered.
        /// </summary>
        WindowEventType EventType;

        /// <summary>
        /// When the event was triggered in ticks from when SDL was started.
        /// </summary>
        uint32_t Timestamp;

        /// <summary>
        /// The window.
        /// </summary>
        uint32_t Window;

        /// <summary>
        /// Event subtype for window events
        /// </summary>
        WindowUpdateEventID EventID;
    };
}
