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
    };
}