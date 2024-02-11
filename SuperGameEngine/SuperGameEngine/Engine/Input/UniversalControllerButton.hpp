#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a button on any controller from the Modern era.
    /// </summary>
    enum class UniversalControllerButton
    {
        /// <summary>
        /// Used when returning a mapping and it is unclear what the mapping is for.
        /// Ommited from the lists for the Enum.
        /// </summary>
        Unknown,

        FaceButtonDown,
        FaceButtonLeft,
        FaceButtonRight,
        FaceButtonUp,
        DPadDown,
        DPadLeft,
        DPadRight,
        DPadUp,
        LeftShoulder,
        RightShoulder,
        LeftTrigger,
        RightTrigger,
        Start,
        Select,
        LeftStickClick,
        RightStickClick,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EUniversalControllerButton : public Object
    {
    public:
        static UniversalControllerButton Min() { return UniversalControllerButton::FaceButtonDown; }
        static UniversalControllerButton Max() { return UniversalControllerButton::RightStickClick; }
        static UniversalControllerButton* ToArray()
        {
            static UniversalControllerButton arr[] =
            {
                UniversalControllerButton::FaceButtonDown,
                UniversalControllerButton::FaceButtonLeft,
                UniversalControllerButton::FaceButtonRight,
                UniversalControllerButton::FaceButtonUp,
                UniversalControllerButton::DPadDown,
                UniversalControllerButton::DPadLeft,
                UniversalControllerButton::DPadRight,
                UniversalControllerButton::DPadUp,
                UniversalControllerButton::LeftShoulder,
                UniversalControllerButton::RightShoulder,
                UniversalControllerButton::LeftTrigger,
                UniversalControllerButton::RightTrigger,
                UniversalControllerButton::Start,
                UniversalControllerButton::Select,
                UniversalControllerButton::LeftStickClick,
                UniversalControllerButton::RightStickClick,
            };
            return arr;
        }

        static std::vector<UniversalControllerButton> ToVector()
        {
            static std::vector<UniversalControllerButton> returnVector =
            {
                UniversalControllerButton::FaceButtonDown,
                UniversalControllerButton::FaceButtonLeft,
                UniversalControllerButton::FaceButtonRight,
                UniversalControllerButton::FaceButtonUp,
                UniversalControllerButton::DPadDown,
                UniversalControllerButton::DPadLeft,
                UniversalControllerButton::DPadRight,
                UniversalControllerButton::DPadUp,
                UniversalControllerButton::LeftShoulder,
                UniversalControllerButton::RightShoulder,
                UniversalControllerButton::LeftTrigger,
                UniversalControllerButton::RightTrigger,
                UniversalControllerButton::Start,
                UniversalControllerButton::Select,
                UniversalControllerButton::LeftStickClick,
                UniversalControllerButton::RightStickClick,
            };
            return returnVector;
        }

        static std::string ToString(UniversalControllerButton value)
        {
            switch (value)
            {
            case UniversalControllerButton::Unknown: return "Unknown";
            case UniversalControllerButton::FaceButtonDown: return "FaceButtonDown";
            case UniversalControllerButton::FaceButtonLeft: return "FaceButtonLeft";
            case UniversalControllerButton::FaceButtonRight: return "FaceButtonRight";
            case UniversalControllerButton::FaceButtonUp: return "FaceButtonUp";
            case UniversalControllerButton::DPadDown: return "DPadDown";
            case UniversalControllerButton::DPadLeft: return "DPadLeft";
            case UniversalControllerButton::DPadRight: return "DPadRight";
            case UniversalControllerButton::DPadUp: return "DPadUp";
            case UniversalControllerButton::LeftShoulder: return "LeftShoulder";
            case UniversalControllerButton::RightShoulder: return "RightShoulder";
            case UniversalControllerButton::LeftTrigger: return "LeftTrigger";
            case UniversalControllerButton::RightTrigger: return "RightTrigger";
            case UniversalControllerButton::Start: return "Start";
            case UniversalControllerButton::Select: return "Select";
            case UniversalControllerButton::LeftStickClick: return "LeftStickClick";
            case UniversalControllerButton::RightStickClick: return "RightStickClick";
            }

            Logger::Exception(NotImplementedException(), FString("EUniversalControllerButton"), FString("ToString"),
                FString("No string value for a UniversalControllerButton requested."));
            return "Unknown";
        }
    };
}