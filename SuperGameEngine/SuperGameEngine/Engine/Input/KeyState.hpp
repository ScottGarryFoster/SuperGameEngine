#pragma once
#include <vector>

namespace SuperGameEngine
{
    /// <summary>
    /// Describes the posible keys pressed on a keyboard.
    /// </summary>
    enum class KeyState
    {
        /// <summary>
        /// Only used for error states
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

    inline KeyState operator | (KeyState lhs, KeyState rhs)
    {
        using T = std::underlying_type_t <KeyState>;
        return static_cast<KeyState>(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    inline KeyState& operator |= (KeyState& lhs, KeyState rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EKeyState
    {
    public:
        static KeyState Min() { return KeyState::Unpressed; }
        static KeyState Max() { return KeyState::Up; }
        static KeyState* ToArray()
        {
            static KeyState arr[] =
            {
                KeyState::Unpressed,
                KeyState::Pressed,
                KeyState::Down,
                KeyState::Up,
            };
            return arr;
        }

        static std::vector<KeyState> ToVector()
        {
            static std::vector<KeyState> returnVector =
            {
                KeyState::Unpressed,
                KeyState::Pressed,
                KeyState::Down,
                KeyState::Up,
            };
            return returnVector;
        }

        static std::string ToString(KeyState value)
        {
            switch (value)
            {
            case KeyState::Unknown: return "Unknown";
            case KeyState::Unpressed: return "Unpressed";
            case KeyState::Pressed: return "Pressed";
            case KeyState::Down: return "Down";
            case KeyState::Up: return "Up";
            }

            Logger::Assert(NotImplementedException(), FString("EKeyState"), FString("ToString"),
                FString("No string value for a Key State requested."));
            return "Unknown";
        }

        static KeyState FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (FString(value) == "Unknown") return KeyState::Unknown;
                if (FString(value) == "Unpressed") return KeyState::Unpressed;
                if (FString(value) == "Pressed") return KeyState::Pressed;
                if (FString(value) == "Down") return KeyState::Down;
                if (FString(value) == "Up") return KeyState::Up;
            }
            else
            {
                if (FString(value).ToLower() == FString("Unknown").ToLower()) return KeyState::Unknown;
                if (FString(value).ToLower() == FString("Unpressed").ToLower()) return KeyState::Unpressed;
                if (FString(value).ToLower() == FString("Pressed").ToLower()) return KeyState::Pressed;
                if (FString(value).ToLower() == FString("Down").ToLower()) return KeyState::Down;
                if (FString(value).ToLower() == FString("Up").ToLower()) return KeyState::Up;
            }

            Logger::Assert(NotImplementedException(), FString("EKeyState"), FString("FromString"),
                FString("No Controller value for a Key State requested."));
            return KeyState::Unknown;
        }
    };
}