#pragma once
#include <cstdint>

#include "MouseButton.h"
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_MouseButtonEvent"/> without the SDL.
    /// </summary>
    struct MouseButtonEvent
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
        /// True means this event is not a mouse but touch.
        /// </summary>
        bool IsTouch;

        /// <summary>
        /// The actual button on the mouse.
        /// </summary>
        MouseButton Button;

        /// <summary>
        /// Number of clicks, 1 for single-click, 2 for double-click, and so on.
        /// </summary>
        uint32_t Clicks;

        /// <summary>
        /// Position X relative to the window.
        /// </summary>
        int32_t X;

        /// <summary>
        /// Position Y relative to the window.
        /// </summary>
        int32_t Y;
    };
}
