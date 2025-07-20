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
}