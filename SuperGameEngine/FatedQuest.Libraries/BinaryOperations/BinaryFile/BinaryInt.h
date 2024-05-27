#pragma once
#include <string>

namespace BinaryOperations
{
    /// <summary>
    /// Operations to create and read binary int.
    /// </summary>
    class BinaryInt
    {
    public:
        /// <summary>
        /// Creates a string in a standard binary format.
        /// </summary>
        /// <param name="plainText">Text in plain text. </param>
        /// <returns>Binary data. </returns>
        std::string ToBinary(const int& data);

        /// <summary>
        /// Parses a binary string into plain text.
        /// </summary>
        /// <param name="binary">Binary string. </param>
        /// <returns>Plain text string. </returns>
        int ToInt(const std::string& binary);

        /// <summary>
        /// Size of the data if it were placed in binary.
        /// </summary>
        /// <param name="data">Data you would make into binary. </param>
        /// <returns>The size of the data in binary. </returns>
        std::streampos SizeOfDataInBinary(const int& data);
    };
}