#include "../../StandardOperations/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

#include "Console/ConsoleLog.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardOperations_Number
{
    class FloatingPointHelpersTests : public ::testing::Test
    {
    public:

        std::shared_ptr<ConsoleLog> m_logger;
        FloatingPointHelpersTests()
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

#pragma region TryParse-Float

    TEST_F(FloatingPointHelpersTests, TryParseFloat_ReturnsFalse_WhenGivenIsNotANumber)
    {
        // Arrange
        std::string given = "NotANumber";

        // Act
        float actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_FALSE(result);
    }

    TEST_F(FloatingPointHelpersTests, TryParseFloat_Parses_WhenGivenIsANumber)
    {
        // Arrange
        std::string given = "42";
        float expected = 42;

        // Act
        float actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_TRUE(result);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FloatingPointHelpersTests, TryParseFloat_Parses_WhenGivenIsAFloat)
    {
        // Arrange
        std::string given = "42.54";
        float expected = 42.54f;

        // Act
        float actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_TRUE(result);
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region TryParse-Double

    TEST_F(FloatingPointHelpersTests, TryParseDouble_ReturnsFalse_WhenGivenIsNotANumber)
    {
        // Arrange
        std::string given = "NotANumber";

        // Act
        double actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_FALSE(result);
    }

    TEST_F(FloatingPointHelpersTests, TryParseDouble_Parses_WhenGivenIsANumber)
    {
        // Arrange
        std::string given = "42";
        double expected = 42;

        // Act
        double actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_TRUE(result);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FloatingPointHelpersTests, TryParseDouble_Parses_WhenGivenIsAFloat)
    {
        // Arrange
        std::string given = "42.54";
        double expected = 42.54;

        // Act
        double actual;
        bool result = FloatingPointHelpers::TryParse(given, actual);

        // Assert
        ASSERT_TRUE(result);
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region RemoveUnneededZeros-Float

    TEST_F(FloatingPointHelpersTests, RemoveUnneededZerosFloat_ReturnsTheSameNumber_WhenNumberDoesNotContainADecimal)
    {
        // Arrange
        float given = 5;
        std::string expected = "5";

        // Act
        std::string actual = FloatingPointHelpers::RemoveUnneededZeros(given);

        // Assert
        ASSERT_EQ(expected, actual) << "Expected: " << given << " Actual: " << expected;
    }

    TEST_F(FloatingPointHelpersTests, RemoveUnneededZeros_ReturnsTheSameNumber_WhenNumberDoesNotEndInAZero)
    {
        // Arrange
        float given = 42.5f;
        std::string expected = "42.5";

        // Act
        std::string actual = FloatingPointHelpers::RemoveUnneededZeros(given);

        // Assert
        ASSERT_EQ(expected, actual) << "Expected: " << given << " Actual: " << expected;
    }

#pragma endregion

#pragma region RemoveUnneededZeros-Double

    TEST_F(FloatingPointHelpersTests, RemoveUnneededZerosDouble_ReturnsTheSameNumber_WhenNumberDoesNotContainADecimal)
    {
        // Arrange
        double given = 99;
        std::string expected = "99";

        // Act
        std::string actual = FloatingPointHelpers::RemoveUnneededZeros(given);

        // Assert
        ASSERT_EQ(expected, actual) << "Expected: " << given << " Actual: " << expected;
    }

    TEST_F(FloatingPointHelpersTests, RemoveUnneededDouble_ReturnsTheSameNumber_WhenNumberDoesNotEndInAZero)
    {
        // Arrange
        float given = 76.93f;
        std::string expected = "76.93";

        // Act
        std::string actual = FloatingPointHelpers::RemoveUnneededZeros(given);

        // Assert
        ASSERT_EQ(expected, actual) << "Expected: " << given << " Actual: " << expected;
    }

#pragma endregion
}