#include <memory>
#include <gtest/gtest.h>

#include "Console/ConsoleLog.h"
#include "Element/MarkdownElement/MarkdownHeading.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_Element_MarkdownElement
{
    class MarkdownHeadingTests : public ::testing::Test
    {
    public:

        MarkdownHeadingTests()
        {
        }

    protected:

        std::shared_ptr<ConsoleLog> m_logger;

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

#pragma region Failure

    TEST_F(MarkdownHeadingTests, OnConstruction_IsCreatedInErrorState_WhenNotGivenAMarkdownHeading)
    {
        // Arrange
        std::string given = "Heading";
        std::string render = "Error: Not a heading.";
        std::string text = "Error: Not a heading.";
        auto expectedDocumentElementType = DocumentElementType::Unknown;
        auto expectedMarkdownElementType = MarkdownElementType::Unknown;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_IsCreatedInErrorState_WhenThereIsNoSpaceAfterHash)
    {
        // Arrange
        std::string given = "#Heading";
        std::string render = "Error: Not a heading.";
        std::string text = "Error: Not a heading.";
        auto expectedDocumentElementType = DocumentElementType::Unknown;
        auto expectedMarkdownElementType = MarkdownElementType::Unknown;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_IsCreatedInErrorState_WhenThereIsNoTextAfterTheHash)
    {
        // Arrange
        std::string given = "#";
        std::string render = "Error: Not a heading.";
        std::string text = "Error: Not a heading.";
        auto expectedDocumentElementType = DocumentElementType::Unknown;
        auto expectedMarkdownElementType = MarkdownElementType::Unknown;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_IsCreatedInErrorState_WhenThereIsNoTextGiven)
    {
        // Arrange
        std::string given = {};
        std::string render = "Error: Not a heading.";
        std::string text = "Error: Not a heading.";
        auto expectedDocumentElementType = DocumentElementType::Unknown;
        auto expectedMarkdownElementType = MarkdownElementType::Unknown;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading1

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading1)
    {
        // Arrange
        std::string given = "# Heading";
        std::string render = "# Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading1;
        auto expectedMarkdownElementType = MarkdownElementType::Heading1;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. " 
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading1WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  # Heading  ";
        std::string render = "# Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading1;
        auto expectedMarkdownElementType = MarkdownElementType::Heading1;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading2

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading2)
    {
        // Arrange
        std::string given = "## Heading";
        std::string render = "## Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading2;
        auto expectedMarkdownElementType = MarkdownElementType::Heading2;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading2WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  ## Heading  ";
        std::string render = "## Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading2;
        auto expectedMarkdownElementType = MarkdownElementType::Heading2;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading3

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading3)
    {
        // Arrange
        std::string given = "### Heading";
        std::string render = "### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading3;
        auto expectedMarkdownElementType = MarkdownElementType::Heading3;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading3WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  ### Heading  ";
        std::string render = "### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading3;
        auto expectedMarkdownElementType = MarkdownElementType::Heading3;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading4

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading4)
    {
        // Arrange
        std::string given = "#### Heading";
        std::string render = "#### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading4;
        auto expectedMarkdownElementType = MarkdownElementType::Heading4;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading4WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  #### Heading  ";
        std::string render = "#### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading4;
        auto expectedMarkdownElementType = MarkdownElementType::Heading4;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading5

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading5)
    {
        // Arrange
        std::string given = "##### Heading";
        std::string render = "##### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading5;
        auto expectedMarkdownElementType = MarkdownElementType::Heading5;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading5WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  ##### Heading  ";
        std::string render = "##### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading5;
        auto expectedMarkdownElementType = MarkdownElementType::Heading5;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Heading6

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading6)
    {
        // Arrange
        std::string given = "###### Heading";
        std::string render = "###### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading6;
        auto expectedMarkdownElementType = MarkdownElementType::Heading6;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_HeadingFromMarkdownIsCreated_WhenGivenHeading6WithSpacesEitherSide)
    {
        // Arrange
        std::string given = "  ###### Heading  ";
        std::string render = "###### Heading";
        std::string text = "Heading";
        auto expectedDocumentElementType = DocumentElementType::Heading6;
        auto expectedMarkdownElementType = MarkdownElementType::Heading6;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion

#pragma region Edge Cases

    TEST_F(MarkdownHeadingTests, OnConstruction_Heading1IsStillParsed_WhenFirstCharacterAfterTheSpaceIsAHashSymbol)
    {
        // Arrange
        std::string given = "# #Valid";
        std::string render = "# #Valid";
        std::string text = "#Valid";
        auto expectedDocumentElementType = DocumentElementType::Heading1;
        auto expectedMarkdownElementType = MarkdownElementType::Heading1;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

    TEST_F(MarkdownHeadingTests, OnConstruction_WillRemoveSpacesBetweenHashAndHeadingInRender_WhenProvidedSpaces)
    {
        // Arrange
        std::string given = "#       #Valid";
        std::string render = "# #Valid";
        std::string text = "#Valid";
        auto expectedDocumentElementType = DocumentElementType::Heading1;
        auto expectedMarkdownElementType = MarkdownElementType::Heading1;

        // Act
        auto testClass = std::make_shared<MarkdownHeading>(given);

        // Assert
        ASSERT_EQ(expectedDocumentElementType, testClass->GetType())
            << "DocumentElementType did not match. "
            << "Expected: " << EDocumentElementType::ToString(expectedDocumentElementType)
            << " Actual: " << EDocumentElementType::ToString(testClass->GetType());
        ASSERT_EQ(expectedMarkdownElementType, testClass->GetMarkdownType())
            << "MarkdownElementType did not match. "
            << "Expected: " << EMarkdownElementType::ToString(expectedMarkdownElementType)
            << " Actual: " << EMarkdownElementType::ToString(testClass->GetMarkdownType());
        ASSERT_EQ(text, testClass->GetText()) << "GetText did not match.";
        ASSERT_EQ(render, testClass->Render()) << "Render did not match.";
    }

#pragma endregion
}