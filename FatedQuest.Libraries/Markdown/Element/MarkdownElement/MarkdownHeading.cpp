#include "MarkdownHeading.h"

#include "../../../StandardOperations/Text/StringHelpers.h"
#include "Logger/Log.h"

using namespace FatedQuestLibraries;

MarkdownHeading::MarkdownHeading(const std::string& input)
{
    std::string rawHeadingInput = StringHelpers::Trim(input);
    std::tuple<DocumentElementType, MarkdownElementType, std::string> headingLevel = GetHeadingLevel(rawHeadingInput);
    m_documentElementType = std::get<0>(headingLevel);
    m_markdownElementType = std::get<1>(headingLevel);

    if (m_markdownElementType != MarkdownElementType::Unknown)
    {
        m_headingText = std::get<2>(headingLevel);

        m_markdownRender = {};
        int headingAsNumber = HeadingLevelToInt(m_markdownElementType);
        for (int h = 0; h < headingAsNumber; ++h)
        {
            m_markdownRender += "#";
        }

        m_markdownRender += " " + m_headingText;
    }
    else
    {
        m_headingText = "Error: Not a heading.";
    }
}

DocumentElementType MarkdownHeading::GetType() const
{
    return m_documentElementType;
}

MarkdownElementType MarkdownHeading::GetMarkdownType() const
{
    return m_markdownElementType;
}

std::string MarkdownHeading::GetText() const
{
    return m_headingText;
}

std::string MarkdownHeading::Render() const
{
    if (m_markdownElementType == MarkdownElementType::Unknown)
    {
        return m_headingText;
    }

    return m_markdownRender;
}

std::tuple<DocumentElementType, MarkdownElementType, std::string> MarkdownHeading::GetHeadingLevel(const std::string& input) const
{
    std::tuple answer = { DocumentElementType::Unknown, MarkdownElementType::Unknown, input };
    if (input.empty())
    {
        return answer;
    }

    std::string headingText = input;
    int heading = 0;
    if (input[0] == '#')
    {
        std::tuple<int, std::string> extracted = ExtractHeadingTextAndLevelWhenUsingHashNotation(input);
        heading = std::get<0>(extracted);
        headingText = std::get<1>(extracted);
    }
    else
    {
        // TODO: The second way you can do heading in Markdown here.
    }

    switch (heading)
    {
        case 1: answer = { DocumentElementType::Heading1, MarkdownElementType::Heading1, headingText }; return answer;
        case 2: answer = { DocumentElementType::Heading2, MarkdownElementType::Heading2, headingText }; return answer;
        case 3: answer = { DocumentElementType::Heading3, MarkdownElementType::Heading3, headingText }; return answer;
        case 4: answer = { DocumentElementType::Heading4, MarkdownElementType::Heading4, headingText }; return answer;
        case 5: answer = { DocumentElementType::Heading5, MarkdownElementType::Heading5, headingText }; return answer;
        case 6: answer = { DocumentElementType::Heading6, MarkdownElementType::Heading6, headingText }; return answer;
    }

    return answer;
}

uint8_t MarkdownHeading::HeadingLevelToInt(MarkdownElementType type) const
{
    switch (type)
    {
        case MarkdownElementType::Heading1: return 1;
        case MarkdownElementType::Heading2: return 2;
        case MarkdownElementType::Heading3: return 3;
        case MarkdownElementType::Heading4: return 4;
        case MarkdownElementType::Heading5: return 5;
        case MarkdownElementType::Heading6: return 6;

        default:
            Log::Error("Heading level not supported. Given: " + EMarkdownElementType::ToString(type), 
                "uint8_t MarkdownHeading::HeadingLevelToInt() const");
            return 0;
    }
}

std::tuple<int, std::string> MarkdownHeading::ExtractHeadingTextAndLevelWhenUsingHashNotation(
    const std::string& input) const
{
    std::string headingText = StringHelpers::Trim(input);
    int headingNumber = 0;
    std::tuple answer = { headingNumber, headingText };

    size_t headingBreak = 0;
    for (size_t c = 0; c < input.length(); ++c)
    {
        char current = input[c];
        if (current == '#')
        {
            ++headingNumber;
        }
        else
        {
            headingBreak = c;
            break;
        }
    }

    bool foundSpace = false;
    bool validHeading = false;
    size_t startOfHeadingText = 0;
    for (size_t c = headingBreak; c < input.length(); ++c)
    {
        char current = input[c];
        if (!foundSpace)
        {
            if (current == ' ')
            {
                foundSpace = true;
            }
        }
        else
        {
            if (current != ' ')
            {
                validHeading = true;
                startOfHeadingText = c;
                break;
            }
        }
    }

    // Requires:
    // 1. A space between # and the text.
    // 2. Some non-space text to start the heading off.
    // Technically all spaces could be a valid heading but I do not want these for this parser.
    if (!validHeading)
    {
        return answer;
    }

    headingText = input.substr(startOfHeadingText, input.length() - startOfHeadingText);

    return { headingNumber, headingText };
}