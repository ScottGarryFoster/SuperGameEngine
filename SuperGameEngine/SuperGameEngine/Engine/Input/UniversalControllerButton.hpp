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

            Logger::Assert(NotImplementedException(), FString("EUniversalControllerButton"), FString("ToString"),
                FString("No string value for a UniversalControllerButton requested."));
            return "Unknown";
        }

        static UniversalControllerButton FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                FString stringValue = value;
                if (stringValue == "Unknown") return UniversalControllerButton::Unknown;
                if (stringValue == "FaceButtonDown") return UniversalControllerButton::FaceButtonDown;
                if (stringValue == "FaceButtonLeft") return UniversalControllerButton::FaceButtonLeft;
                if (stringValue == "FaceButtonRight") return UniversalControllerButton::FaceButtonRight;
                if (stringValue == "FaceButtonUp") return UniversalControllerButton::FaceButtonUp;
                if (stringValue == "DPadDown") return UniversalControllerButton::DPadDown;
                if (stringValue == "DPadLeft") return UniversalControllerButton::DPadLeft;
                if (stringValue == "DPadRight") return UniversalControllerButton::DPadRight;
                if (stringValue == "DPadUp") return UniversalControllerButton::DPadUp;
                if (stringValue == "LeftShoulder") return UniversalControllerButton::LeftShoulder;
                if (stringValue == "RightShoulder") return UniversalControllerButton::RightShoulder;
                if (stringValue == "LeftTrigger") return UniversalControllerButton::LeftTrigger;
                if (stringValue == "RightTrigger") return UniversalControllerButton::RightTrigger;
                if (stringValue == "Start") return UniversalControllerButton::Start;
                if (stringValue == "Select") return UniversalControllerButton::Select;
                if (stringValue == "LeftStickClick") return UniversalControllerButton::LeftStickClick;
                if (stringValue == "RightStickClick") return UniversalControllerButton::RightStickClick;
            }
            else
            {
                FString stringValueLower = value;
                stringValueLower.ConvertToLower();
                if (stringValueLower == FString("Unknown").ToLower()) return UniversalControllerButton::Unknown;
                if (stringValueLower == FString("FaceButtonDown").ToLower()) return UniversalControllerButton::FaceButtonDown;
                if (stringValueLower == FString("FaceButtonLeft").ToLower()) return UniversalControllerButton::FaceButtonLeft;
                if (stringValueLower == FString("FaceButtonRight").ToLower()) return UniversalControllerButton::FaceButtonRight;
                if (stringValueLower == FString("FaceButtonUp").ToLower()) return UniversalControllerButton::FaceButtonUp;
                if (stringValueLower == FString("DPadDown").ToLower()) return UniversalControllerButton::DPadDown;
                if (stringValueLower == FString("DPadLeft").ToLower()) return UniversalControllerButton::DPadLeft;
                if (stringValueLower == FString("DPadRight").ToLower()) return UniversalControllerButton::DPadRight;
                if (stringValueLower == FString("DPadUp").ToLower()) return UniversalControllerButton::DPadUp;
                if (stringValueLower == FString("LeftShoulder").ToLower()) return UniversalControllerButton::LeftShoulder;
                if (stringValueLower == FString("RightShoulder").ToLower()) return UniversalControllerButton::RightShoulder;
                if (stringValueLower == FString("LeftTrigger").ToLower()) return UniversalControllerButton::LeftTrigger;
                if (stringValueLower == FString("RightTrigger").ToLower()) return UniversalControllerButton::RightTrigger;
                if (stringValueLower == FString("Start").ToLower()) return UniversalControllerButton::Start;
                if (stringValueLower == FString("Select").ToLower()) return UniversalControllerButton::Select;
                if (stringValueLower == FString("LeftStickClick").ToLower()) return UniversalControllerButton::LeftStickClick;
                if (stringValueLower == FString("RightStickClick").ToLower()) return UniversalControllerButton::RightStickClick;
            }

            Logger::Assert(NotImplementedException(), FString("EUniversalControllerButton"), FString("FromString"),
                FString("No Universal Controller Button value for a button requested: ") + value);
            return UniversalControllerButton::Unknown;
        }
    };
}