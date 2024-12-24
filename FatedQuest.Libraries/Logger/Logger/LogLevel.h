#pragma once
#include "../FatedQuestReferences.h"
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// Date: 2024/12/24 14:33:40
// +------------------------------+
namespace FatedQuestLibraries
{
    /// <summary>
    /// The level of severity of the log.
    /// </summary>
    enum class LogLevel
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        /// <summary>
        /// The event is something to be concerned about but was handled.
        /// </summary>
        Info,

        /// <summary>
        /// The event has changed what occured and is indictive of something wrong.
        /// </summary>
        Warning,

        /// <summary>
        /// The event shows something has gone wrong and logic has changed route to work around it.
        /// </summary>
        Error,

        /// <summary>
        /// There was an exception which should be brought to the users attention.
        /// </summary>
        Exception,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class ELogLevel
    {
    public:
        static LogLevel Min() { return LogLevel::Info; }
        static LogLevel Max() { return LogLevel::Exception; }

        static LogLevel* ToArray()
        {
            static LogLevel returnArray[] =
            {
                LogLevel::Info,
                LogLevel::Warning,
                LogLevel::Error,
                LogLevel::Exception,
            };
            
            return returnArray;
        }

        static std::vector<LogLevel> ToVector()
        {
            static std::vector<LogLevel> returnVector =
            {
                LogLevel::Info,
                LogLevel::Warning,
                LogLevel::Error,
                LogLevel::Exception,
            };
            
            return returnVector;
        }

        static std::string ToString(LogLevel value)
        {
            switch (value)
            {
                case LogLevel::Unknown: return "Unknown";
                case LogLevel::Info: return "Info";
                case LogLevel::Warning: return "Warning";
                case LogLevel::Error: return "Error";
                case LogLevel::Exception: return "Exception";
            }
            
            return "Unknown";
        }

        static LogLevel FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return LogLevel::Unknown;
                if (value == "Info") return LogLevel::Info;
                if (value == "Warning") return LogLevel::Warning;
                if (value == "Error") return LogLevel::Error;
                if (value == "Exception") return LogLevel::Exception;
            }
            else
            {
                std::string valueLower = FatedQuestLibraries::StringHelpers::ToLower(value); 
                if (valueLower == "unknown") return LogLevel::Unknown;
                if (valueLower == "info") return LogLevel::Info;
                if (valueLower == "warning") return LogLevel::Warning;
                if (valueLower == "error") return LogLevel::Error;
                if (valueLower == "exception") return LogLevel::Exception;
            }
            
            return LogLevel::Unknown;
        }
    };
}
