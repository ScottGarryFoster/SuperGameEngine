#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace SuperGameTools
{
    /// <summary>
    /// The colour palette used.
    /// </summary>
    enum class ColourPalette : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Darkmode default.
        /// </summary>
        Dark,

        /// <summary>
        /// Lightmode default.
        /// </summary>
        Light,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EColourPalette
    {
    public:
        static ColourPalette Min() { return ColourPalette::Dark; }
        static ColourPalette Max() { return ColourPalette::Light; }

        static ColourPalette* ToArray()
        {
            static ColourPalette returnArray[] =
            {
                ColourPalette::Dark,
                ColourPalette::Light,
            };
            
            return returnArray;
        }

        static std::vector<ColourPalette> ToVector()
        {
            static std::vector<ColourPalette> returnVector =
            {
                ColourPalette::Dark,
                ColourPalette::Light,
            };
            
            return returnVector;
        }

        static std::string ToString(ColourPalette value)
        {
            switch (value)
            {
                case ColourPalette::Unknown: return "Unknown";
                case ColourPalette::Dark: return "Dark";
                case ColourPalette::Light: return "Light";
            }
            
            return "Unknown";
        }

        static ColourPalette FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return ColourPalette::Unknown;
                if (value == "Dark") return ColourPalette::Dark;
                if (value == "Light") return ColourPalette::Light;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return ColourPalette::Unknown;
                if (valueLower == "dark") return ColourPalette::Dark;
                if (valueLower == "light") return ColourPalette::Light;
            }
            
            return ColourPalette::Unknown;
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
