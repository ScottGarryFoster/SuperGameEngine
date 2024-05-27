#pragma once
#include <string>

namespace BinaryOperations
{
    /// <summary>
    /// Operations to create and read binary strings.
    /// </summary>
    class BinaryString
    {
    public:
        /// <summary>
        /// Creates a string in a standard binary format.
        /// </summary>
        /// <param name="plainText">Text in plain text. </param>
        /// <returns>Binary data. </returns>
        std::string ToBinary(const std::string& plainText);

        /// <summary>
        /// Parses a binary string into plain text.
        /// </summary>
        /// <param name="binary">Binary string. </param>
        /// <returns>Plain text string. </returns>
        std::string ToPlainText(const std::string& binary);

        /// <summary>
        /// Size of the data if it were placed in binary.
        /// </summary>
        /// <param name="plainText">Data you would make into binary. </param>
        /// <returns>The size of the data in binary. </returns>
        std::streampos SizeOfDataInBinary(const std::string& plainText);
    };
}