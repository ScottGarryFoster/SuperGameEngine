#pragma once
#include "BinaryFile.h"

namespace BinaryOperations
{
    /// <summary>
    /// A binary file using the StandardCLibrary.
    /// This is the type to use for SuperGameEngine.
    /// </summary>
    class StandardBinaryFile : public BinaryFile
    {
    public:

        virtual void AddInt(std::string key) override;

        virtual void SetInt(std::string key, int value) override;

        virtual int TryGetInt(std::string key, int defaultValue) override;

        virtual std::string ExportBinaryData() override;
    };
}