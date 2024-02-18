#pragma once
#include "../Object/Object.h"
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Methods to assist the use of ints.
    /// </summary>
    class IntHelpers : public Object
    {
    public:

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is -1 by default. </param>
        /// <returns>True means is parsed. </returns>
        inline static bool TryParse(FString& parsing, int& outValue)
        {
            outValue = -1;
            try 
            {
                outValue = std::stoi(parsing.AsStdString());
                return true;
            }
            catch (const std::exception e)
            {

            }

            return false;
        }

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is -1 by default. </param>
        /// <returns>True means is parsed. </returns>
        inline static bool TryParse(std::string& parsing, int& outValue)
        {
            outValue = -1;
            try
            {
                outValue = std::stoi(parsing);
                return true;
            }
            catch (const std::exception e)
            {

            }

            return false;
        }

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is 0 by default. </param>
        /// <returns>True means is parsed. </returns>
        inline static bool TryParse(FString& parsing, unsigned int& outValue)
        {
            outValue = 0;
            try
            {
                outValue = std::stoul(parsing.AsStdString());
                return true;
            }
            catch (const std::exception e)
            {

            }

            return false;
        }

        /// <summary>
        /// Parses a string to an Int.
        /// </summary>
        /// <param name="parsing">Pasing value. </param>
        /// <param name="outValue">The output of the parsing. Is 0 by default. </param>
        /// <returns>True means is parsed. </returns>
        inline static bool TryParse(std::string& parsing, unsigned int& outValue)
        {
            outValue = 0;
            try
            {
                outValue = std::stoul(parsing);
                return true;
            }
            catch (const std::exception e)
            {

            }

            return false;
        }
    };
}