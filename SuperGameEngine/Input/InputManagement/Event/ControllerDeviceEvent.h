#pragma once
#include <cstdint>

namespace SuperGameInput
{
    /// <summary>
    /// Represents a <see cref="SDL_ControllerDeviceEvent"/> without the SDL.
    /// </summary>
    struct ControllerDeviceEvent
    {
    public:
        /// <summary>
        /// When the event was triggered in ticks from when SDL was started.
        /// </summary>
        uint32_t Timestamp;

        /// <summary>
        /// Used mainly for conversion, this is the number the controller sits in the
        /// list of all the joy sticks SDL knows of.
        /// </summary>
        /// <remarks>Only used in Add. </remarks>
        int IndexID = -1;

        /// <summary>
        /// The instance ID added or removed.
        /// Use this to get more information on the controller.
        /// </summary>
        int32_t ControllerInstanceID;

        /// <summary>
        /// The name of the Controller.
        /// </summary>
        /// <remarks>Only used in Add. </remarks>
        std::string Name;

        /// <summary>
        /// Number of axes (plural of axis) on the Controller.
        /// </summary>
        /// <remarks>Only used in Add. </remarks>
        int Axes;

        /// <summary>
        /// Number of buttons on the Controller.
        /// </summary>
        /// <remarks>Only used in Add. </remarks>
        int Buttons;
    };
}


