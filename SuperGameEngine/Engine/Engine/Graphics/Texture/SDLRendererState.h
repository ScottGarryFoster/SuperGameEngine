#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace SuperGameEngine
{
    /// <summary>
    /// The state the renderer is in.
    /// Used to understand whether to trust the reference.
    /// </summary>
    enum class SDLRendererState : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// The renderer is currently in use and therefore can be trusted.
        /// </summary>
        Active,

        /// <summary>
        /// The renderer has been destroyed.
        /// Remove references and do not use it again.
        /// </summary>
        Destroyed,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ESDLRendererState
    {
    public:
        static SDLRendererState Min() { return SDLRendererState::Active; }
        static SDLRendererState Max() { return SDLRendererState::Destroyed; }

        static SDLRendererState* ToArray()
        {
            static SDLRendererState returnArray[] =
            {
                SDLRendererState::Active,
                SDLRendererState::Destroyed,
            };
            
            return returnArray;
        }

        static std::vector<SDLRendererState> ToVector()
        {
            static std::vector<SDLRendererState> returnVector =
            {
                SDLRendererState::Active,
                SDLRendererState::Destroyed,
            };
            
            return returnVector;
        }

        static std::string ToString(SDLRendererState value)
        {
            switch (value)
            {
                case SDLRendererState::Unknown: return "Unknown";
                case SDLRendererState::Active: return "Active";
                case SDLRendererState::Destroyed: return "Destroyed";
            }
            
            return "Unknown";
        }

        static SDLRendererState FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return SDLRendererState::Unknown;
                if (value == "Active") return SDLRendererState::Active;
                if (value == "Destroyed") return SDLRendererState::Destroyed;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return SDLRendererState::Unknown;
                if (valueLower == "active") return SDLRendererState::Active;
                if (valueLower == "destroyed") return SDLRendererState::Destroyed;
            }
            
            return SDLRendererState::Unknown;
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
    };
}
