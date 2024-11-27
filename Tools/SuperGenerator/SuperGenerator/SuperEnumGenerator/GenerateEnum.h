#pragma once
#include <string>

namespace SuperEnumGenerator
{
    /// <summary>
    /// Generates enums.
    /// </summary>
    class GenerateEnum
    {
    public:
        /// <summary>
        /// Generates a single enum file.
        /// </summary>
        /// <param name="enumFilepath">The .enum </param>
        /// <param name="outputPath"></param>
        /// <returns></returns>
        bool SingleFile(const std::string& enumFilepath, const std::string& outputPath) const;
    };
}