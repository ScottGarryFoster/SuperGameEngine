#include "MarkdownParagraph.h"

#include <stack>

#include "Text/StringHelpers.h"

using namespace FatedQuestLibraries;

MarkdownParagraph::MarkdownParagraph(const std::string& input)
{
    m_isValid = IsInputValidForElement(input);
    if (!input.empty() && m_isValid)
    {
        m_segments = ParseText(input);
    }
}

DocumentElementType MarkdownParagraph::GetType() const
{
    if (m_isValid)
    {
        return DocumentElementType::Paragraph;
        
    }

    return DocumentElementType::Unknown;
}

MarkdownElementType MarkdownParagraph::GetMarkdownType() const
{
    if (m_isValid)
    {
        return MarkdownElementType::Paragraph;

    }

    return MarkdownElementType::Unknown;
}

std::string MarkdownParagraph::GetText() const
{
    return {};
}

std::string MarkdownParagraph::Render() const
{
    std::string returnString = {};
    for (const Segment& segment : m_segments)
    {
        if (segment.SpecialAttribute == MarkdownTextStyleSpecialAttribute::None)
        {
            returnString += MarkdownTextStyleToText(segment.OpeningStyle) + segment.Text + MarkdownTextStyleToText(segment.ClosingStyle);
        }
        else
        {
            // Right now there are two special types so we can just render like this.
            if (segment.SpecialAttribute == MarkdownTextStyleSpecialAttribute::Link)
            {
                returnString += '[';
                
            }
            else
            {
                returnString += "![";
                
            }

            // Link or image within an image is not supported so do not worry about that.
            for (const Segment& innerSegment : segment.LinkedTextSegments)
            {
                returnString += MarkdownTextStyleToText(innerSegment.OpeningStyle) + innerSegment.Text + MarkdownTextStyleToText(innerSegment.ClosingStyle);
            }
            returnString += "](" + segment.LinkTarget + ')';
        }
    }


    return returnString;
}

bool MarkdownParagraph::IsInputValidForElement(const std::string& input) const
{
    if (input.empty())
    {
        return false;
    }

    std::string trimmed = StringHelpers::Trim(input);
    if (trimmed.empty())
    {
        return false;
    }

    const std::vector<std::string> m_failedStartingMarkersStartingWith =
    {
        "> ", ">> ",
        "# ", "## ", "### ", "#### ", "#####", "######",
        "| ",
        "1. ", "2. ", "3. ", "4. ", "5. ", "6. ", "7. ", "8. ", "9. ", "10. ",
        "- ", "* ", "+ ",
        "```",
    };

    for (const std::string& marker : m_failedStartingMarkersStartingWith)
    {
        if (trimmed.starts_with(marker))
        {
            return false;
        }
    }

    const std::vector<std::string> m_failedStartingMarkersWholeLines =
    {
        "***", "---", "___",
    };

    for (const std::string& marker : m_failedStartingMarkersWholeLines)
    {
        if (trimmed.compare(0, trimmed.size(), marker) == 0)
        {
            return false;
        }
    }

    return true;
}

std::vector<MarkdownParagraph::Segment> MarkdownParagraph::GetParsedTextSegments() const
{
    return m_segments;
}

bool MarkdownParagraph::HandleEscapeMarker(const std::string& text, std::string& buffer, size_t& i) const
{
    bool foundEscape = false;
    if (text[i] == '\\' && i + 1 < text.size())
    {
        foundEscape = true;
        bool markerWasEscaped = false;
        for (auto const& m : m_markers)
        {
            if (text.compare(i + 1, m.Marker.size(), m.Marker) == 0)
            {
                buffer += m.Marker;
                i += 1 + m.Marker.size();
                markerWasEscaped = true;
                break;
            }
        }

        const std::vector<std::string> specialMarker = { "!\\[", "!", "[" };
        for (auto const& m : specialMarker)
        {
            if (text.compare(i + 1, m.size(), m) == 0)
            {
                // Because \\!\\[ is the way to escape an image in markdown we need a work around.
                // The other way would be to do a replace the escape characters in the string.
                if (m == "!\\[")
                {
                    buffer += "![";
                }
                else
                {
                    buffer += m;
                }
                
                i += 1 + m.size();
                markerWasEscaped = true;
                break;
            }
        }

        if (!markerWasEscaped)
        {
            // "markerWasEscaped" is true when a marker is found next.
            // That situation we want to ensure it is ignored (we jump to the character after)
            buffer.push_back(text[i]);
            ++i;
        }
    }

    return foundEscape;
}

std::string MarkdownParagraph::MarkdownTextStyleToText(const MarkdownTextStyle& style) const
{
    if (style == MarkdownTextStyle::Plain)
    {
        return {};
    }

    std::string returnString = {};
    for (const MarkdownMarker& marker : m_markers)
    {
        if (EMarkdownTextStyle::HasFlag(style, marker.Style))
        {
            returnString += marker.Marker;
        }
    }

    return returnString;
}

std::vector<MarkdownParagraph::Segment> MarkdownParagraph::ParseText(const std::string& text) const
{
    std::vector<Segment> segments;
    std::stack<MarkdownTextStyle> styleStack;
    styleStack.push(MarkdownTextStyle::Plain);
    std::string buffer;
    size_t i = 0;

    while (i < text.size())
    {
        if (HandleEscapeMarker(text, buffer, i))
        {
            continue;
        }

        // Link or Image
        if (text[i] == '!' || text[i] == '[')
        {
            Segment linkSeg;
            size_t backup = i;
            if (ParseLinkOrImage(i, text, styleStack.top(), linkSeg))
            {
                if (!buffer.empty())
                {
                    segments.emplace_back(buffer, styleStack.top());
                    buffer.clear();
                }

                // Add the parsed segment and keep parsing.
                segments.push_back(std::move(linkSeg));
                continue;
            }

            // Restore pointer if not a valid link/image
            i = backup;
        }

        bool spaceBufferState = false;
        bool matched = false;
        for (auto const& m : m_markers)
        {
            bool foundMarker = text.compare(i, m.Marker.size(), m.Marker) == 0;
            if (foundMarker)
            {
                if (EMarkdownTextStyle::HasFlag(styleStack.top(), m.Style))
                {
                    // Potentially closing
                    if (i > 0 && text[i - 1] == ' ')
                    {
                        // There was a space before the marker, disregard.
                        foundMarker = false;

                        // Ignore all future parsing and continue at the next character after a space.
                        // This ensures that you cannot enter ** and get italic even though there is a space
                        // between it and text.
                        spaceBufferState = true;
                        break;
                    }
                }
                else
                {
                    // Potentially opening
                    if (i + m.Marker.size() < text.size() && text[i + m.Marker.size()] == ' ')
                    {
                        // There was a space before the marker, disregard.
                        foundMarker = false;

                        // Ignore all future parsing and continue at the next character after a space.
                        // This ensures that you cannot enter ** and get italic even though there is a space
                        // between it and text.
                        spaceBufferState = true;
                        break;
                    }
                }
            }

            if (foundMarker)
            {
                // flush current buffer
                if (!buffer.empty()) 
                {
                    segments.emplace_back(buffer, styleStack.top());
                    buffer.clear();
                }

                bool toggleIsValid = i > 0 && text[i - 1] != ' ';

                // toggle style
                if ((styleStack.top() & m.Style) == m.Style)
                {
                    MarkdownTextStyle newStyle = static_cast<MarkdownTextStyle>(
                        static_cast<int>(styleStack.top()) &
                        ~static_cast<int>(m.Style));
                    styleStack.pop();
                    styleStack.push(newStyle);
                }
                else
                {
                    MarkdownTextStyle newStyle = static_cast<MarkdownTextStyle>(
                        static_cast<int>(styleStack.top()) |
                        static_cast<int>(m.Style));
                    styleStack.push(newStyle);
                }

                i += m.Marker.size();
                matched = true;
                break;
            }
        }

        if (spaceBufferState)
        {
            while (text[i] != ' ')
            {
                buffer.push_back(text[i]);
                i++;
            }
            buffer.push_back(' ');
            i++;

            spaceBufferState = false;
        }
        else if (!matched)
        {
            buffer.push_back(text[i]);
            i++;
        }
    }

    if (!buffer.empty())
    {
        segments.emplace_back(buffer, styleStack.top());
    }

    Segment* lastSegment = nullptr;
    MarkdownTextStyle lastStyle = MarkdownTextStyle::Plain;
    for (Segment& segment : segments)
    {
        MarkdownTextStyle opening = segment.Style & ~lastStyle;
        MarkdownTextStyle closing = lastStyle & ~segment.Style;
        lastStyle = segment.Style;

        segment.OpeningStyle = opening;

        // The closing is the style as compared to this...
        // However, we arrange the segments as text, open, close so we need to
        // retroactively update the closing style.
        if (lastSegment != nullptr)
        {
            lastSegment->ClosingStyle = closing;
        }

        lastSegment = &segment;
    }

    if (!segments.empty())
    {
        MarkdownTextStyle closing = lastStyle & ~MarkdownTextStyle::Plain;
        segments.back().ClosingStyle = closing;
    }


    return segments;
}

bool MarkdownParagraph::ParseLinkOrImage(
    size_t& i, const 
    std::string& input, 
    MarkdownTextStyle currentStyle,
    Segment& result) const
{
    bool isImage = false;
    size_t start = i;

    if (input[i] == '!') {
        isImage = true;
        i++;
    }
    if (i >= input.size() || input[i] != '[')
    {
        i = start;
        return false;
    }

    i++; // Skip '['
    std::string innerContent;
    int depth = 1;
    while (i < input.size() && depth > 0)
    {
        if (input[i] == '[')
        {
            depth++;
        }
        else if (input[i] == ']')
        {
            depth--;
            if (depth == 0) break;
        }

        if (depth > 0)
        {
            innerContent.push_back(input[i]);
        }
        i++;
    }
    if (i >= input.size() || input[i] != ']')
    {
        i = start;
        return false;
    }
    i++; // skip ']'

    if (i >= input.size() || input[i] != '(')
    {
        i = start;
        return false;
    }

    i++; // skip '('
    std::string url;
    while (i < input.size() && input[i] != ')')
    {
        url.push_back(input[i]);
        i++;
    }
    if (i < input.size() && input[i] == ')')
    {
        i++;
    }

    // recursively parse formatted link/alt text
    std::vector<Segment> innerSegs = ParseText(innerContent);

    result.SpecialAttribute = isImage ? MarkdownTextStyleSpecialAttribute::Image : MarkdownTextStyleSpecialAttribute::Link;
    result.LinkTarget = url;
    result.Style = currentStyle;
    result.LinkedTextSegments = std::move(innerSegs);
    result.Text = innerContent;

    return true;
}
