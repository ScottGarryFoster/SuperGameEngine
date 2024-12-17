#pragma once
#include <string>

namespace FatedQuestLibraries
{
    /// <summary>
    /// Represents an XML Attribute
    /// </summary>
    class XMLAttribute
    {
    public:
        /// <summary>
        /// Returns the name of the attribute.
        /// </summary>
        /// <returns>The name of the attribute. </returns>
        virtual const std::string Name() const = 0;

        /// <summary>
        /// The value of the attribute.
        /// </summary>
        /// <returns>
        /// The value of the attribute.
        /// Could be empty if nothing is given.
        /// </returns>
        virtual const std::string Value() const = 0;
    };
}