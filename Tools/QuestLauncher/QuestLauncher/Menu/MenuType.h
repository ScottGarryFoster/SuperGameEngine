#pragma once
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// +------------------------------+
namespace QuestLauncher
{
    /// <summary>
    /// The method to display the menu item.
    /// </summary>
    enum class MenuType
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Just a text option
        /// </summary>
        Simple,

        /// <summary>
        /// A line between menu items.
        /// </summary>
        Separator,

        /// <summary>
        /// Header item
        /// </summary>
        Header,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EMenuType
    {
    public:
        static MenuType Min() { return MenuType::Simple; }
        static MenuType Max() { return MenuType::Header; }

        static MenuType* ToArray()
        {
            static MenuType returnArray[] =
            {
                MenuType::Simple,
                MenuType::Separator,
                MenuType::Header,
            };
            
            return returnArray;
        }

        static std::vector<MenuType> ToVector()
        {
            static std::vector<MenuType> returnVector =
            {
                MenuType::Simple,
                MenuType::Separator,
                MenuType::Header,
            };
            
            return returnVector;
        }

        static std::string ToString(MenuType value)
        {
            switch (value)
            {
                case MenuType::Unknown: return "Unknown";
                case MenuType::Simple: return "Simple";
                case MenuType::Separator: return "Separator";
                case MenuType::Header: return "Header";
            }
            
            return "Unknown";
        }

        static MenuType FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return MenuType::Unknown;
                if (value == "Simple") return MenuType::Simple;
                if (value == "Separator") return MenuType::Separator;
                if (value == "Header") return MenuType::Header;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return MenuType::Unknown;
                if (valueLower == "simple") return MenuType::Simple;
                if (valueLower == "separator") return MenuType::Separator;
                if (valueLower == "header") return MenuType::Header;
            }
            
            return MenuType::Unknown;
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
