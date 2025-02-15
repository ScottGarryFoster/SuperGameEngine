#pragma once
#include <cstdint>

#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_JoyButtonEvent"/> without the SDL.
    /// </summary>
    struct JoyButtonEvent
    {
    public:
        /// <summary>
        /// The types of events that can be delivered.
        /// </summary>
        WindowEventType Type;

        /// <summary>
        /// Ticks since SDL was launched.
        /// </summary>
        uint32_t Timestamp;

        /// <summary>
        /// Controller/Joystick Instance ID. Unique to each device.
        /// </summary>
        int32_t InstanceID;

        /// <summary>
        /// The button number this button represents.
        /// </summary>
        uint32_t Button;
    };
}
