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
        virtual ~BinaryString(){}

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
    };
}