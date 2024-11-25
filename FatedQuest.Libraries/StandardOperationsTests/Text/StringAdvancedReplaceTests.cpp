#include "../../StandardOperations/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardOperations_Text
{
    class StringAdvancedReplaceTests : public ::testing::Test
    {
    public:

        StringAdvancedReplaceTests()
        {
        }

    protected:

        void SetUp() override
        {

        }

        void TearDown() override
        {

        }

    };

#pragma region Replace
    TEST_F(StringAdvancedReplaceTests, Replace_ReturnsSource_WhenSourceIsShorterThanCriteria)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "target";
        std::string givenReplacement = "b";

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenSource, actual) << "givenSource(" << givenSource << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, Replace_ReturnsSource_WhenCriteriaIsNotFound)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "b";
        std::string givenReplacement = "c";

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenSource, actual) << "givenSource(" << givenSource << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, Replace_ReturnsReplacement_WhenCriteriaIsFound)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenReplacement, actual) << "replacement(" << givenReplacement << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, Replace_ReturnsReplacesAllInstances_WhenCriteriaIsFoundMultipleTimes)
    {
        // Arrange
        std::string givenSource = "aaa";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        std::string expected = givenReplacement + givenReplacement + givenReplacement;

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, Replace_OnlyReplacesCriteria_WhenNotJustCriteriaIsFound)
    {
        // Arrange
        std::string givenSource = "aca";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        std::string expected = givenReplacement + "c" + givenReplacement;

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, Replace_ReplacesCriteria_WhenReplacementIsLargerThanCriteria)
    {
        // Arrange
        std::string givenSource = "a1a";
        std::string givenCriteria = "1";
        std::string givenReplacement = "four";

        std::string expected = "a" + givenReplacement + "a";

        // Act
        std::string actual = StringAdvancedReplace::Replace(givenSource, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

#pragma endregion

#pragma region ReplaceInPlace
    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_ReturnsSource_WhenSourceIsShorterThanCriteria)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "target";
        std::string givenReplacement = "b";

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenSource, actual) << "givenSource(" << givenSource << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_ReturnsSource_WhenCriteriaIsNotFound)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "b";
        std::string givenReplacement = "c";

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenSource, actual) << "givenSource(" << givenSource << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_ReturnsReplacement_WhenCriteriaIsFound)
    {
        // Arrange
        std::string givenSource = "a";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(givenReplacement, actual) << "replacement(" << givenReplacement << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_ReturnsReplacesAllInstances_WhenCriteriaIsFoundMultipleTimes)
    {
        // Arrange
        std::string givenSource = "aaa";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        std::string expected = givenReplacement + givenReplacement + givenReplacement;

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_OnlyReplacesCriteria_WhenNotJustCriteriaIsFound)
    {
        // Arrange
        std::string givenSource = "aca";
        std::string givenCriteria = "a";
        std::string givenReplacement = "b";

        std::string expected = givenReplacement + "c" + givenReplacement;

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

    TEST_F(StringAdvancedReplaceTests, ReplaceInPlace_ReplacesCriteria_WhenReplacementIsLargerThanCriteria)
    {
        // Arrange
        std::string givenSource = "a1a";
        std::string givenCriteria = "1";
        std::string givenReplacement = "four";

        std::string expected = "a" + givenReplacement + "a";

        // Act
        std::string actual = givenSource;
        StringAdvancedReplace::ReplaceInPlace(actual, givenCriteria, givenReplacement);

        // Assert
        ASSERT_EQ(expected, actual) << "expected(" << expected << ") != actual(" << actual << ")";
    }

#pragma endregion
}