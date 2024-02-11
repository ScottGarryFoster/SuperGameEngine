#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes buttons on an Xbox Controller.
    /// </summary>
    enum class DirectXButton
    {
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
        static DirectXButton Max() { return DirectXButton::RightShoulder; }
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
    };
}