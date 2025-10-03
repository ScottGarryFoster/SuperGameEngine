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
        /// How the heading should be rendered in Markdown.
        /// </summary>
        std::string m_markdownRender;

        /// <summary>
        /// Describes the type of a single aspect of a document, the element.
        /// </summary>
        DocumentElementType m_documentElementType;

        /// <summary>
        /// Describes the type of a single aspect of a markdown document.
        /// </summary>
        MarkdownElementType m_markdownElementType;

        /// <summary>
        /// Get the heading level as the types.
        /// </summary>
        /// <param name="input">Raw input from the line in the document. </param>
        /// <returns>The type of heading and the heading text itself. </returns>
        std::tuple<DocumentElementType, MarkdownElementType, std::string> GetHeadingLevel(const std::string& input) const;

        /// <summary>
        /// Converts a heading level (as a MarkdownElementType) to an int.
        /// </summary>
        /// <param name="type">The type of the element, only Heading levels supported. </param>
        /// <returns>The heading level, so heading 2 would be 2. 0 means not supported. </returns>
        uint8_t HeadingLevelToInt(MarkdownElementType type) const;

        /// <summary>
        /// Extract heading level and text when the input is using the markdown "# Heading" notation.
        /// </summary>
        /// <param name="input">Raw input from the line. </param>
        /// <returns>
        /// The heading level (0 failed, 2 would mean heading 2).
        /// std::string, is the extracted text, empty when invalid.
        /// </returns>
        std::tuple<int, std::string> ExtractHeadingTextAndLevelWhenUsingHashNotation(const std::string& input) const;
    };
}
