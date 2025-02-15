#pragma once
#include <cstdint>
#include <string>

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_JoyDeviceEvent"/> without the SDL.
    /// </summary>
    /// <remarks>The better struct to use is <see cref="ControllerDeviceEvent" and those events. </remarks>
    struct JoystickDeviceEvent
    {
    public:
        /// <summary>
        /// When the event was triggered in ticks from when SDL was started.
        /// </summary>
        uint32_t Timestamp;

        /// <summary>
        /// The instance ID added or removed.
        /// Use this to get more information on the joystick.
        /// </summary>
        int32_t JoystickInstanceID;
    };
}


