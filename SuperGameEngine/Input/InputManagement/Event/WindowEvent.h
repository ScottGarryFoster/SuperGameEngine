#pragma once
#include "KeyboardEvent.h"
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents an SDL Event without the SDL.
    /// </summary>
    struct WindowEvent
    {
    public:
        /// <summary>
        /// The types of events that can be delivered.
        /// </summary>
        WindowEventType EventType;

        /// <summary>
        /// Represents a <see cref="SDL_KeyboardEvent"/> without the SDL.
        /// </summary>
        KeyboardEvent Keyboard;
    };
}


