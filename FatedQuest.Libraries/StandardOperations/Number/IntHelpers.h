#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Methods to assist the use of ints.
    /// </summary>
    class IntHelpers
    {
    public:

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is -1 by default. </param>
        /// <returns>True means is parsed. </returns>
        static bool TryParse(const std::string& parsing, int& outValue);

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is 0 by default. </param>
        /// <returns>True means is parsed. </returns>
        static bool TryParse(const std::string& parsing, unsigned int& outValue);

        /// <summary>
        /// Add two ints together in a safe manner.
        /// </summary>
        /// <param name="left">First number to add. </param>
        /// <param name="right">Number to add to. </param>
        /// <returns>Result. </returns>
        /// <exception cref="std::overflow_error">
        /// If adding the two numbers together would cause an overflow or underflow.
        /// </exception>
        static int32_t SafeAddition(int32_t left, int32_t right);
    };
}