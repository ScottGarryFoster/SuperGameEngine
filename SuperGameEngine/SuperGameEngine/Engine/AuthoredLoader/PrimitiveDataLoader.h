#pragma once
#include <memory>
#include <string>

#include "PrimitiveData.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Loads basic data from an external source.
    /// </summary>
    /// <remark>
    /// This exists to abstract file formats away and allow XML, JSON or other formats without changing other systems.
    /// </remark>
    class PrimitiveDataLoader
    {
    public:
        /// <summary>
        /// Extract basic data into a portable source.
        /// </summary>
        /// <param name="data">Data to extract from. </param>
        /// <returns>Extracted data. Will be empty if could not extract. </returns>
        virtual const std::shared_ptr<PrimitiveData> ExtractData(const std::string& data) = 0;
    };
}