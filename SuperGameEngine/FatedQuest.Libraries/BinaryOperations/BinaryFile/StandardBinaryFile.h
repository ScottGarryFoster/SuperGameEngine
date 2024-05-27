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

        /// <summary>
        /// Add an int to the file.
        /// This means this int would be considered as part of the reading
        /// and writing process.
        /// </summary>
        /// <param name="key">What to call this int.
        /// This must be a unique name for this int.</param>
        virtual void AddInt(std::string key) override;

        /// <summary>
        /// Set the value of an int.
        /// </summary>
        /// <param name="key">Unique name for the int. </param>
        /// <param name="value">New value to set. </param>
        virtual void SetInt(std::string key, int value) override;

        /// <summary>
        /// Try to get the value of the int.
        /// Returns default if not set.
        /// </summary>
        /// <param name="key">Unique name for the int. </param>
        /// <param name="defaultValue">Default value to use if not set. </param>
        /// <returns>Value of the int or default if not found. </returns>
        virtual int TryGetInt(std::string key, int defaultValue) override;

        /// <summary>
        /// Export the data in a binary form.
        /// </summary>
        /// <returns>The data in a binary form. </returns>
        virtual const std::string ExportBinaryData() override;

        /// <summary>
        /// Import data in a binary form.
        /// Will wipe any existing data.
        /// </summary>
        /// <param name="data">Data in a binary form.</param>
        virtual void ImportBinaryData(const std::string& data) override;

    private:
        /// <summary>
        /// Indicates if an int value is set or not.
        /// </summary>
        struct IntValue
        {
        public:
            int Value = 0;
            bool IsSet = false;
        };

        /// <summary>
        /// Holds the Int values for the Binary Operations.
        /// </summary>
        std::map<std::string, IntValue> m_intValues;

        /// <summary>
        /// Operations for binary strings.
        /// </summary>
        std::shared_ptr<BinaryString> m_binaryString;

        /// <summary>
        /// Operations for binary ints.
        /// </summary>
        std::shared_ptr<BinaryInt> m_binaryInt;

        /// <summary>
        /// Move the pointer of the String Stream.
        /// </summary>
        /// <param name="stringStream">Stream to move. </param>
        /// <param name="value">Data value to use when moving. </param>
        /// <returns>Current seeked value. </returns>
        std::string MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, std::string value);

        /// <summary>
        /// Move the pointer of the String Stream.
        /// </summary>
        /// <param name="stringStream">Stream to move. </param>
        /// <param name="value">Data value to use when moving. </param>
        /// <returns>Current seeked value. </returns>
        std::string MoveStreamPointer(std::shared_ptr<FStringStream> stringStream, int value);

        /// <summary>
        /// Try to parse the given string to an int.
        /// </summary>
        /// <param name="data">Data to parse. </param>
        /// <param name="output">Output if parsed or -1 if not. </param>
        /// <returns>True means parsed. </returns>
        bool TryParseInt(std::string& data, int& output);

        /// <summary>
        /// Take the binary data and load the int key from it.
        /// Must start at the point the int keys begin.
        /// </summary>
        /// <param name="stringStream">String stream seeked to the int keys. </param>
        /// <returns>Current seeked string. </returns>
        std::string ProcessIntKeys(std::shared_ptr<FStringStream> stringStream);
    };
}