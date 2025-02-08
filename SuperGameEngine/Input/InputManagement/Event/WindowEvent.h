#pragma once
#include "ControllerDeviceEvent.h"
#include "JoystickDeviceEvent.h"
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

        /// <summary>
        /// Represents a <see cref="SDL_JoyDeviceEvent"/> without the SDL.
        /// </summary>
        JoystickDeviceEvent JoystickDevice;

        /// <summary>
        /// Represents a <see cref="SDL_ControllerDeviceEvent"/> without the SDL.
        /// </summary>
        ControllerDeviceEvent ControllerDevice;
    };
}


