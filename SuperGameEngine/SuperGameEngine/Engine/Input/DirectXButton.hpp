#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes buttons on an Xbox Controller.
    /// </summary>
    enum class DirectXButton
    {
        Unknown = -1,

        A,
        B,
        X,
        Y,
        DpadUp,
        DpadDown,
        DpadLeft,
        DpadRight,
        Start,
        Back,
        LeftThumb,
        RightThumb,
        LeftShoulder,
        RightShoulder,
        LeftTrigger,
        RightTrigger,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EDirectXButton : public Object
    {
    public:
        static DirectXButton Min() { return DirectXButton::A; }
        static DirectXButton Max() { return DirectXButton::RightTrigger; }
        static DirectXButton* ToArray()
        {
            static DirectXButton arr[] =
            {
                DirectXButton::A,
                DirectXButton::B,
                DirectXButton::X,
                DirectXButton::Y,
                DirectXButton::DpadUp,
                DirectXButton::DpadDown,
                DirectXButton::DpadLeft,
                DirectXButton::DpadRight,
                DirectXButton::Start,
                DirectXButton::Back,
                DirectXButton::LeftThumb,
                DirectXButton::RightThumb,
                DirectXButton::LeftShoulder,
                DirectXButton::RightShoulder,
                DirectXButton::LeftTrigger,
                DirectXButton::RightTrigger,
            };
            return arr;
        }

        static std::vector<DirectXButton> ToVector()
        {
            static std::vector<DirectXButton> returnVector =
            {
                DirectXButton::A,
                DirectXButton::B,
                DirectXButton::X,
                DirectXButton::Y,
                DirectXButton::DpadUp,
                DirectXButton::DpadDown,
                DirectXButton::DpadLeft,
                DirectXButton::DpadRight,
                DirectXButton::Start,
                DirectXButton::Back,
                DirectXButton::LeftThumb,
                DirectXButton::RightThumb,
                DirectXButton::LeftShoulder,
                DirectXButton::RightShoulder,
                DirectXButton::LeftTrigger,
                DirectXButton::RightTrigger,
            };
            return returnVector;
        }

        static std::string ToString(DirectXButton value)
        {
            switch (value)
            {
            case DirectXButton::Unknown: return "Unknown";
            case DirectXButton::A: return "A";
            case DirectXButton::B: return "B";
            case DirectXButton::X: return "X";
            case DirectXButton::Y: return "Y";
            case DirectXButton::DpadUp: return "DpadUp";
            case DirectXButton::DpadDown: return "DpadDown";
            case DirectXButton::DpadLeft: return "DpadLeft";
            case DirectXButton::DpadRight: return "DpadRight";
            case DirectXButton::Start: return "Start";
            case DirectXButton::Back: return "Back";
            case DirectXButton::LeftThumb: return "LeftThumb";
            case DirectXButton::RightThumb: return "RightThumb";
            case DirectXButton::LeftShoulder: return "LeftShoulder";
            case DirectXButton::RightShoulder: return "RightShoulder";
            case DirectXButton::LeftTrigger: return "LeftTrigger";
            case DirectXButton::RightTrigger: return "RightTrigger";
            }

            Logger::Assert(NotImplementedException(), FString("EDirectXButton"), FString("ToString"),
                FString("No string value for a DirectX Button requested."));
            return "Unknown";
        }

        static DirectXButton FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (FString(value) == "Unknown") return DirectXButton::Unknown;
                if (FString(value) == "A") return DirectXButton::A;
                if (FString(value) == "B") return DirectXButton::B;
                if (FString(value) == "X") return DirectXButton::X;
                if (FString(value) == "Y") return DirectXButton::Y;
                if (FString(value) == "DpadUp") return DirectXButton::DpadUp;
                if (FString(value) == "DpadDown") return DirectXButton::DpadDown;
                if (FString(value) == "DpadLeft") return DirectXButton::DpadLeft;
                if (FString(value) == "DpadRight") return DirectXButton::DpadRight;
                if (FString(value) == "Start") return DirectXButton::Start;
                if (FString(value) == "Back") return DirectXButton::Back;
                if (FString(value) == "LeftThumb") return DirectXButton::LeftThumb;
                if (FString(value) == "RightThumb") return DirectXButton::RightThumb;
                if (FString(value) == "LeftShoulder") return DirectXButton::LeftShoulder;
                if (FString(value) == "RightShoulder") return DirectXButton::RightShoulder;
                if (FString(value) == "LeftTrigger") return DirectXButton::LeftTrigger;
                if (FString(value) == "RightTrigger") return DirectXButton::RightTrigger;
            }
            else
            {
                if (FString(value).ToLower() == FString("Unknown").ToLower()) return DirectXButton::Unknown;
                if (FString(value).ToLower() == FString("A").ToLower()) return DirectXButton::A;
                if (FString(value).ToLower() == FString("B").ToLower()) return DirectXButton::B;
                if (FString(value).ToLower() == FString("X").ToLower()) return DirectXButton::X;
                if (FString(value).ToLower() == FString("Y").ToLower()) return DirectXButton::Y;
                if (FString(value).ToLower() == FString("DpadUp").ToLower()) return DirectXButton::DpadUp;
                if (FString(value).ToLower() == FString("DpadDown").ToLower()) return DirectXButton::DpadDown;
                if (FString(value).ToLower() == FString("DpadLeft").ToLower()) return DirectXButton::DpadLeft;
                if (FString(value).ToLower() == FString("DpadRight").ToLower()) return DirectXButton::DpadRight;
                if (FString(value).ToLower() == FString("Start").ToLower()) return DirectXButton::Start;
                if (FString(value).ToLower() == FString("Back").ToLower()) return DirectXButton::Back;
                if (FString(value).ToLower() == FString("LeftThumb").ToLower()) return DirectXButton::LeftThumb;
                if (FString(value).ToLower() == FString("RightThumb").ToLower()) return DirectXButton::RightThumb;
                if (FString(value).ToLower() == FString("LeftShoulder").ToLower()) return DirectXButton::LeftShoulder;
                if (FString(value).ToLower() == FString("RightShoulder").ToLower()) return DirectXButton::RightShoulder;
                if (FString(value).ToLower() == FString("LeftTrigger").ToLower()) return DirectXButton::LeftTrigger;
                if (FString(value).ToLower() == FString("RightTrigger").ToLower()) return DirectXButton::RightTrigger;
            }

            Logger::Assert(NotImplementedException(), FString("EDirectXButton"), FString("FromString"),
                FString("No Controller value for a DirectX Button requested."));
            return DirectXButton::Unknown;
        }
    };
}