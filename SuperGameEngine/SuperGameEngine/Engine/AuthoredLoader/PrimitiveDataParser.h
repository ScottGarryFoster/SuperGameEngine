#pragma once
#include <memory>
#include "ParsedData.h"
#include "PrimitiveData.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Parses primitive data into useable structures.
    /// </summary>
    class PrimitiveDataParser
    {
    public:
        /// <summary>
        /// Parse the given data into Parsed data.
        /// </summary>
        /// <param name="primitiveData">
        /// Primitive Data in a String format.
        /// </param>
        /// <returns>A parsed version of the data. </returns>
        virtual const std::shared_ptr<ParsedData> ParseData(const std::shared_ptr<PrimitiveData> primitiveData) = 0;
    };
}