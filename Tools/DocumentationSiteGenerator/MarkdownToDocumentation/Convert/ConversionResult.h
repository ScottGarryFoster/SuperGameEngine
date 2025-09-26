#pragma once
#include <string>

namespace MarkdownToDocumentation
{
    /// <summary>
    /// The result from a conversion.
    /// </summary>
    struct ConversionResult
    {
    public:

        /// <summary>
        /// True means converted.
        /// </summary>
        bool Converted = false;

        /// <summary>
        /// If not why not.
        /// </summary>
        std::string ErrorMessage;
    };
}
