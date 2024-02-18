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

        static UniversalControllerButton FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (FString(value) == "Unknown") return UniversalControllerButton::Unknown;
                if (FString(value) == "FaceButtonDown") return UniversalControllerButton::FaceButtonDown;
                if (FString(value) == "FaceButtonLeft") return UniversalControllerButton::FaceButtonLeft;
                if (FString(value) == "FaceButtonRight") return UniversalControllerButton::FaceButtonRight;
                if (FString(value) == "FaceButtonUp") return UniversalControllerButton::FaceButtonUp;
                if (FString(value) == "DPadDown") return UniversalControllerButton::DPadDown;
                if (FString(value) == "DPadLeft") return UniversalControllerButton::DPadLeft;
                if (FString(value) == "DPadRight") return UniversalControllerButton::DPadRight;
                if (FString(value) == "DPadUp") return UniversalControllerButton::DPadUp;
                if (FString(value) == "LeftShoulder") return UniversalControllerButton::LeftShoulder;
                if (FString(value) == "RightShoulder") return UniversalControllerButton::RightShoulder;
                if (FString(value) == "LeftTrigger") return UniversalControllerButton::LeftTrigger;
                if (FString(value) == "RightTrigger") return UniversalControllerButton::RightTrigger;
                if (FString(value) == "Start") return UniversalControllerButton::Start;
                if (FString(value) == "Select") return UniversalControllerButton::Select;
                if (FString(value) == "LeftStickClick") return UniversalControllerButton::LeftStickClick;
                if (FString(value) == "RightStickClick") return UniversalControllerButton::RightStickClick;
            }
            else
            {
                if (FString(value).ToLower() == FString("Unknown").ToLower()) return UniversalControllerButton::Unknown;
                if (FString(value).ToLower() == FString("FaceButtonDown").ToLower()) return UniversalControllerButton::FaceButtonDown;
                if (FString(value).ToLower() == FString("FaceButtonLeft").ToLower()) return UniversalControllerButton::FaceButtonLeft;
                if (FString(value).ToLower() == FString("FaceButtonRight").ToLower()) return UniversalControllerButton::FaceButtonRight;
                if (FString(value).ToLower() == FString("FaceButtonUp").ToLower()) return UniversalControllerButton::FaceButtonUp;
                if (FString(value).ToLower() == FString("DPadDown").ToLower()) return UniversalControllerButton::DPadDown;
                if (FString(value).ToLower() == FString("DPadLeft").ToLower()) return UniversalControllerButton::DPadLeft;
                if (FString(value).ToLower() == FString("DPadRight").ToLower()) return UniversalControllerButton::DPadRight;
                if (FString(value).ToLower() == FString("DPadUp").ToLower()) return UniversalControllerButton::DPadUp;
                if (FString(value).ToLower() == FString("LeftShoulder").ToLower()) return UniversalControllerButton::LeftShoulder;
                if (FString(value).ToLower() == FString("RightShoulder").ToLower()) return UniversalControllerButton::RightShoulder;
                if (FString(value).ToLower() == FString("LeftTrigger").ToLower()) return UniversalControllerButton::LeftTrigger;
                if (FString(value).ToLower() == FString("RightTrigger").ToLower()) return UniversalControllerButton::RightTrigger;
                if (FString(value).ToLower() == FString("Start").ToLower()) return UniversalControllerButton::Start;
                if (FString(value).ToLower() == FString("Select").ToLower()) return UniversalControllerButton::Select;
                if (FString(value).ToLower() == FString("LeftStickClick").ToLower()) return UniversalControllerButton::LeftStickClick;
                if (FString(value).ToLower() == FString("RightStickClick").ToLower()) return UniversalControllerButton::RightStickClick;
            }

            Logger::Exception(NotImplementedException(), FString("EUniversalControllerButton"), FString("FromString"),
                FString("No Universal Controller Button value for a button requested: ") + value);
            return UniversalControllerButton::Unknown;
        }
    };
}