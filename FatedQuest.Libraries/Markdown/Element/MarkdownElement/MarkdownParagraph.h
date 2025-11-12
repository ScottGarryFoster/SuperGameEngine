#pragma once
#include "MarkdownTextStyle.h"
#include "MarkdownTextStyleSpecialAttribute.h"
#include "Element/MarkdownElement.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A single element contained with a document.
    /// </summary>
    class MarkdownParagraph : public virtual MarkdownElement
    {
    public:
        /// <summary>
        /// Create a heading from the complete input text.
        /// </summary>
        /// <param name="input">Input text. </param>
        MarkdownParagraph(const std::string& input);

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

        /// <summary>
        /// Determines whether the given input would create a valid version of this element.
        /// </summary>
        /// <param name="input">Test Input. </param>
        /// <returns>True means this input is valid. </returns>
        /// <remarks>
        /// This is used to avoid hitting the garbage collector as the only
        /// other way to validate input would be to construct a new element.
        /// </remarks>
        virtual bool IsInputValidForElement(const std::string& input) const override;

    protected:

        /// <summary>
        /// A segment of text.
        /// Segments are in order, you may be able to use 'Style' with HTML but for
        /// something like markdown you would need to use the Opening and Closing Styles
        /// as they are indiscriminate wrappers (same opening and closing).
        /// </summary>
        struct Segment
        {
            /// <summary>
            /// The text to display.
            /// </summary>
            std::string Text;

            /// <summary>
            /// The style to use when displaying the text.
            /// </summary>
            MarkdownTextStyle Style;

            /// <summary>
            /// The style this text gained from the previous segment.
            /// </summary>
            MarkdownTextStyle OpeningStyle;

            /// <summary>
            /// The style this text is losing from previous segments.
            /// </summary>
            MarkdownTextStyle ClosingStyle;

            /// <summary>
            /// Is there Special Behaviour Applied?
            /// In the case of a link:
            /// In which case the text becomes the text in the link (unformatted).
            /// Then link target is the URL, and the LinkChildren is a formatted look at
            /// the inner text if say one does [**My text *is formatted***](#link) which
            /// ideally a user does not do but hey ho some editors will do this.
            /// In the case of an Image:
            /// Link Target becomes the Image URL.
            /// Text unformatted alt text, LinkedTextSegments the formatted alt text.
            /// </summary>
            MarkdownTextStyleSpecialAttribute SpecialAttribute;

            /// <summary>
            /// Target of the link.
            /// </summary>
            std::string LinkTarget;

            /// <summary>
            /// Formated linkable text.
            /// </summary>
            std::vector<Segment> LinkedTextSegments;
        };

        /// <summary>
        /// Returns the text as parsed segments.
        /// </summary>
        /// <returns>The parsed segments. </returns>
        std::vector<Segment> GetParsedTextSegments() const;

    private:

        /// <summary>
        /// A markdown mark and the style it is matched to, for instance ** for bold.
        /// </summary>
        struct MarkdownMarker
        {
            /// <summary>
            /// The marker to parse or re-add to text.
            /// </summary>
            std::string Marker;

            /// <summary>
            /// The style it matches to.
            /// </summary>
            MarkdownTextStyle Style;
        };

        /// <summary>
        /// All the markdown markers to parse out.
        /// </summary>
        const std::vector<MarkdownMarker> m_markers = 
        {
            {.Marker= "**", .Style= MarkdownTextStyle::Bold},
            {.Marker= "*", .Style= MarkdownTextStyle::Italic},
            {.Marker= "__", .Style= MarkdownTextStyle::Underline},
            {.Marker= "~~", .Style= MarkdownTextStyle::Strike},
            {.Marker= "==", .Style= MarkdownTextStyle::Highlight},
            {.Marker= "`", .Style= MarkdownTextStyle::InlineCode},
        };

        /// <summary>
        /// All the markers which if a line starts with these should not parse into a paragraph.
        /// </summary>
        const std::vector<std::string> m_failedStartingMarkers =
        {
            "> ", ">>",
            "# ", "##",
            "| ",
            "1. ", "2. ", "3. ", "4. ", "5. ", "6. ", "7. ", "8. ", "9. ", "10. ",
            "- ", "* ", "+ ",
            "```",
            "---","***","___",
        };

        /// <summary>
        /// Parsed Segments for the statement.
        /// </summary>
        std::vector<Segment> m_segments;

        /// <summary>
        /// True means the input provided on construction was valid.
        /// </summary>
        bool m_isValid;

        /// <summary>
        /// Parses all text into the segments for further use.
        /// </summary>
        /// <param name="text">Raw text. </param>
        /// <returns>Parsed information. </returns>
        std::vector<Segment> ParseText(const std::string& text) const;

        /// <summary>
        /// Parses a segment of text into a link or image.
        /// </summary>
        /// <param name="i">Location in the large piece of text. </param>
        /// <param name="input">Larger piece of text. </param>
        /// <param name="currentStyle">Current style parsed </param>
        /// <param name="result">The resulting link or image segment. </param>
        /// <returns>True means was a link or image. </returns>
        bool ParseLinkOrImage(size_t& i, const std::string& input, MarkdownTextStyle currentStyle, Segment& result) const;

        /// <summary>
        /// Handles and moves the pointer if there is an escape marker.
        /// </summary>
        /// <param name="text">Larger piece of text. </param>
        /// <param name="buffer">The buffer used to keep the text for the segment. </param>
        /// <param name="i">The current pointer. </param>
        /// <returns>True means there was an escape marker. </returns>
        bool HandleEscapeMarker(const std::string& text, std::string& buffer, size_t& i) const;

        /// <summary>
        /// Parses a given style into the text required to represent it.
        /// </summary>
        /// <param name="style">Style to parse. </param>
        /// <returns>Text which represents it. </returns>
        std::string MarkdownTextStyleToText(const MarkdownTextStyle& style) const;
    };
}
