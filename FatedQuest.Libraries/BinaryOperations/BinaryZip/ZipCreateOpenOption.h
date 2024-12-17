#pragma once
#include "../../StandardOperations/Text/StringHelpers.h"
#include <vector>
#include <string>


// +------------------------------+
// Generated by SuperGenerator as an
// SuperEnum. See Tools for details.
// Date: 2024/12/17 20:21:32
// +------------------------------+
namespace FatedQuestLibraries
{
    /// <summary>
    /// Describes how to open or create a zip.
    /// </summary>
    enum class ZipCreateOpenOption
    {
        /// <summary>
        /// Only used for unsuccessful parsing.
        /// </summary>
        Unknown = -1,

        CloseAfterOperation,

        LeaveOpen,

        CreateIfDoesNotExistAndLeaveOpen,

        CreateIfDoesNotExistCloseAfter,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EZipCreateOpenOption
    {
    public:
        static ZipCreateOpenOption Min() { return ZipCreateOpenOption::CloseAfterOperation; }
        static ZipCreateOpenOption Max() { return ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter; }

        static ZipCreateOpenOption* ToArray()
        {
            static ZipCreateOpenOption returnArray[] =
            {
                ZipCreateOpenOption::CloseAfterOperation,
                ZipCreateOpenOption::LeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter,
            };
            
            return returnArray;
        }

        static std::vector<ZipCreateOpenOption> ToVector()
        {
            static std::vector<ZipCreateOpenOption> returnVector =
            {
                ZipCreateOpenOption::CloseAfterOperation,
                ZipCreateOpenOption::LeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter,
            };
            
            return returnVector;
        }

        static std::string ToString(ZipCreateOpenOption value)
        {
            switch (value)
            {
                case ZipCreateOpenOption::Unknown: return "Unknown";
                case ZipCreateOpenOption::CloseAfterOperation: return "CloseAfterOperation";
                case ZipCreateOpenOption::LeaveOpen: return "LeaveOpen";
                case ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen: return "CreateIfDoesNotExistAndLeaveOpen";
                case ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter: return "CreateIfDoesNotExistCloseAfter";
            }
            
            return "Unknown";
        }

        static ZipCreateOpenOption FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                if (value == "Unknown") return ZipCreateOpenOption::Unknown;
                if (value == "CloseAfterOperation") return ZipCreateOpenOption::CloseAfterOperation;
                if (value == "LeaveOpen") return ZipCreateOpenOption::LeaveOpen;
                if (value == "CreateIfDoesNotExistAndLeaveOpen") return ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen;
                if (value == "CreateIfDoesNotExistCloseAfter") return ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter;
            }
            else
            {
                std::string valueLower = FatedQuestLibraries::StringHelpers::ToLower(value); 
                if (valueLower == "unknown") return ZipCreateOpenOption::Unknown;
                if (valueLower == "closeafteroperation") return ZipCreateOpenOption::CloseAfterOperation;
                if (valueLower == "leaveopen") return ZipCreateOpenOption::LeaveOpen;
                if (valueLower == "createifdoesnotexistandleaveopen") return ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen;
                if (valueLower == "createifdoesnotexistcloseafter") return ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter;
            }
            
            return ZipCreateOpenOption::Unknown;
        }
    };
}
