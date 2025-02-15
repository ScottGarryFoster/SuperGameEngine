#pragma once
#include "ControllerDeviceEvent.h"
#include "JoyAxisEvent.h"
#include "JoyButtonEvent.h"
#include "JoyHatEvent.h"
#include "JoystickDeviceEvent.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "WindowEventType.h"
#include "WindowUpdateEvent.h"

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
        /// Represents a <see cref="SDL_WindowEvent"/> without the SDL.
        /// </summary>
        WindowUpdateEvent WindowUpdate;

        /// <summary>
        /// Represents a <see cref="SDL_KeyboardEvent"/> without the SDL.
        /// </summary>
        KeyboardEvent Keyboard;

        /// <summary>
        /// Represents a <see cref="SDL_JoyDeviceEvent"/> without the SDL.
        /// </summary>
        JoystickDeviceEvent JoystickDevice;

        /// <summary>
        /// Represents a <see cref="SDL_JoyButtonEvent"/> without the SDL.
        /// </summary>
        JoyButtonEvent JoyButton;

        /// <summary>
        /// Represents a <see cref="SDL_JoyHatEvent"/> without the SDL.
        /// </summary>
        JoyHatEvent JoyHat;

        /// <summary>
        /// Represents a <see cref="SDL_JoyAxisEvent"/> without the SDL.
        /// </summary>
        JoyAxisEvent JoyAxis;

        /// <summary>
        /// Represents a <see cref="SDL_ControllerDeviceEvent"/> without the SDL.
        /// </summary>
        ControllerDeviceEvent ControllerDevice;

        /// <summary>
        /// Represents a <see cref="SDL_MouseButtonEvent"/> without the SDL.
        /// </summary>
        MouseButtonEvent MouseButton;

        /// <summary>
        /// Represents a <see cref="SDL_MouseMotionEvent"/> without the SDL.
        /// </summary>
        MouseMotionEvent MouseMotion;
    };
}


