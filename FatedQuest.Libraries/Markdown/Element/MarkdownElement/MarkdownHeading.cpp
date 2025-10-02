#include "MarkdownHeading.h"

#include "../../../StandardOperations/Text/StringHelpers.h"

using namespace FatedQuestLibraries;

MarkdownHeading::MarkdownHeading(const std::string& input)
{
    std::string rawHeadingInput = StringHelpers::Trim(input);
    std::tuple<DocumentElementType, MarkdownElementType> headingLevel = GetHeadingLevel(rawHeadingInput);
    m_documentElementType = std::get<0>(headingLevel);
    m_markdownElementType = std::get<1>(headingLevel);

    if (m_markdownElementType != MarkdownElementType::Unknown)
    {
        m_headingText = rawHeadingInput.substr(2, rawHeadingInput.length() - 2);
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
    if (m_markdownElementType != MarkdownElementType::Unknown)
    {
        return "# " + m_headingText;
    }
    else
    {
        return m_headingText;
    }
}

std::tuple<DocumentElementType, MarkdownElementType> MarkdownHeading::GetHeadingLevel(const std::string& input) const
{
    std::tuple answer = { DocumentElementType::Unknown, MarkdownElementType::Unknown };
    if (input.empty())
    {
        return answer;
    }

    int heading = 0;
    for (size_t c = 0; c < input.size(); ++c)
    {
        if (c == '#')
        {
            ++heading;
        }
        else
        {
            break;
        }
    }

    switch (heading)
    {
        case 1: answer = { DocumentElementType::Heading1, MarkdownElementType::Heading1 }; return answer;
    }

    return answer;
}
