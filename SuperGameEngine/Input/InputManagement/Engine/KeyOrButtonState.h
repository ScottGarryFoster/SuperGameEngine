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
    /// Describes the state of keys pressed on a keyboard,
    /// mouse buttons or controller buttons.
    /// </summary>
    enum class KeyOrButtonState : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Key is not pressed at all.
        /// Default state.
        /// </summary>
        Unpressed = 0,

        /// <summary>
        /// Has just been pressed. Always also means down. Fires first frame.
        /// </summary>
        Pressed = 1 << 0,

        /// <summary>
        /// Key is down. Fires every frame.
        /// </summary>
        Down = 1 << 1,

        /// <summary>
        /// Key was just release. Fires first frame.
        /// </summary>
        Up = 1 << 2,
    };

    inline KeyOrButtonState operator | (KeyOrButtonState lhs, KeyOrButtonState rhs)
    {
        using T = std::underlying_type_t <KeyOrButtonState>;
        return static_cast<KeyOrButtonState>(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline KeyOrButtonState& operator |= (KeyOrButtonState& lhs, KeyOrButtonState rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    inline KeyOrButtonState operator & (KeyOrButtonState lhs, KeyOrButtonState rhs)
    {
        using T = std::underlying_type_t <KeyOrButtonState>;
        return static_cast<KeyOrButtonState>(static_cast<T>(lhs) & static_cast<T>(rhs));
    }

    inline KeyOrButtonState& operator &= (KeyOrButtonState& lhs, KeyOrButtonState rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EKeyOrButtonState
    {
    public:
        static KeyOrButtonState Min() { return KeyOrButtonState::Unpressed; }
        static KeyOrButtonState Max() { return KeyOrButtonState::Up; }

        static KeyOrButtonState* ToArray()
        {
            static KeyOrButtonState returnArray[] =
            {
                KeyOrButtonState::Unpressed,
                KeyOrButtonState::Pressed,
                KeyOrButtonState::Down,
                KeyOrButtonState::Up,
            };
            
            return returnArray;
        }

        static std::vector<KeyOrButtonState> ToVector()
        {
            static std::vector<KeyOrButtonState> returnVector =
            {
                KeyOrButtonState::Unpressed,
                KeyOrButtonState::Pressed,
                KeyOrButtonState::Down,
                KeyOrButtonState::Up,
            };
            
            return returnVector;
        }

        static std::string ToString(KeyOrButtonState value)
        {
            switch (value)
            {
                case KeyOrButtonState::Unknown: return "Unknown";
                case KeyOrButtonState::Unpressed: return "Unpressed";
                case KeyOrButtonState::Pressed: return "Pressed";
                case KeyOrButtonState::Down: return "Down";
                case KeyOrButtonState::Up: return "Up";
            }
            
            return "Unknown";
        }

        static KeyOrButtonState FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return KeyOrButtonState::Unknown;
                if (value == "Unpressed") return KeyOrButtonState::Unpressed;
                if (value == "Pressed") return KeyOrButtonState::Pressed;
                if (value == "Down") return KeyOrButtonState::Down;
                if (value == "Up") return KeyOrButtonState::Up;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return KeyOrButtonState::Unknown;
                if (valueLower == "unpressed") return KeyOrButtonState::Unpressed;
                if (valueLower == "pressed") return KeyOrButtonState::Pressed;
                if (valueLower == "down") return KeyOrButtonState::Down;
                if (valueLower == "up") return KeyOrButtonState::Up;
            }
            
            return KeyOrButtonState::Unknown;
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

        /// <summary>
        /// Test to see whether value has the given flag.
        /// </summary>
        /// <param name="origin">Origin to look for flag in. </param>
        /// <param name="lookFor">Value to look for. </param>
        /// <returns>True means has flag. </returns>
        static bool HasFlag(KeyOrButtonState origin, KeyOrButtonState lookFor)
        {
            return (origin & lookFor) != KeyOrButtonState::Unpressed;
        }
    };
}
