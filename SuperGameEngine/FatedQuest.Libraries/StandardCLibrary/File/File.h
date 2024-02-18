#pragma once

#include <string>
#include "../Text/FString.h"

namespace StandardCLibrary
{
    /// <summary>
    /// Gives access to Files.
    /// </summary>
    class File
    {
    public:
        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        static bool Exists(const std::string& filepath);

        /// <summary>
        /// Detirmines if the file path exists.
        /// </summary>
        /// <param name="filepath">File path to test. </param>
        /// <returns>True means exists. </returns>
        static bool Exists(const FString& filepath);
    };
}

