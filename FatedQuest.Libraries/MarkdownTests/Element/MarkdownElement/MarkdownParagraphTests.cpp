#include <memory>
#include <gtest/gtest.h>

#include "Console/ConsoleLog.h"
#include "Element/MarkdownElement/MarkdownParagraph.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_Element_MarkdownElement
{
    class MarkdownParagraphTests : public ::testing::Test
    {
    public:

        MarkdownParagraphTests()
        {
        }

    protected:

        std::shared_ptr<ConsoleLog> m_logger;

        const char* m_errorMessage = "Error: Not a heading.";

        void SetUp() override
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto event = Log::GetEvent().lock())
            {
                event->Subscribe(m_logger);
            }
        }

        void TearDown() override
        {
            if (auto event = Log::GetEvent().lock())
            {
                event->Unsubscribe(m_logger);
            }
        }
    };

    /// <summary>
    /// This the test case we use because the render is almost irrelevant.
    /// If the render decides to close a tag **== instead of ==** it really does not matter to what we would
    /// ever use the markdown project for. In every case we would be re-rendering the segments with our own tags
    /// therefore this testcase tests the parsed segments of text.
    /// </summary>
    class MarkdownTestCase : public MarkdownParagraph
    {
    public:
        MarkdownTestCase(const std::string& input) : MarkdownParagraph(input){}

        /// <summary>
        /// Gets all the text segments.
        /// Each element in the vector is new distinct segment of text with a new style (could be given a style or taken away).
        /// </summary>
        /// <returns></returns>
        std::vector<std::unordered_map<std::string, std::string>> GetSegmentInfo() const
        {
            std::vector<Segment> segments = GetParsedTextSegments();
            auto returnVector = std::vector<std::unordered_map<std::string, std::string>>();
            for (const Segment& segment : segments)
            {
                auto map = std::unordered_map<std::string, std::string>();
                map.insert_or_assign("Text", segment.Text);
                map.insert_or_assign("Style", EMarkdownTextStyle::ToString(segment.Style));
                map.insert_or_assign("OpeningStyle", EMarkdownTextStyle::ToString(segment.OpeningStyle));
                map.insert_or_assign("ClosingStyle", EMarkdownTextStyle::ToString(segment.ClosingStyle));
                map.insert_or_assign("SpecialAttribute", EMarkdownTextStyleSpecialAttribute::ToString(segment.SpecialAttribute));
                map.insert_or_assign("LinkTarget", segment.LinkTarget);

                returnVector.emplace_back(map);
            }

            return returnVector;
        }

        /// <summary>
        /// Get just the links and images and return the children.
        /// The outer vector is each link or image.
        /// Then each of those contains the paragraphs parsed for the linked text or alt text for images.
        /// </summary>
        /// <returns></returns>
        std::vector<std::vector<std::unordered_map<std::string, std::string>>> GetLinkSegmentInfo() const
        {
            std::vector<Segment> segments = GetParsedTextSegments();
            auto returnVector = std::vector<std::vector<std::unordered_map<std::string, std::string>>>();
            for (const Segment& segment : segments)
            {
                if (segment.SpecialAttribute == MarkdownTextStyleSpecialAttribute::None)
                {
                    continue;
                }

                auto returnInnerVector = std::vector<std::unordered_map<std::string, std::string>>();
                for (const Segment& innerSegment : segment.LinkedTextSegments)
                {
                    auto map = std::unordered_map<std::string, std::string>();
                    map.insert_or_assign("Text", innerSegment.Text);
                    map.insert_or_assign("Style", EMarkdownTextStyle::ToString(innerSegment.Style));
                    map.insert_or_assign("OpeningStyle", EMarkdownTextStyle::ToString(innerSegment.OpeningStyle));
                    map.insert_or_assign("ClosingStyle", EMarkdownTextStyle::ToString(innerSegment.ClosingStyle));
                    map.insert_or_assign("SpecialAttribute", EMarkdownTextStyleSpecialAttribute::ToString(innerSegment.SpecialAttribute));
                    map.insert_or_assign("LinkTarget", innerSegment.LinkTarget);

                    returnInnerVector.emplace_back(map);
                }

                returnVector.emplace_back(returnInnerVector);
            }

            return returnVector;
        }
    };

#pragma region Basic Text

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsBoldTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "**BoldText**";

        int expectedSegments = 1;
        std::string textExpected = "BoldText";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsItalicTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "*ItalicText*";

        int expectedSegments = 1;
        std::string textExpected = "ItalicText";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Italic);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Italic);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Italic);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsHighlightTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "==HighlightText==";

        int expectedSegments = 1;
        std::string textExpected = "HighlightText";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsInlineCodeTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "`InlineCode Text`";

        int expectedSegments = 1;
        std::string textExpected = "InlineCode Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::InlineCode);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::InlineCode);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::InlineCode);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsStrikeTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "~~Strike Text~~";

        int expectedSegments = 1;
        std::string textExpected = "Strike Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Strike);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Strike);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Strike);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ReturnsUnderlineTest_WhenGivenTextMarkedUp)
    {
        // Arrange
        std::string given = "__Underline Text__";

        int expectedSegments = 1;
        std::string textExpected = "Underline Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Escaped Characters

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesBothHightlightAndBold_WhenNoEscapeCharactersUsed)
    {
        // Arrange
        std::string given = "==**Highlight Text Not Bold**==";

        int expectedSegments = 1;
        std::string textExpected = "Highlight Text Not Bold";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_DoesNotParseText_WhenCharactersAreEscaped)
    {
        // Arrange
        std::string given = "==\\*\\*Highlight Text Not Bold\\*\\*==";

        int expectedSegments = 1;
        std::string textExpected = "**Highlight Text Not Bold**";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_DoesNotParseText_WhenEscapedCharacterIsBeforeATwoCharacterMarker)
    {
        // Arrange
        std::string given = "==Highlight Text \\== still same segment==";

        int expectedSegments = 1;
        std::string textExpected = "Highlight Text == still same segment";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesTextWithBackslash_WhenBackSlashIsNotBeforeAMarker)
    {
        // Arrange
        std::string given = "==**Highlight Text\\ Not Bold**==";

        int expectedSegments = 1;
        std::string textExpected = "Highlight Text\\ Not Bold";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight | MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_HandlesTwoEscapedCharactersInARow)
    {
        // Arrange
        std::string given = "==Highlight Text \\\\== still same segment==";

        int expectedSegments = 1;
        std::string textExpected = "Highlight Text \\== still same segment";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Spaces Before Markers

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_DoesNotParseMarkers_WhenTheCharacterBeforeAMarkerIsASpace)
    {
        // Arrange
        std::string given = "Plain text ** bold text";

        int expectedSegments = 1;
        std::string textExpected = "Plain text ** bold text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_DoesCountAClosingTag_WhenTheCharacterBeforeAMarkerIsASpace)
    {
        // Arrange
        std::string given = "Plain text **bold text ** did not close** now closed";

        int expectedSegments = 3;
        std::string textExpected0 = "Plain text ";
        std::string styleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        // We do not lose bold here so there is no closing tag:
        std::string closingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected0 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected1 = "bold text ** did not close";
        std::string styleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected1 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected2 = " now closed";
        std::string styleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected2 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected0, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected0, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected0, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected0, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected0, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected1, segments.at(1).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected1, segments.at(1).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected1, segments.at(1).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected1, segments.at(1).at("ClosingStyle")) << "ClosingStyle did not match. Expected: "
            << closingStyleExpected1 << " Actual: " << segments.at(1).at("ClosingStyle");
        ASSERT_EQ(specialAttributeExpected1, segments.at(1).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected2, segments.at(2).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected2, segments.at(2).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected2, segments.at(2).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected2, segments.at(2).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected2, segments.at(2).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Standard Combinations

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_CombinesMarkers_WhenGivenBoldAndItalic)
    {
        // Arrange
        std::string given = "***Bold and Italic***";

        int expectedSegments = 1;
        std::string textExpected = "Bold and Italic";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Italic);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Italic);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Italic);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_CombinesMarkers_WhenGivenBoldAndHighlight)
    {
        // Arrange
        std::string given = "**==Bold and Highlight==**";

        int expectedSegments = 1;
        std::string textExpected = "Bold and Highlight";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_CombinesMarkersMidText_WhenSwitchingMidMarker)
    {
        // Arrange
        std::string given = "**Bold Text ==Highlight And Bold==**";

        int expectedSegments = 2;
        std::string textExpected0 = "Bold Text ";
        std::string styleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        // We do not lose bold here so there is no closing tag:
        std::string closingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected0 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected1 = "Highlight And Bold";
        std::string styleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string openingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected1 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected0, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected0, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected0, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected0, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected0, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected1, segments.at(1).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected1, segments.at(1).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected1, segments.at(1).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected1, segments.at(1).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected1, segments.at(1).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ClosesTags_WhenMarkersAreLostMidText)
    {
        // Arrange
        std::string given = "**Bold Text ==Highlight And Bold== Continued Bold**";

        int expectedSegments = 3;
        std::string textExpected0 = "Bold Text ";
        std::string styleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        // We do not lose bold here so there is no closing tag:
        std::string closingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected0 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected1 = "Highlight And Bold";
        std::string styleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold | MarkdownTextStyle::Highlight);
        std::string openingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected1 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected2 = " Continued Bold";
        std::string styleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected2 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected0, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected0, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected0, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected0, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected0, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected1, segments.at(1).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected1, segments.at(1).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected1, segments.at(1).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected1, segments.at(1).at("ClosingStyle")) << "ClosingStyle did not match. Expected: "
            << closingStyleExpected1 << " Actual: " << segments.at(1).at("ClosingStyle");
        ASSERT_EQ(specialAttributeExpected1, segments.at(1).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected2, segments.at(2).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected2, segments.at(2).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected2, segments.at(2).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected2, segments.at(2).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected2, segments.at(2).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Automatic end tags

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesTag_WhenEndMarkerNotProvided)
    {
        // Arrange
        std::string given = "**Bold Text";

        int expectedSegments = 1;
        std::string textExpected = "Bold Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesTag_WhenEndMarkerNotProvidedAndThereAreOtherMarkersOnTheLine)
    {
        // Arrange
        std::string given = "**Bold Text**__Underlined text__==Highlighted text";

        int expectedSegments = 3;
        std::string textExpected0 = "Bold Text";
        std::string styleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected0 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected1 = "Underlined text";
        std::string styleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string openingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string closingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Underline);
        std::string specialAttributeExpected1 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected2 = "Highlighted text";
        std::string styleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string openingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string closingStyleExpected2 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Highlight);
        std::string specialAttributeExpected2 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected0, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected0, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected0, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected0, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected0, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected1, segments.at(1).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected1, segments.at(1).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected1, segments.at(1).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected1, segments.at(1).at("ClosingStyle")) << "ClosingStyle did not match. Expected: "
            << closingStyleExpected1 << " Actual: " << segments.at(1).at("ClosingStyle");
        ASSERT_EQ(specialAttributeExpected1, segments.at(1).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected2, segments.at(2).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected2, segments.at(2).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected2, segments.at(2).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected2, segments.at(2).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected2, segments.at(2).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Links and Images

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesLinks_WhenGivenJustALink)
    {
        // Arrange
        std::string given = "[Link Text](Link Target)";

        int expectedSegments = 1;
        std::string textExpected = "Link Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::Link);
        std::string linkTargetExpected = "Link Target";

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
        ASSERT_EQ(linkTargetExpected, segments.at(0).at("LinkTarget")) << "LinkTarget did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesFormattingWithinLinks_WhenGivenJustALink)
    {
        // Arrange
        std::string given = "[**Link Text**](Link Target)";

        int expectedSegments = 1;
        std::string textExpected = "Link Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments = testClass->GetLinkSegmentInfo();
        ASSERT_EQ(expectedSegments, linkSegments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";
        const std::vector<std::unordered_map<std::string, std::string>>& linkInnerSegments = linkSegments.at(0);

        ASSERT_EQ(textExpected, linkInnerSegments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, linkInnerSegments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, linkInnerSegments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, linkInnerSegments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, linkInnerSegments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesImages_WhenGivenJustAnImage)
    {
        // Arrange
        std::string given = "![Image Text](Image Target)";

        int expectedSegments = 1;
        std::string textExpected = "Image Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::Image);
        std::string linkTargetExpected = "Image Target";

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
        ASSERT_EQ(linkTargetExpected, segments.at(0).at("LinkTarget")) << "LinkTarget did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ParsesFormattingWithinImages_WhenGivenJustAnImage)
    {
        // Arrange
        std::string given = "[**Image Text**](Image Target)";

        int expectedSegments = 1;
        std::string textExpected = "Image Text";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Bold);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments = testClass->GetLinkSegmentInfo();
        ASSERT_EQ(expectedSegments, linkSegments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";
        const std::vector<std::unordered_map<std::string, std::string>>& linkInnerSegments = linkSegments.at(0);

        ASSERT_EQ(textExpected, linkInnerSegments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, linkInnerSegments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, linkInnerSegments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, linkInnerSegments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, linkInnerSegments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_LinksAreEscaped_WhenAnEscapeCharacterIsFoundAtTheStart)
    {
        // Arrange
        std::string given = "\\[Link Text](Link Target)";

        int expectedSegments = 1;
        std::string textExpected = "[Link Text](Link Target)";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ImagesAreEscaped_WhenAnEscapeCharacterIsFoundAtTheStart)
    {
        // Arrange
        std::string given = "\\!\\[Link Text](Link Target)";

        int expectedSegments = 1;
        std::string textExpected = "![Link Text](Link Target)";
        std::string styleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected, segments.at(0).at("Text")) << "Text did not match.";
        ASSERT_EQ(styleExpected, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
    }

    TEST_F(MarkdownParagraphTests, GetParsedTextSegements_ImagesAreEscapedButNotLink_WhenAnEscapeCharacterIsFoundAtTheStartButNotBeforeTheLink)
    {
        // Arrange
        std::string given = "\\![Link Text](Link Target)";

        int expectedSegments = 2;
        std::string textExpected0 = "!";
        std::string styleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected0 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected0 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::None);

        std::string textExpected1 = "Link Text";
        std::string styleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string openingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string closingStyleExpected1 = EMarkdownTextStyle::ToString(MarkdownTextStyle::Plain);
        std::string specialAttributeExpected1 = EMarkdownTextStyleSpecialAttribute::ToString(MarkdownTextStyleSpecialAttribute::Link);
        std::string linkTargetExpected1 = "Link Target";

        // Act
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        ASSERT_EQ(expectedSegments, segments.size()) << "Only" << expectedSegments << " text segment should have been parsed.";

        ASSERT_EQ(textExpected0, segments.at(0).at("Text")) << "Text did not match.";
        ASSERT_EQ(styleExpected0, segments.at(0).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected0, segments.at(0).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected0, segments.at(0).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected0, segments.at(0).at("SpecialAttribute")) << "SpecialAttribute did not match. ";

        ASSERT_EQ(textExpected1, segments.at(1).at("Text")) << "Text did not match.";
        ASSERT_EQ(styleExpected1, segments.at(1).at("Style")) << "Style did not match. ";
        ASSERT_EQ(openingStyleExpected1, segments.at(1).at("OpeningStyle")) << "OpeningStyle did not match. ";
        ASSERT_EQ(closingStyleExpected1, segments.at(1).at("ClosingStyle")) << "ClosingStyle did not match. ";
        ASSERT_EQ(specialAttributeExpected1, segments.at(1).at("SpecialAttribute")) << "SpecialAttribute did not match. ";
        ASSERT_EQ(linkTargetExpected1, segments.at(1).at("LinkTarget")) << "SpecialAttribute did not match. ";
    }

#pragma endregion

#pragma region Render

    TEST_F(MarkdownParagraphTests, Render_GivesTheSameParsedTextInAsOut_WhenGivenAThreeSegmentPieceOfText)
    {
        // Arrange
        // Expected 3 segments given current tests
        std::string given = "Plain text **bold text** now closed";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        std::string render = testClass->Render();
        auto testClass2 = std::make_shared<MarkdownTestCase>(render);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        std::vector<std::unordered_map<std::string, std::string>> segments2 = testClass2->GetSegmentInfo();
        ASSERT_EQ(segments.size(), segments2.size());

        const std::string types[] = { "Text", "Style", "OpeningStyle", "ClosingStyle", "SpecialAttribute" };
        for (size_t i = 0; i < segments.size(); ++i)
        {
            for (const std::string& type : types)
            {
                std::string leftText = segments.at(i).at(type);
                std::string rightText = segments2.at(i).at(type);
                ASSERT_EQ(leftText, rightText) << "Original parse does not match new parse. Type: " << type << " index: " << i;
            }
        }
    }

    TEST_F(MarkdownParagraphTests, Render_GivesTheSameParsedTextInAsOut_WhenGivenAMoreDifficultPieceOfText)
    {
        // Arrange
        // Expected 17 segment given current tests and ensured to not close the markdown at the end.
        std::string given = "Contrary to popular belief, **Lorem Ipsum** is not simply random text. "
                            "It has roots in a piece of **==classical Latin literature== from 45 BC, "
                            "making it over 2000 years old**. Richard McClintock, a Latin professor "
                            "at Hampden-Sydney College in Virginia, looked up one of the more obscure "
                            "Latin words, consectetur, *from a Lorem Ipsum passage*, __and going through the "
                            "cites of the word in classical literature__, discovered the undoubtable source. "
                            "Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" "
                            "(The Extremes of Good and Evil) ~~by Cicero, written in 45 BC~~. This book is a treatise on "
                            "the theory of ethics, ==**very popular during** the Renaissance. *The first*== line of Lorem Ipsum, "
                            "\"Lorem ipsum dolor sit amet..\", **comes from a line in section 1.10.32.";

        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        std::string render = testClass->Render();
        auto testClass2 = std::make_shared<MarkdownTestCase>(render);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        std::vector<std::unordered_map<std::string, std::string>> segments2 = testClass2->GetSegmentInfo();
        ASSERT_EQ(segments.size(), segments2.size());

        const std::string types[] = { "Text", "Style", "OpeningStyle", "ClosingStyle", "SpecialAttribute" };
        for (size_t i = 0; i < segments.size(); ++i)
        {
            for (const std::string& type : types)
            {
                std::string leftText = segments.at(i).at(type);
                std::string rightText = segments2.at(i).at(type);
                ASSERT_EQ(leftText, rightText) << "Original parse does not match new parse. Type: " << type << " index: " << i;
            }
        }
    }

    TEST_F(MarkdownParagraphTests, Render_GivesTheSameParsedTextInAsOut_WhenGivenALink)
    {
        // Arrange
        // Expected 3 segments given current tests
        std::string given = "Plain text [bold text](hyper link) now closed";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        std::string render = testClass->Render();
        auto testClass2 = std::make_shared<MarkdownTestCase>(render);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        std::vector<std::unordered_map<std::string, std::string>> segments2 = testClass2->GetSegmentInfo();
        ASSERT_EQ(segments.size(), segments2.size());

        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments = testClass->GetLinkSegmentInfo();
        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments2 = testClass2->GetLinkSegmentInfo();
        ASSERT_EQ(linkSegments.size(), linkSegments2.size());

        const std::string types[] = { "Text", "Style", "OpeningStyle", "ClosingStyle", "SpecialAttribute", "LinkTarget" };
        for (size_t i = 0; i < segments.size(); ++i)
        {
            for (const std::string& type : types)
            {
                std::string leftText = segments.at(i).at(type);
                std::string rightText = segments2.at(i).at(type);
                ASSERT_EQ(leftText, rightText) << "Original parse does not match new parse. Type: " << type << " index: " << i;
            }
        }

        for (size_t i = 0; i < linkSegments.size(); ++i)
        {
            ASSERT_EQ(linkSegments.at(i).size(), linkSegments2.at(i).size())
                << "Number of segments within a link or images does not match. Index: " << i;

            for (size_t j = 0; j < linkSegments.at(i).size(); ++j)
            {
                for (const std::string& type : types)
                {
                    std::string leftText = linkSegments.at(i).at(j).at(type);
                    std::string rightText = linkSegments2.at(i).at(j).at(type);
                    ASSERT_EQ(leftText, rightText) << "Within a Link or Image. Original parse does not match new parse. "
                                                      "Type: " << type << " index: i " << i << " j " << j;
                }
            }
        }
    }

    TEST_F(MarkdownParagraphTests, Render_GivesTheSameParsedTextInAsOut_WhenGivenAnImage)
    {
        // Arrange
        // Expected 3 segments given current tests
        std::string given = "Plain text ![bold text](hyper link) now closed";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        std::string render = testClass->Render();
        auto testClass2 = std::make_shared<MarkdownTestCase>(render);

        // Assert
        std::vector<std::unordered_map<std::string, std::string>> segments = testClass->GetSegmentInfo();
        std::vector<std::unordered_map<std::string, std::string>> segments2 = testClass2->GetSegmentInfo();
        ASSERT_EQ(segments.size(), segments2.size());

        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments = testClass->GetLinkSegmentInfo();
        std::vector<std::vector<std::unordered_map<std::string, std::string>>> linkSegments2 = testClass2->GetLinkSegmentInfo();
        ASSERT_EQ(linkSegments.size(), linkSegments2.size());

        const std::string types[] = { "Text", "Style", "OpeningStyle", "ClosingStyle", "SpecialAttribute", "LinkTarget" };
        for (size_t i = 0; i < segments.size(); ++i)
        {
            for (const std::string& type : types)
            {
                std::string leftText = segments.at(i).at(type);
                std::string rightText = segments2.at(i).at(type);
                ASSERT_EQ(leftText, rightText) << "Original parse does not match new parse. Type: " << type << " index: " << i;
            }
        }

        for (size_t i = 0; i < linkSegments.size(); ++i)
        {
            ASSERT_EQ(linkSegments.at(i).size(), linkSegments2.at(i).size())
                << "Number of segments within a link or images does not match. Index: " << i;

            for (size_t j = 0; j < linkSegments.at(i).size(); ++j)
            {
                for (const std::string& type : types)
                {
                    std::string leftText = linkSegments.at(i).at(j).at(type);
                    std::string rightText = linkSegments2.at(i).at(j).at(type);
                    ASSERT_EQ(leftText, rightText) << "Within a Link or Image. Original parse does not match new parse. "
                        "Type: " << type << " index: i " << i << " j " << j;
                }
            }
        }
    }

#pragma endregion

#pragma region IsInputValidForElement

    TEST_F(MarkdownParagraphTests, IsInputValidForElement_ReturnsTrue_WhenStringBeginsWithAlphaCharacter)
    {
        // Arrange
        std::string given = "Some text";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        bool isValid = testClass->IsInputValidForElement(given);

        // Assert
        ASSERT_TRUE(isValid);
    }

    TEST_F(MarkdownParagraphTests, GetType_ReturnsParagraph_WhenStringBeginsWithAlphaCharacter)
    {
        // Arrange
        std::string given = "Some text";
        auto expected = DocumentElementType::Paragraph;
        auto markdownExpected = MarkdownElementType::Paragraph;
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        DocumentElementType actual = testClass->GetType();
        MarkdownElementType actual2 = testClass->GetMarkdownType();

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(markdownExpected, actual2);
    }

    TEST_F(MarkdownParagraphTests, IsInputValidForElement_ReturnsTrue_WhenStringBeginsWithAlphaCharacterAfterSomeSpaces)
    {
        // Arrange
        std::string given = "    Some text";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        bool isValid = testClass->IsInputValidForElement(given);

        // Assert
        ASSERT_TRUE(isValid);
    }

    TEST_F(MarkdownParagraphTests, GetType_ReturnsParagraph_WhenStringBeginsWithAlphaCharacterAfterSomeSpaces)
    {
        // Arrange
        std::string given = "    Some text";
        auto expected = DocumentElementType::Paragraph;
        auto markdownExpected = MarkdownElementType::Paragraph;
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        DocumentElementType actual = testClass->GetType();
        MarkdownElementType actual2 = testClass->GetMarkdownType();

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(markdownExpected, actual2);
    }

    TEST_F(MarkdownParagraphTests, IsInputValidForElement_ReturnsFalse_WhenStringBeginsWithAHeading)
    {
        // Arrange
        std::string given = "# Some text";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        bool isValid = testClass->IsInputValidForElement(given);

        // Assert
        ASSERT_FALSE(isValid);
    }

    TEST_F(MarkdownParagraphTests, GetType_ReturnsUnknown_WhenStringBeginsWithAHeading)
    {
        // Arrange
        std::string given = "# Some text";
        auto expected = DocumentElementType::Unknown;
        auto markdownExpected = MarkdownElementType::Unknown;
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        DocumentElementType actual = testClass->GetType();
        MarkdownElementType actual2 = testClass->GetMarkdownType();

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(markdownExpected, actual2);
    }

    TEST_F(MarkdownParagraphTests, IsInputValidForElement_ReturnsFalse_WhenASpaceIsTheFirstCharacterButHeadingIsAfter)
    {
        // Arrange
        std::string given = "   # Some text";
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        bool isValid = testClass->IsInputValidForElement(given);

        // Assert
        ASSERT_FALSE(isValid);
    }

    TEST_F(MarkdownParagraphTests, GetType_ReturnsUnknown_WhenASpaceIsTheFirstCharacterButHeadingIsAfter)
    {
        // Arrange
        std::string given = "    # Some text";
        auto expected = DocumentElementType::Unknown;
        auto markdownExpected = MarkdownElementType::Unknown;
        auto testClass = std::make_shared<MarkdownTestCase>(given);

        // Act
        DocumentElementType actual = testClass->GetType();
        MarkdownElementType actual2 = testClass->GetMarkdownType();

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(markdownExpected, actual2);
    }

#pragma endregion
}