#pragma once
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// The base information for a file, allows the most basic tasks to be performed.
    /// </summary>
    class UniversalTemplate
    {
    public:

        /// <summary>
        /// Create an asset file based on the file path.
        /// </summary>
        /// <param name="filepath">Filepath to use as a base. </param>
        /// <returns>An asset file </returns>
        virtual std::string CreateBaseFile(const std::string& filepath) const = 0;
    };
}