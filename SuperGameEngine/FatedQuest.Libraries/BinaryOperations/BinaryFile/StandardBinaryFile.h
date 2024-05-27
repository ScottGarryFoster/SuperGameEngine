#pragma once
#include "../../StandardCLibrary/LibraryIncludes.h"
#include "BinaryFile.h"
#include "BinaryString.h"
#include "BinaryInt.h"
#include <map>
#include <memory>

using namespace StandardCLibrary;

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

        /// <summary>
        /// Operations for binary ints.
        /// </summary>
        std::shared_ptr<BinaryInt> m_binaryInt;

        std::string MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, std::string value);
        std::string MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, int value);

        bool TryParseInt(std::string& data, int& output);
    };
}