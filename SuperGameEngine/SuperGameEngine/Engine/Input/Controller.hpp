#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a specific controller
    /// </summary>
    enum class Controller
    {
        /// <summary>
        /// We have no idea what this controller is.
        /// </summary>
        Unknown,

        /// <summary>
        /// This will show up for all off the shelf 360 controllers
        /// which match the layout. This also means the vibrations will
        /// not work for all controllers.
        /// </summary>
        Xbox360Controller,

        /// <summary>
        /// Xbox Series X or S controller.
        /// </summary>
        XboxSeriesController,

        NintendoSwitchProController,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EController : public Object
    {
    public:
        static Controller Min() { return Controller::Xbox360Controller; }
        static Controller Max() { return Controller::NintendoSwitchProController; }
        static Controller* ToArray()
        {
            static Controller arr[] =
            {
                Controller::Xbox360Controller,
                Controller::XboxSeriesController,
                Controller::NintendoSwitchProController,
            };
            return arr;
        }

        static std::vector<Controller> ToVector()
        {
            static std::vector<Controller> returnVector =
            {
                Controller::Xbox360Controller,
                Controller::XboxSeriesController,
                Controller::NintendoSwitchProController,
            };
            return returnVector;
        }

        static std::string ToString(Controller value)
        {
            switch (value)
            {
                case Controller::Unknown: return "Unknown";
                case Controller::Xbox360Controller: return "Xbox360Controller";
                case Controller::XboxSeriesController: return "XboxSeriesController";
                case Controller::NintendoSwitchProController: return "NintendoSwitchProController";
            }

            Logger::Exception(NotImplementedException(), FString("EController"), FString("ToString"), FString("No string value for a controller requested."));
            return "Unknown";
        }
    };
}