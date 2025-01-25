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
    /// How the tree view item should display with an icon.
    /// Does not affect if the element can open or close.
    /// </summary>
    enum class TreeViewItemCollapsibleIcon : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Nothing is displayed next to it.
        /// </summary>
        NoIcon,

        /// <summary>
        /// Arrow is displayed next to it. Will change on open/close.
        /// </summary>
        Arrow,

        /// <summary>
        /// Bullet point is displayed next to it.
        /// </summary>
        Bullet,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ETreeViewItemCollapsibleIcon
    {
    public:
        static TreeViewItemCollapsibleIcon Min() { return TreeViewItemCollapsibleIcon::NoIcon; }
        static TreeViewItemCollapsibleIcon Max() { return TreeViewItemCollapsibleIcon::Bullet; }

        static TreeViewItemCollapsibleIcon* ToArray()
        {
            static TreeViewItemCollapsibleIcon returnArray[] =
            {
                TreeViewItemCollapsibleIcon::NoIcon,
                TreeViewItemCollapsibleIcon::Arrow,
                TreeViewItemCollapsibleIcon::Bullet,
            };
            
            return returnArray;
        }

        static std::vector<TreeViewItemCollapsibleIcon> ToVector()
        {
            static std::vector<TreeViewItemCollapsibleIcon> returnVector =
            {
                TreeViewItemCollapsibleIcon::NoIcon,
                TreeViewItemCollapsibleIcon::Arrow,
                TreeViewItemCollapsibleIcon::Bullet,
            };
            
            return returnVector;
        }

        static std::string ToString(TreeViewItemCollapsibleIcon value)
        {
            switch (value)
            {
                case TreeViewItemCollapsibleIcon::Unknown: return "Unknown";
                case TreeViewItemCollapsibleIcon::NoIcon: return "NoIcon";
                case TreeViewItemCollapsibleIcon::Arrow: return "Arrow";
                case TreeViewItemCollapsibleIcon::Bullet: return "Bullet";
            }
            
            return "Unknown";
        }

        static TreeViewItemCollapsibleIcon FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return TreeViewItemCollapsibleIcon::Unknown;
                if (value == "NoIcon") return TreeViewItemCollapsibleIcon::NoIcon;
                if (value == "Arrow") return TreeViewItemCollapsibleIcon::Arrow;
                if (value == "Bullet") return TreeViewItemCollapsibleIcon::Bullet;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return TreeViewItemCollapsibleIcon::Unknown;
                if (valueLower == "noicon") return TreeViewItemCollapsibleIcon::NoIcon;
                if (valueLower == "arrow") return TreeViewItemCollapsibleIcon::Arrow;
                if (valueLower == "bullet") return TreeViewItemCollapsibleIcon::Bullet;
            }
            
            return TreeViewItemCollapsibleIcon::Unknown;
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
