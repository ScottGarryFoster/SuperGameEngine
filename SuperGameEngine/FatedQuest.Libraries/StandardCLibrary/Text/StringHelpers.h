#pragma once
#include <string>
#include <vector>

namespace StandardCLibrary
{
    /// <summary>
    /// Methods which standardise string based operations.
    /// </summary>
    class StringHelpers
    {
    public:
        /// <summary>
        /// Joins the given string together with the separator.
        /// </summary>
        /// <param name="separator">Separator to use. </param>
        /// <param name="list">List of strings to use. </param>
        /// <returns>Joined string. </returns>
        static std::string Join(const std::string& separator, const std::vector<std::string>& list);

        /// <summary>
        /// Splits a thing into many smaller strings.
        /// </summary>
        /// <param name="separator">Separator to use when spliting. </param>
        /// <param name="input">String to split. </param>
        /// <returns>The final split string. </returns>
        static std::vector<std::string> Split(const std::string& separator, const std::string& input);

        /// <summary>
        /// Trims spaces from both sides.
        /// </summary>
        /// <param name="input">Input to have spaces trimmed. </param>
        /// <returns>Trimmed String. </returns>
        static std::string Trim(const std::string& input);

        /// <summary>
        /// Converts the given to lowercase.
        /// </summary>
        /// <param name="input">Input to convert. </param>
        static void ConvertToLower(std::string& input);

        /// <summary>
        /// Returns a lowercase version of the given.
        /// </summary>
        /// <param name="input">Input to convert. </param>
        /// <returns>Lowercase version of the given. </returns>
        static std::string ToLower(const std::string& input);

        /// <summary>
        /// Converts the given to uppercase.
        /// </summary>
        /// <param name="input">Input to convert. </param>
        static void ConvertToUpper(std::string& input);

        /// <summary>
        /// Returns a uppercase version of the given.
        /// </summary>
        /// <param name="input">Input to convert. </param>
        /// <returns>Uppercase version of the given. </returns>
        static std::string ToUpper(const std::string& input);

        /// <summary>
        /// Converts a string from Unsigned Char.
        /// </summary>
        /// <param name="input">Unsigned char to find text. </param>
        /// <returns>String representation. </returns>
        static std::string ConvertFrom(const std::vector<unsigned char>& input);

        /// <summary>
        /// Compares strings.
        /// </summary>
        /// <param name="left">Left to check. </param>
        /// <param name="right">Right to check against. </param>
        /// <param name="ignorecase">True means do not look at letter casing. </param>
        /// <returns>True means equal. </returns>
        static bool Equals(const std::string& left, const std::string& right, bool ignorecase = false);

        /// <summary>
        /// Figures out the given is empty or contains nothing more than spaces.
        /// </summary>
        /// <param name="input">Input to test. </param>
        /// <returns>True means string contains nothing or is just whitespace. </returns>
        static bool IsEmptyOrWhitespace(const std::string& input);
    };
}