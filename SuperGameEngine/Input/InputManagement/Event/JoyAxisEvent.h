#pragma once
#include <cstdint>
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_JoyAxisEvent"/> without the SDL.
    /// </summary>
    struct JoyAxisEvent
    {
    public:
        /// <summary>
        /// The types of events that can be delivered.
        /// </summary>
        WindowEventType Type;

        /// <summary>
        /// When the event was triggered in ticks from when SDL was started.
        /// </summary>
        uint32_t Timestamp;

        /// <summary>
        /// The instance ID added or removed.
        /// Use this to get more information on the controller.
        /// </summary>
        int32_t ControllerInstanceID;

        /// <summary>
        /// Axis Index.
        /// </summary>
        uint8_t Axis = -1;

        /// <summary>
        /// The value of the axis.
        /// </summary>
        int16_t Value;
    };
}
