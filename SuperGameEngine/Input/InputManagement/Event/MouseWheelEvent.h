#pragma once
#include <cstdint>

#include "MouseButton.h"
#include "MouseWheelDirection.h"
#include "WindowEventType.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_MouseWheelEvent"/> without the SDL.
    /// </summary>
    struct MouseWheelEvent
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
        /// When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back
        /// </summary>
        MouseWheelDirection Direction;

        /// <summary>
        /// Mouse Wheel scroll Left and Right.
        /// </summary>
        int32_t X;

        /// <summary>
        /// Mouse Wheel scroll Up and Down.
        /// </summary>
        int32_t Y;

        /// <summary>
        /// Mouse Wheel scroll Left and Right.
        /// </summary>
        float PreciseX;

        /// <summary>
        /// Mouse Wheel scroll Up and Down.
        /// </summary>
        float PreciseY;

        /// <summary>
        /// Mouse position X relative to the window.
        /// </summary>
        int32_t MouseX;

        /// <summary>
        /// Mouse position Y relative to the window.
        /// </summary>
        int32_t MouseY;
    };
}
