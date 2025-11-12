#pragma once
#include <memory>

#include "DocumentElementType.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single element contained with a document.
    /// </summary>
    class DocumentElement
    {
    public:

        /// <summary>
        /// The pure type of the document element.
        /// </summary>
        /// <returns>The pure type of the document element. </returns>
        virtual DocumentElementType GetType() const = 0;

        /// <summary>
        /// Get the text for this element if any.
        /// </summary>
        /// <returns>The text for this element. </returns>
        virtual std::string GetText() const = 0;

        /// <summary>
        /// Render the element.
        /// Write this element to render it with formatting.
        /// </summary>
        virtual std::string Render() const = 0;
    };
}
