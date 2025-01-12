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
    /// How the selection changed.
    /// </summary>
    enum class SelectionChangeType
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// A selectable was added.
        /// </summary>
        Add,

        /// <summary>
        /// A selectable was removed.
        /// </summary>
        Remove,

        /// <summary>
        /// A selectable group was set to another set of selectables.
        /// </summary>
        Set,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ESelectionChangeType
    {
    public:
        static SelectionChangeType Min() { return SelectionChangeType::Add; }
        static SelectionChangeType Max() { return SelectionChangeType::Set; }

        static SelectionChangeType* ToArray()
        {
            static SelectionChangeType returnArray[] =
            {
                SelectionChangeType::Add,
                SelectionChangeType::Remove,
                SelectionChangeType::Set,
            };
            
            return returnArray;
        }

        static std::vector<SelectionChangeType> ToVector()
        {
            static std::vector<SelectionChangeType> returnVector =
            {
                SelectionChangeType::Add,
                SelectionChangeType::Remove,
                SelectionChangeType::Set,
            };
            
            return returnVector;
        }

        static std::string ToString(SelectionChangeType value)
        {
            switch (value)
            {
                case SelectionChangeType::Unknown: return "Unknown";
                case SelectionChangeType::Add: return "Add";
                case SelectionChangeType::Remove: return "Remove";
                case SelectionChangeType::Set: return "Set";
            }
            
            return "Unknown";
        }

        static SelectionChangeType FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return SelectionChangeType::Unknown;
                if (value == "Add") return SelectionChangeType::Add;
                if (value == "Remove") return SelectionChangeType::Remove;
                if (value == "Set") return SelectionChangeType::Set;
            }
            else
            {
                std::string valueLower = ToLower(value); 
                if (valueLower == "unknown") return SelectionChangeType::Unknown;
                if (valueLower == "add") return SelectionChangeType::Add;
                if (valueLower == "remove") return SelectionChangeType::Remove;
                if (valueLower == "set") return SelectionChangeType::Set;
            }
            
            return SelectionChangeType::Unknown;
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
