#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a control stick upon a modern game controller.
    /// </summary>
    enum class UniversalControllerAxis
    {
        /// <summary>
        /// Used when returning a mapping and it is unclear what the mapping is for.
        /// Ommited from the lists for the Enum.
        /// </summary>
        Unknown,

        LeftStickX,
        LeftStickY,
        RightStickX,
        RightStickY,
        LeftTrigger,
        RightTrigger,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EUniversalControllerAxis : public Object
    {
    public:
        static UniversalControllerAxis Min() { return UniversalControllerAxis::LeftStickX; }
        static UniversalControllerAxis Max() { return UniversalControllerAxis::RightTrigger; }
        static UniversalControllerAxis* ToArray()
        {
            static UniversalControllerAxis arr[] =
            {
                UniversalControllerAxis::LeftStickX,
                UniversalControllerAxis::LeftStickY,
                UniversalControllerAxis::RightStickX,
                UniversalControllerAxis::RightStickY,
                UniversalControllerAxis::LeftTrigger,
                UniversalControllerAxis::RightTrigger,
            };

            return arr;
        }

        static std::vector<UniversalControllerAxis> ToVector()
        {
            static std::vector<UniversalControllerAxis> returnVector =
            {
                UniversalControllerAxis::LeftStickX,
                UniversalControllerAxis::LeftStickY,
                UniversalControllerAxis::RightStickX,
                UniversalControllerAxis::RightStickY,
                UniversalControllerAxis::LeftTrigger,
                UniversalControllerAxis::RightTrigger,
            };

            return returnVector;
        }

        static std::string ToString(UniversalControllerAxis value)
        {
            switch (value)
            {
                case UniversalControllerAxis::Unknown: return "Unknown";
                case UniversalControllerAxis::LeftStickX: return "LeftStickX";
                case UniversalControllerAxis::LeftStickY: return "LeftStickY";
                case UniversalControllerAxis::RightStickX: return "RightStickX";
                case UniversalControllerAxis::RightStickY: return "RightStickY";
                case UniversalControllerAxis::LeftTrigger: return "LeftTrigger";
                case UniversalControllerAxis::RightTrigger: return "RightTrigger";
            }

            Logger::Exception(NotImplementedException(), FString("EUniversalControllerAxis"), FString("ToString"),
                FString("No string value for a UniversalControllerAxis requested."));
            return "Unknown";
        }

        static UniversalControllerAxis FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                FString stringValue = value;
                if (stringValue == "Unknown") return UniversalControllerAxis::Unknown;
                if (stringValue == "LeftStickX") return UniversalControllerAxis::LeftStickX;
                if (stringValue == "LeftStickY") return UniversalControllerAxis::LeftStickY;
                if (stringValue == "RightStickX") return UniversalControllerAxis::RightStickX;
                if (stringValue == "RightStickY") return UniversalControllerAxis::RightStickY;
                if (stringValue == "LeftTrigger") return UniversalControllerAxis::LeftTrigger;
                if (stringValue == "RightTrigger") return UniversalControllerAxis::RightTrigger;
            }
            else
            {
                FString stringValueLower = value;
                stringValueLower.ConvertToLower();
                if (stringValueLower == FString("Unknown").ToLower()) return UniversalControllerAxis::Unknown;
                if (stringValueLower == FString("LeftStickX").ToLower()) return UniversalControllerAxis::LeftStickX;
                if (stringValueLower == FString("LeftStickY").ToLower()) return UniversalControllerAxis::LeftStickY;
                if (stringValueLower == FString("RightStickX").ToLower()) return UniversalControllerAxis::RightStickX;
                if (stringValueLower == FString("RightStickY").ToLower()) return UniversalControllerAxis::RightStickY;
                if (stringValueLower == FString("LeftTrigger").ToLower()) return UniversalControllerAxis::LeftTrigger;
                if (stringValueLower == FString("RightTrigger").ToLower()) return UniversalControllerAxis::RightTrigger;
            }

            Logger::Exception(NotImplementedException(), FString("EUniversalControllerAxis"), FString("FromString"),
                FString("No Universal Controller Axis value for a button requested: ") + value);
            return UniversalControllerAxis::Unknown;
        }
    };
}