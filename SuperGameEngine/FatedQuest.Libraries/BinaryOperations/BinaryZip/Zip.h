#pragma once
#include <string>
#include "ZipCreateOpenOption.hpp"

namespace BinaryOperations
{
    /// <summary>
    /// A zip file.
    /// </summary>
    class Zip
    {
    public:
        /// <summary>
        /// Creates an empty zip.
        /// </summary>
        /// <param name="filename">Zip filename to create. </param>
        /// <param name="options"></param>
        /// <returns></returns>
        virtual bool CreateZip(const std::string& filename, const std::vector<std::string>& filenames, const ZipCreateOpenOption& options) = 0;
    };
}