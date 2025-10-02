#pragma once
#include "DocumentElement.h"
#include "MarkdownElementType.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single element contained with a document.
    /// </summary>
    class MarkdownElement : public virtual DocumentElement
    {
    public:

        /// <summary>
        /// The pure type of the markdown element.
        /// </summary>
        /// <returns>The pure type of the markdown element. </returns>
        virtual MarkdownElementType GetMarkdownType() const = 0;
    };
}
