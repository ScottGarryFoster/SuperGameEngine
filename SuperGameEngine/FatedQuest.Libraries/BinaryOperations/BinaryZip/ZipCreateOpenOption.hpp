#pragma once
#include "../../StandardCLibrary/LibraryIncludes.h"
#include "../../Logging/Logger.h"

using namespace StandardCLibrary;

namespace BinaryOperations
{
    /// <summary>
    /// Describes how to open or create a zip.
    /// </summary>
    enum class ZipCreateOpenOption
    {
        /// <summary>
        /// Used when converting to return an unknown value.
        /// </summary>
        Unknown,

        CloseAfterOperation,
        LeaveOpen,
        CreateIfDoesNotExistAndLeaveOpen,
        CreateIfDoesNotExistCloseAfter,
    };

    /// <summary>
    /// Accompanies enums to provide extra functionality.
    /// </summary>
    class EZipCreateOpenOption : public Object
    {
    public:
        static ZipCreateOpenOption Min() { return ZipCreateOpenOption::CloseAfterOperation; }
        static ZipCreateOpenOption Max() { return ZipCreateOpenOption::LeaveOpen; }
        static ZipCreateOpenOption* ToArray()
        {
            static ZipCreateOpenOption arr[] =
            {
                ZipCreateOpenOption::CloseAfterOperation,
                ZipCreateOpenOption::LeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen,
                ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter,
            };

            return arr;
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

            Logger::Assert(NotImplementedException(), FString("EZipCreateOpenOption"), FString("ToString"),
                FString("No string value for a ZipCreateOpenOption requested."));
            return "Unknown";
        }

        static ZipCreateOpenOption FromString(std::string value, bool checkCase = true)
        {
            if (checkCase)
            {
                FString stringValue = value;
                if (stringValue == "Unknown") return ZipCreateOpenOption::Unknown;
                if (stringValue == "CloseAfterOperation") return ZipCreateOpenOption::CloseAfterOperation;
                if (stringValue == "LeaveOpen") return ZipCreateOpenOption::LeaveOpen;
                if (stringValue == "CreateIfDoesNotExistAndLeaveOpen") return ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen;
                if (stringValue == "CreateIfDoesNotExistCloseAfter") return ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter;
            }
            else
            {
                FString stringValueLower = value;
                stringValueLower.ConvertToLower();
                if (stringValueLower == FString("Unknown").ToLower()) return ZipCreateOpenOption::Unknown;
                if (stringValueLower == FString("CloseAfterOperation").ToLower()) return ZipCreateOpenOption::CloseAfterOperation;
                if (stringValueLower == FString("LeaveOpen").ToLower()) return ZipCreateOpenOption::LeaveOpen;
                if (stringValueLower == FString("CreateIfDoesNotExistAndLeaveOpen").ToLower()) return ZipCreateOpenOption::CreateIfDoesNotExistAndLeaveOpen;
                if (stringValueLower == FString("CreateIfDoesNotExistCloseAfter").ToLower()) return ZipCreateOpenOption::CreateIfDoesNotExistCloseAfter;
            }

            Logger::Assert(NotImplementedException(), FString("EZipCreateOpenOption"), FString("FromString"),
                FString("No Zip Create Open Option value for a button requested: ") + value);
            return ZipCreateOpenOption::Unknown;
        }
    };
}