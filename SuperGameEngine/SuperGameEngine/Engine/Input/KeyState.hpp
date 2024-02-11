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
    };
}