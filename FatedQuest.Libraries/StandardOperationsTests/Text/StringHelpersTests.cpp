#include "../../StandardOperations/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

#include "Console/ConsoleLog.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardOperations_Text
{
    class StringHelpersTests : public ::testing::Test
    {
    public:

        std::shared_ptr<ConsoleLog> m_logger;
        StringHelpersTests()
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Subscribe(m_logger);
            }
        }

    protected:

        void SetUp() override
        {

        }

        void TearDown() override
        {

        }

    };

#pragma region Contains
    TEST_F(StringHelpersTests, Contains_ReturnsTrue_WhenLeftIsInRight)
    {
        // Arrange
        std::string needle = "cat";
        std::string haystack = "dog cat mouse";

        // Act
        bool actual = StringHelpers::Contains(needle, haystack);

        // Assert
        ASSERT_TRUE(actual) << "Needle: " << needle << " Haystack: " << haystack;
    }

    TEST_F(StringHelpersTests, Contains_ReturnsFalse_WhenLeftIsLargerThanRight)
    {
        // Arrange
        std::string needle = "mouse";
        std::string haystack = "cat";

        // Act
        bool actual = StringHelpers::Contains(needle, haystack);

        // Assert
        ASSERT_FALSE(actual) << "Needle: " << needle << " Haystack: " << haystack;
    }

    TEST_F(StringHelpersTests, Contains_ReturnsFalse_WhenLeftIsEmpty)
    {
        // Arrange
        std::string needle = {};
        std::string haystack = "dog cat mouse";

        // Act
        bool actual = StringHelpers::Contains(needle, haystack);

        // Assert
        ASSERT_FALSE(actual) << "Needle: " << needle << " Haystack: " << haystack;
    }

    TEST_F(StringHelpersTests, Contains_ReturnsFalse_WhenRightIsIsEmpty)
    {
        // Arrange
        std::string needle = "cat";
        std::string haystack = {};

        // Act
        bool actual = StringHelpers::Contains(needle, haystack);

        // Assert
        ASSERT_FALSE(actual) << "Needle: " << needle << " Haystack: " << haystack;
    }

    TEST_F(StringHelpersTests, Contains_ReturnsTrue_WhenLeftAndRightAreBothEmpty)
    {
        // Arrange
        std::string needle = {};
        std::string haystack = {};

        // Act
        bool actual = StringHelpers::Contains(needle, haystack);

        // Assert
        ASSERT_TRUE(actual) << "Needle: " << needle << " Haystack: " << haystack;
    }
#pragma endregion

#pragma region Contains
    TEST_F(StringHelpersTests, DisplayName_ReturnsGiven_WhenGivenIsFine)
    {
        // Arrange
        std::string given = "I am a display name";
        std::string expected = "I am a display name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_AddsSpaces_WhenCapitalsButNoSpacesAreFound)
    {
        // Arrange
        std::string given = "IAmADisplayName";
        std::string expected = "I Am A Display Name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_AddsSpaces_WhenDashesButNoSpacesAreFound)
    {
        // Arrange
        std::string given = "I-am-a-display-name";
        std::string expected = "I am a display name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_AddsSpaces_WhenUnderscoresButNoSpacesAreFound)
    {
        // Arrange
        std::string given = "I_am_a_display_name";
        std::string expected = "I am a display name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_Capitalises_WhenAFullStopIsFound)
    {
        // Arrange
        std::string given = "I am. a display name";
        std::string expected = "I am. A display name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_DoesNotAddMultipleSpaces_WhenASpaceIsAlreadyFound)
    {
        // Arrange
        std::string given = "I Am A Display Name";
        std::string expected = "I Am A Display Name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, DisplayName_DoesNotAddMultipleFullstops_WhenAFullstopIsAlreadyFound)
    {
        // Arrange
        std::string given = "I Am... a Display Name";
        std::string expected = "I Am. A Display Name";

        // Act
        std::string actual = StringHelpers::DisplayName(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion
}