#pragma once
#include <vector>
#include <string>

namespace SuperGameEngine
{
    /// <summary>
    /// How to treat a window once it exits it's update/draw operations.
    /// </summary>
    enum class WindowExit
    {
        /// <summary>
        /// Used when converting to return an unknown value.
        /// </summary>
        Unknown,

        /// <summary>
        /// Settings or user input has made it clear closing the application is
        /// the ideal operation.
        /// </summary>
        Close,
        
        /// <summary>
        /// The settings for loading the window have changed and the window should be closed
        /// and reopenned.
        /// </summary>
        Restart,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EWindowExit
    {
    public:
        static WindowExit Min() { return WindowExit::Close; }
        static WindowExit Max() { return WindowExit::Restart; }
        static WindowExit* ToArray()
        {
            static WindowExit arr[] =
            {
                WindowExit::Close,
                WindowExit::Restart,
            };

            return arr;
        }

        static std::vector<WindowExit> ToVector()
        {
            static std::vector<WindowExit> returnVector =
            {
                WindowExit::Close,
                WindowExit::Restart,
            };

            return returnVector;
        }

        static std::string ToString(WindowExit value)
        {
            switch (value)
            {
            case WindowExit::Unknown: return "Unknown";
            case WindowExit::Close: return "Close";
            case WindowExit::Restart: return "Restart";
            }

            return "Unknown";
        }

        static WindowExit FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                std::string stringValue = value;
                if (stringValue == "Unknown") return WindowExit::Unknown;
                if (stringValue == "Close") return WindowExit::Close;
                if (stringValue == "Restart") return WindowExit::Restart;
            }
            else
            {
                std::string stringValue = ToLower(value);
                if (stringValue == "unknown") return WindowExit::Unknown;
                if (stringValue == "close") return WindowExit::Close;
                if (stringValue == "restart") return WindowExit::Restart;
            }

            return WindowExit::Unknown;
        }

    private:

        static std::string ToLower(const std::string input)
        {
            std::string toLower = input;
            for (char& c : toLower)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    c = c - 'A' + 'a';
                }
            }

            return input;
        }
    };
}