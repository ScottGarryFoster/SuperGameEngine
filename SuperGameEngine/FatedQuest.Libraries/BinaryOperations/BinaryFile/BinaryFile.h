#pragma once
#include <string>

namespace BinaryOperations
{
    /// <summary>
    /// Represents a file which can be read from and saved to a binary file.
    /// </summary>
    class BinaryFile
    {
    public:

        virtual void AddInt(std::string key) = 0;

        virtual void SetInt(std::string key, int value) = 0;

        virtual int TryGetInt(std::string key, int defaultValue) = 0;

        virtual std::string ExportBinaryData() = 0;
    };
}