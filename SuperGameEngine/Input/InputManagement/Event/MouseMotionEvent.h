#pragma once
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_MouseMotionEvent"/> without the SDL.
    /// </summary>
    struct MouseMotionEvent
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
        /// The window with mouse focus, if any
        /// </summary>
        uint32_t Window;

        /// <summary>
        /// The mouse instance id.
        /// Use 'IsTouch' before using this as touch will not provide an instance.
        /// </summary>
        uint32_t InstanceID;

        /// <summary>
        /// Position X relative to the window.
        /// </summary>
        int32_t X;

        /// <summary>
        /// Position Y relative to the window.
        /// </summary>
        int32_t Y;

        /// <summary>
        /// Relative X movement.
        /// </summary>
        int32_t RelativeX;

        /// <summary>
        /// Relative Y movement.
        /// </summary>
        int32_t RelativeY;
    };
}
