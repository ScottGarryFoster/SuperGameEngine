#pragma once
#include "Element/MarkdownElement.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single element contained with a document.
    /// </summary>
    class MarkdownHeading : public virtual MarkdownElement
    {
    public:
        /// <summary>
        /// Create a heading from the complete input text.
        /// </summary>
        /// <param name="input">Input text. </param>
        MarkdownHeading(const std::string& input);

        /// <summary>
        /// The pure type of the document element.
        /// </summary>
        /// <returns>The pure type of the document element. </returns>
        virtual DocumentElementType GetType() const override;

        /// <summary>
        /// The pure type of the markdown element.
        /// </summary>
        /// <returns>The pure type of the markdown element. </returns>
        virtual MarkdownElementType GetMarkdownType() const override;

        /// <summary>
        /// Get the text for this element if any.
        /// </summary>
        /// <returns>The text for this element. </returns>
        virtual std::string GetText() const override;

        /// <summary>
        /// Render the element.
        /// Write this element to render it with formatting.
        /// </summary>
        virtual std::string Render() const override;

    private:

        /// <summary>
        /// The actual text for the heading.
        /// </summary>
        std::string m_headingText;

        /// <summary>
        /// Describes the type of a single aspect of a document, the element.
        /// </summary>
        DocumentElementType m_documentElementType;

        /// <summary>
        /// Describes the type of a single aspect of a markdown document.
        /// </summary>
        MarkdownElementType m_markdownElementType;

        std::tuple<DocumentElementType, MarkdownElementType> GetHeadingLevel(const std::string& input) const;
    };
}
