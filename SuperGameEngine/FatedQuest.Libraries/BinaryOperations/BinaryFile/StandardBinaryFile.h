#pragma once
#include "BinaryFile.h"
#include "BinaryString.h"
#include <map>
#include <memory>

namespace BinaryOperations
{
    /// <summary>
    /// A binary file using the StandardCLibrary.
    /// This is the type to use for SuperGameEngine.
    /// </summary>
    class StandardBinaryFile : public BinaryFile
    {
    public:
        StandardBinaryFile();
        virtual ~StandardBinaryFile();

        virtual void AddInt(std::string key) override;

        virtual void SetInt(std::string key, int value) override;

        virtual int TryGetInt(std::string key, int defaultValue) override;

        virtual const std::string ExportBinaryData() override;

        virtual void ImportBinaryData(const std::string& data) override;

    private:
        std::map<std::string, int> m_intValues;

        /// <summary>
        /// Operations for binary strings.
        /// </summary>
        std::shared_ptr<BinaryString> m_binaryString;
    };
}