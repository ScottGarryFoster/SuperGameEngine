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
    /// How the tree view item should open or close.
    /// </summary>
    enum class TreeViewItemCollapsibleBehaviour : int8_t
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// Will open and close with a click or action from the user such as the arrow.
        /// </summary>
        CanOpenClose,

        /// <summary>
        /// Will only open if the arrow is used.
        /// </summary>
        OpenCloseFromArrowOnly,

        /// <summary>
        /// Will only open if the item is selected with a double click.
        /// </summary>
        OpenCloseFromDoubleClickOnly,

        /// <summary>
        /// Always shown the user and cannot be collapsed.
        /// </summary>
        AlwaysShown,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ETreeViewItemCollapsibleBehaviour
    {
    public:
        static TreeViewItemCollapsibleBehaviour Min() { return TreeViewItemCollapsibleBehaviour::CanOpenClose; }
        static TreeViewItemCollapsibleBehaviour Max() { return TreeViewItemCollapsibleBehaviour::AlwaysShown; }

        static TreeViewItemCollapsibleBehaviour* ToArray()
        {
            static TreeViewItemCollapsibleBehaviour returnArray[] =
            {
                TreeViewItemCollapsibleBehaviour::CanOpenClose,
                TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly,
                TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly,
                TreeViewItemCollapsibleBehaviour::AlwaysShown,
            };
            
            return returnArray;
        }

        static std::vector<TreeViewItemCollapsibleBehaviour> ToVector()
        {
            static std::vector<TreeViewItemCollapsibleBehaviour> returnVector =
            {
                TreeViewItemCollapsibleBehaviour::CanOpenClose,
                TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly,
                TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly,
                TreeViewItemCollapsibleBehaviour::AlwaysShown,
            };
            
            return returnVector;
        }

        static std::string ToString(TreeViewItemCollapsibleBehaviour value)
        {
            switch (value)
            {
                case TreeViewItemCollapsibleBehaviour::Unknown: return "Unknown";
                case TreeViewItemCollapsibleBehaviour::CanOpenClose: return "CanOpenClose";
                case TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly: return "OpenCloseFromArrowOnly";
                case TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly: return "OpenCloseFromDoubleClickOnly";
                case TreeViewItemCollapsibleBehaviour::AlwaysShown: return "AlwaysShown";
            }
            
            return "Unknown";
        }

        static TreeViewItemCollapsibleBehaviour FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return TreeViewItemCollapsibleBehaviour::Unknown;
                if (value == "CanOpenClose") return TreeViewItemCollapsibleBehaviour::CanOpenClose;
                if (value == "OpenCloseFromArrowOnly") return TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly;
                if (value == "OpenCloseFromDoubleClickOnly") return TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly;
                if (value == "AlwaysShown") return TreeViewItemCollapsibleBehaviour::AlwaysShown;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return TreeViewItemCollapsibleBehaviour::Unknown;
                if (valueLower == "canopenclose") return TreeViewItemCollapsibleBehaviour::CanOpenClose;
                if (valueLower == "openclosefromarrowonly") return TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly;
                if (valueLower == "openclosefromdoubleclickonly") return TreeViewItemCollapsibleBehaviour::OpenCloseFromDoubleClickOnly;
                if (valueLower == "alwaysshown") return TreeViewItemCollapsibleBehaviour::AlwaysShown;
            }
            
            return TreeViewItemCollapsibleBehaviour::Unknown;
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
