#include "../LibraryIncludes.h"
#include <vector>

using namespace StandardCLibrary;

namespace StandardCLibraryTests_StringHelpers
{
    class StringHelpersTests : public ::testing::Test
    {
    public:
        StringHelpersTests()
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

#pragma region Join
    TEST_F(StringHelpersTests, Join_ReturnsGiven_WhenStringGiven)
    {
        std::string given = "Something";
        std::vector<std::string> list = std::vector<std::string>();
        list.push_back(given);
        std::string expected = "Something";

        std::string actual = StringHelpers::Join("", list);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Join_ReturnsGluedStrings_WhenMultipleStringsGiven)
    {
        // Arrange
        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("Something");
        given.push_back("Else");

        std::string expected = "SomethingElse";

        // Act
        std::string actual = StringHelpers::Join("", given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Join_ReturnsGluedStringsWithSeparatorBetween_WhenMultipleStringsGiven)
    {
        // Arrange
        std::vector<std::string> given = std::vector<std::string>();
        given.push_back("Something");
        given.push_back("Else");
        std::string separator = "::";

        std::string expected = "Something::Else";

        // Act
        std::string actual = StringHelpers::Join(separator, given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region Trim
    TEST_F(StringHelpersTests, Trim_RemovesSpacesFromLeft_WhenSpacesAreFoundOnLeftTest)
    {
        std::string given = "   Something";
        std::string expected = "Something";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_RemovesSpacesFromRight_WhenSpacesAreFoundOnLeftTest)
    {
        std::string given = "Something   ";
        std::string expected = "Something";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_RemovesSpacesFromLeftAndRight_WhenFoundOnBothSides)
    {
        std::string given = "    Something   ";
        std::string expected = "Something";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_DoesNotRemoveSpacesFromTheMiddle_WhenSpacesFoundOnBothSides)
    {
        std::string given = "    Something else   ";
        std::string expected = "Something else";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_DoesNotRemoveSpacesFromTheMiddle_WhenSpacesFoundOnLeft)
    {
        std::string given = "    Something else";
        std::string expected = "Something else";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_DoesNotRemoveSpacesFromTheMiddle_WhenSpacesFoundOnRight)
    {
        std::string given = "Something else    ";
        std::string expected = "Something else";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, Trim_DoesNotRemoveSpacesFromTheMiddle_WhenNoSpacesFoundOnSides)
    {
        std::string given = "    Something else    ";
        std::string expected = "Something else";

        std::string actual = StringHelpers::Trim(given);

        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region ConvertToLower
    TEST_F(StringHelpersTests, ConvertToLower_ConvertsGivenToLower_WhenGivenHasCapitals)
    {
        std::string given = "HasCapitalLetters";
        std::string expected = "hascapitalletters";

        StringHelpers::ConvertToLower(given);

        ASSERT_EQ(expected, given);
    }

    TEST_F(StringHelpersTests, ConvertToLower_ReturnsEmpty_WhenGivenEmpty)
    {
        std::string given = "";
        std::string expected = "";

        StringHelpers::ConvertToLower(given);

        ASSERT_EQ(expected, given);
    }

    TEST_F(StringHelpersTests, ConvertToLower_RetainsNumbers_WhenNumbersAreInString)
    {
        std::string given = "Has2Capital1Letters";
        std::string expected = "has2capital1letters";

        StringHelpers::ConvertToLower(given);

        ASSERT_EQ(expected, given);
    }
#pragma endregion

#pragma region ToLower
    TEST_F(StringHelpersTests, ToLower_ConvertsGivenToLower_WhenGivenHasCapitals)
    {
        std::string given = "HasCapitalLetters";
        std::string expected = "hascapitalletters";

        std::string actual = StringHelpers::ToLower(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, ToLower_ReturnsEmpty_WhenGivenEmpty)
    {
        std::string given = "";
        std::string expected = "";

        std::string actual = StringHelpers::ToLower(given);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region ConvertToUpper
    TEST_F(StringHelpersTests, ConvertToUpper_ConvertsGivenToUpper_WhenGivenHasLowercaseLetters)
    {
        std::string given = "HasCapitalLetters";
        std::string expected = "HASCAPITALLETTERS";

        StringHelpers::ConvertToUpper(given);

        ASSERT_EQ(expected, given);
    }

    TEST_F(StringHelpersTests, ConvertToUpper_ReturnsEmpty_WhenGivenEmpty)
    {
        std::string given = "";
        std::string expected = "";

        StringHelpers::ConvertToUpper(given);

        ASSERT_EQ(expected, given);
    }

    TEST_F(StringHelpersTests, ConvertToUpper_RetainsNumbers_WhenNumbersAreInString)
    {
        std::string given = "Has2Capital1Letters";
        std::string expected = "HAS2CAPITAL1LETTERS";

        StringHelpers::ConvertToUpper(given);

        ASSERT_EQ(expected, given);
    }
#pragma endregion

#pragma region ToUpper
    TEST_F(StringHelpersTests, ToUpper_ConvertsGivenToUpper_WhenGivenHasCapitals)
    {
        std::string given = "HasCapitalLetters";
        std::string expected = "HASCAPITALLETTERS";

        std::string actual = StringHelpers::ToUpper(given);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(StringHelpersTests, ToUpper_ReturnsEmpty_WhenGivenEmpty)
    {
        std::string given = "";
        std::string expected = "";

        std::string actual = StringHelpers::ToUpper(given);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
}