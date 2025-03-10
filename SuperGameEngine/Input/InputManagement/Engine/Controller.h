#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace SuperGameInput
{
    /// <summary>
    /// Describes a specific controller.
    /// </summary>
    enum class Controller : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

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

        /// <summary>
        /// Official Switch Original Pro Controller.
        /// </summary>
        NintendoSwitchProController,

        /// <summary>
        /// This is an Official N64 Controller from the
        /// Nintendo Online Switch Subscription.
        /// </summary>
        NintendoN64Controller,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EController
    {
    public:
        static Controller Min() { return Controller::Xbox360Controller; }
        static Controller Max() { return Controller::NintendoN64Controller; }

        static Controller* ToArray()
        {
            static Controller returnArray[] =
            {
                Controller::Xbox360Controller,
                Controller::XboxSeriesController,
                Controller::NintendoSwitchProController,
                Controller::NintendoN64Controller,
            };
            
            return returnArray;
        }

        static std::vector<Controller> ToVector()
        {
            static std::vector<Controller> returnVector =
            {
                Controller::Xbox360Controller,
                Controller::XboxSeriesController,
                Controller::NintendoSwitchProController,
                Controller::NintendoN64Controller,
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
                case Controller::NintendoN64Controller: return "NintendoN64Controller";
            }
            
            return "Unknown";
        }

        static Controller FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return Controller::Unknown;
                if (value == "Xbox360Controller") return Controller::Xbox360Controller;
                if (value == "XboxSeriesController") return Controller::XboxSeriesController;
                if (value == "NintendoSwitchProController") return Controller::NintendoSwitchProController;
                if (value == "NintendoN64Controller") return Controller::NintendoN64Controller;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return Controller::Unknown;
                if (valueLower == "xbox360controller") return Controller::Xbox360Controller;
                if (valueLower == "xboxseriescontroller") return Controller::XboxSeriesController;
                if (valueLower == "nintendoswitchprocontroller") return Controller::NintendoSwitchProController;
                if (valueLower == "nintendon64controller") return Controller::NintendoN64Controller;
            }
            
            return Controller::Unknown;
        }

        /// <summary>
        /// Converts to lower. Copy from StringHelpers to ensure Enum does not require
        /// any outside dependency. Although we could include a header, doing so restricts
        /// the project which holds StringHelpers.
        /// </summary>
        static std::string ToLower(const std::string & input)
        {
            std::string output = input;
            for (char& c : output)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    c = c - 'A' + 'a';
                }
            }
            return output;
        }
    };
}
