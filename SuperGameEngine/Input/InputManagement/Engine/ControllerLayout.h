#pragma once
#include "AxisToUniversalAxis.h"
#include "Controller.h"
#include "ControllerAxisMappedToButton.h"
#include "UniversalControllerButton.h"

namespace SuperGameInput
{
    /// <summary>
    /// Represents a single controller input.
    /// Multiple physical controllers may share the same controller layout.
    /// </summary>
    struct ControllerLayout
    {
    public:
        /// <summary>
        /// The type of controller.
        /// </summary>
        Controller Controller = Controller::Unknown;

        /// <summary>
        /// The name displayed when a controller is plugged in.
        /// </summary>
        std::string Name = {};

        /// <summary>
        /// The number of Axis the controller reports to have.
        /// </summary>
        int Axis = -1;

        /// <summary>
        /// The number of buttons a controller reports to have.
        /// </summary>
        int Buttons = -1;

        /// <summary>
        /// The number of hats a controller reports to have.
        /// A hat is a dpad on a modern controller.
        /// </summary>
        int Hats = -1;

        /// <summary>
        /// Every SDL button and it's universal mapping.
        /// First found will be the resolve.
        /// </summary>
        std::vector<std::pair<int, UniversalControllerButton>> SDLToUniversalButton;

        /// <summary>
        /// Describes how the axis will resolve to buttons.
        /// </summary>
        std::vector<ControllerAxisMappedToButton> AxisToButton;

        /// <summary>
        /// The hat mapped to DPad.
        /// Keep to -1 (no map) if the DPad is mapped to buttons instead.
        /// </summary>
        int HatMappedToDpad = -1;

        /// <summary>
        /// Maps an SDL Axis to a Universal one.
        /// </summary>
        std::vector<AxisToUniversalAxis> SDLAxisToUniversalAxis;
    };
}


