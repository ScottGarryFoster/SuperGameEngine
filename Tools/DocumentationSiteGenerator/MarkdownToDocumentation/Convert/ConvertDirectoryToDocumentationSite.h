#pragma once
#include "ConversionResult.h"

namespace MarkdownToDocumentation
{
    /// <summary>
    /// Converts text to a publishable documentation website.
    /// </summary>
    class ConvertDirectoryToDocumentationSite
    {
        /// <summary>
        /// Convert the source directory files into a documentation site in the destination location.
        /// </summary>
        /// <param name="source">The source of the documentation. </param>
        /// <param name="destination">The location of the final site. </param>
        /// <returns>The result of the conversion. </returns>
        virtual ConversionResult ConvertDirectory(const std::string& source, const std::string& destination) = 0;
    };
}
