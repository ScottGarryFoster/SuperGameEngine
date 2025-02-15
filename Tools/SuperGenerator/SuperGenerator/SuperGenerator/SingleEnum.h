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
    /// When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back
    /// </summary>
    enum class MouseWheelDirection : uint8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown,

        /// <summary>
        /// The scroll direction is normal
        /// </summary>
        SDL_MOUSEWHEEL_NORMAL,

        /// <summary>
        /// The scroll direction is flipped / natural
        /// </summary>
        SDL_MOUSEWHEEL_FLIPPED,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EMouseWheelDirection
    {
    public:
        static MouseWheelDirection Min() { return MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL; }
        static MouseWheelDirection Max() { return MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED; }

        static MouseWheelDirection* ToArray()
        {
            static MouseWheelDirection returnArray[] =
            {
                MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL,
                MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED,
            };

            return returnArray;
        }

        static std::vector<MouseWheelDirection> ToVector()
        {
            static std::vector<MouseWheelDirection> returnVector =
            {
                MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL,
                MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED,
            };

            return returnVector;
        }

        static std::string ToString(MouseWheelDirection value)
        {
            switch (value)
            {
            case MouseWheelDirection::Unknown: return "Unknown";
            case MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL: return "SDL_MOUSEWHEEL_NORMAL";
            case MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED: return "SDL_MOUSEWHEEL_FLIPPED";
            }

            return "Unknown";
        }

        static MouseWheelDirection FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return MouseWheelDirection::Unknown;
                if (value == "SDL_MOUSEWHEEL_NORMAL") return MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL;
                if (value == "SDL_MOUSEWHEEL_FLIPPED") return MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED;
            }
            else
            {
                std::string valueLower = ToLower(value);
                if (valueLower == "unknown") return MouseWheelDirection::Unknown;
                if (valueLower == "sdl_mousewheel_normal") return MouseWheelDirection::SDL_MOUSEWHEEL_NORMAL;
                if (valueLower == "sdl_mousewheel_flipped") return MouseWheelDirection::SDL_MOUSEWHEEL_FLIPPED;
            }

            return MouseWheelDirection::Unknown;
        }

        /// <summary>
        /// Converts to lower. Copy from StringHelpers to ensure Enum does not require
        /// any outside dependency. Although we could include a header, doing so restricts
        /// the project which holds StringHelpers.
        /// </summary>
        static std::string ToLower(const std::string& input)
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
    };
}
