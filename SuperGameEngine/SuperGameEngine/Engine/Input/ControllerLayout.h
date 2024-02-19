#pragma once
#include <map>

#include "../../LibraryIncludes.h"
#include "UniversalControllerButton.hpp"
#include "ControllerAxisMappedToButton.h"
#include "Controller.hpp"
#include "UniversalControllerAxis.hpp"
#include "AxisToUniversalAxis.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes how SDL buttons, axis and hat relate to the Universal ideas of controllers.
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
        FString Name = FString();

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
        FList<std::pair<int, UniversalControllerButton>> SDLToUniversalButton;

        /// <summary>
        /// Describes how the axis will resolve to buttons.
        /// </summary>
        FList<ControllerAxisMappedToButton> AxisToButton;

        /// <summary>
        /// The hat mapped to DPad.
        /// Keep to -1 (no map) if the DPad is mapped to buttons instead.
        /// </summary>
        int HatMappedToDpad = -1;

        /// <summary>
        /// Maps an SDL Axis to a Universal one.
        /// </summary>
        FList<AxisToUniversalAxis> SDLAxisToUniversalAxis;
    };
}