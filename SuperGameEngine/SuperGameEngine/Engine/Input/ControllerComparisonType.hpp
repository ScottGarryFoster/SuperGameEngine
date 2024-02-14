#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// How to compare two values.
    /// </summary>
    enum class ControllerComparisonType
    {
        Greater,

        Less,

        Equals,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EControllerComparisonType : public Object
    {
    public:
        static ControllerComparisonType Min() { return ControllerComparisonType::Greater; }
        static ControllerComparisonType Max() { return ControllerComparisonType::Equals; }
        static ControllerComparisonType* ToArray()
        {
            static ControllerComparisonType arr[] =
            {
                ControllerComparisonType::Greater,
                ControllerComparisonType::Less,
                ControllerComparisonType::Equals,
            };
            return arr;
        }

        static std::vector<ControllerComparisonType> ToVector()
        {
            static std::vector<ControllerComparisonType> returnVector =
            {
                ControllerComparisonType::Greater,
                ControllerComparisonType::Less,
                ControllerComparisonType::Equals,
            };
            return returnVector;
        }

        static std::string ToString(ControllerComparisonType value)
        {
            switch (value)
            {
                case ControllerComparisonType::Greater: return "Greater";
                case ControllerComparisonType::Less: return "Less";
                case ControllerComparisonType::Equals: return "Equals";
            }

            Logger::Exception(NotImplementedException(), FString("EControllerComparisonType"), FString("ToString"),
                FString("No string value for a ControllerComparisonType requested."));
            return "Unknown";
        }

        static ControllerComparisonType FromString(std::string value)
        {
            if (value == "Greater") return ControllerComparisonType::Greater;
            if (value == "Less") return ControllerComparisonType::Less;
            if (value == "Equals") return ControllerComparisonType::Equals;

            Logger::Exception(NotImplementedException(), FString("EControllerComparisonType"), FString("FromString"),
                FString("No enum value for a ControllerComparisonType requested: ") + value);
            return ControllerComparisonType::Greater;
        }
    };
}