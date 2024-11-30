#pragma once
#include <string>
#include <vector>

namespace FatedQuestLibraries
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
        /// Split string into pieces.
        /// </summary>
        /// <param name="toSplit">Source to split. </param>
        /// <param name="by">Place to split by. </param>
        /// <returns>Pieces split into. </returns>
        static std::vector<std::string> Split(const std::string& toSplit, const std::string& by);

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
    };
}