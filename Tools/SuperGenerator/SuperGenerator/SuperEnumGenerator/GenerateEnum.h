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
        /// <param name="currentFolder"></param>
        /// <returns></returns>
        bool SingleFile(const std::string& enumFilepath, const std::string& outputPath, const std::string& currentFolder) const;

        /// <summary>
        /// Generate all enums within the given directory.
        /// </summary>
        /// <param name="topLevel">Directory to search. </param>
        /// <param name="superEnumExtension">File extension to filter for super enums. </param>
        /// <param name="destinationExtension">Extension to save the result as. </param>
        /// <param name="currentFolder">The current folder. Used to find relative files to this one. </param>
        void AllEnums(
            const std::string& topLevel, 
            const std::string& superEnumExtension, 
            const std::string& destinationExtension, 
            const std::string& currentFolder) const;
    };
}