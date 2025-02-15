#pragma once
#include "HatPosition.h"
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_JoyHatEvent"/> without the SDL.
    /// </summary>
    struct JoyHatEvent
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
        /// The index of the Hat.
        /// This should be mapped from the controller layout.
        /// </summary>
        uint32_t HatIndex;

        /// <summary>
        /// The position of the event upon a hat (dpad generally).
        /// </summary>
        HatPosition Position;
    };
}

