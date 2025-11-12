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

        /// <summary>
        /// Determines whether the given input would create a valid version of this element.
        /// </summary>
        /// <param name="input">Test Input. </param>
        /// <returns>True means this input is valid. </returns>
        /// <remarks>
        /// This is used to avoid hitting the garbage collector as the only
        /// other way to validate input would be to construct a new element.
        /// </remarks>
        virtual bool IsInputValidForElement(const std::string& input) const = 0;
    };
}
