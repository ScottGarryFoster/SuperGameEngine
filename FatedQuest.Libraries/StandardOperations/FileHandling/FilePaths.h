#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Helper class to grab paths.
    /// </summary>
    class FilePaths
    {
    public:
        /// <summary>
        /// Gets the directory the application is running from.
        /// </summary>
        /// <returns>
        /// The directory the application is running from.
        /// </returns>
        static std::string ApplicationDirectory();
    };
}


