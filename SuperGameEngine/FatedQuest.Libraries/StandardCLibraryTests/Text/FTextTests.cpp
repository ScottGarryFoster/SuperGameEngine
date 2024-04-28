#include <cstring>

#include "../LibraryIncludes.h"
#include "../../StandardCLibrary/Text/FText.h"

using namespace StandardCLibrary;
namespace StandardCLibraryTests_Text_TextTests
{
    std::string CutStringToSize(std::string toCut, size_t size);

    TEST(FTextTest, OnConstruction_ReturnsEmptyString_WhenGivenNoInput)
    {
        std::string expected = "";

        FText actual = FText();

        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OnConstruction_ReturnsAMatching_WhenGivenAnInput)
    {
        std::string expected = "something";

        FText actual = FText(expected);

        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OnConstruction_ReturnsAFlattenedString_WhenGivenAVectorInput)
    {
        // Arrange
        std::string startingWith = "something";
        std::string thenGiven = "Else";
        std::string finallyGiven = "Something again";
        std::string expected = startingWith + thenGiven + finallyGiven;

        std::vector<std::string> given;
        given.push_back(startingWith);
        given.push_back(thenGiven);
        given.push_back(finallyGiven);

        // Act
        FText actual = FText(given);

        // Assert
        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OnConstructionWide_ReturnsEmptyString_WhenGivenNoInput)
    {
        std::wstring expected = L"";

        FText actual = FText();

        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdWstring();
    }

    TEST(FTextTest, OnConstructionWide_ReturnsAMatching_WhenGivenAnInput)
    {
        std::wstring expected = L"something";

        FText actual = FText(expected);

        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdWstring();
    }

    TEST(FTextTest, OnConstructionWide_ReturnsAFlattenedString_WhenGivenAVectorInput)
    {
        // Arrange
        std::wstring startingWith = L"something";
        std::wstring thenGiven = L"Else";
        std::wstring finallyGiven = L"Something again";
        std::wstring expected = startingWith + thenGiven + finallyGiven;

        std::vector<std::wstring> given;
        given.push_back(startingWith);
        given.push_back(thenGiven);
        given.push_back(finallyGiven);

        // Act
        FText actual = FText(given);

        // Assert
        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdWstring();
    }

#pragma region WideString
    TEST(FTextTest, OnConstruction_GivenWideStringIsReturned_WhenUsingACharacterOutsideASCII)
    {
        std::wstring expected = L"世界";

        FText actual = FText(expected);

        ASSERT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdWstring();
    }
#pragma endregion

#pragma region Operator Plus
    TEST(FTextTest, OperatorPlus_JoinsTogetherTwoFTexts_WhenRightHandIsAnFText)
    {
        FText left = FText("foo");
        FText right = "bar";
        FText expected = FText("foobar");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFTextAndString_WhenRightHandIsAString)
    {
        FText left = FText("foo");
        std::string right = "bar";
        FText expected = FText("foobar");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFTextAndWstring_WhenRightHandIsAString)
    {
        FText left = FText("foo");
        std::wstring right = L"bar";
        FText expected = FText("foobar");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdWstring();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherInt_WhenRightHandIsAnInt)
    {
        FText left = FText("foo");
        int right = 42;
        FText expected = FText("foo42");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFloat_WhenRightHandIsAnFloat)
    {
        FText left = FText("foo");
        float right = 42.421f;
        FText expected = FText("foo42.42");

        FText actual = left + right;

        std::string cutActual = CutStringToSize(actual.AsStdString(), expected.AsStdString().size());
        ASSERT_TRUE(expected == cutActual) << "Expected: " << expected.AsStdString() << " Actual: " << cutActual;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherDouble_WhenRightHandIsAnDouble)
    {
        FText left = FText("foo");
        double right = 42.421;
        FText expected = FText("foo42.42");

        FText actual = left + right;

        std::string cutActual = CutStringToSize(actual.AsStdString(), expected.AsStdString().size());
        ASSERT_TRUE(expected == cutActual) << "Expected: " << expected << " Actual: " << cutActual;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherLongInt_WhenRightHandIsAnLongInt)
    {
        FText left = FText("foo");
        long int right = 42;
        FText expected = FText("foo42");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherUnsignedLongInt_WhenRightHandIsAnUnsignedLongInt)
    {
        FText left = FText("foo");
        unsigned long int right = 42;
        FText expected = FText("foo42");

        FText actual = left + right;

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }
#pragma endregion

#pragma region Operator Plus Equals
    TEST(FTextTest, OperatorPlus_JoinsTogetherTwoFTexts_WhenRightHandIsAnFTextWithPlusEquals)
    {
        FText left = FText("foo");
        FText right = "bar";
        FText expected = FText("foobar");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected.AsStdString() << " Actual: " << left.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFTextAndString_WhenRightHandIsAStringWithPlusEquals)
    {
        FText left = FText("foo");
        std::string right = "bar";
        FText expected = FText("foobar");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected.AsStdString() << " Actual: " << left.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFTextAndWstring_WhenRightHandIsAStringWithPlusEquals)
    {
        FText left = FText("foo");
        std::wstring right = L"bar";
        FText expected = FText("foobar");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected.AsStdString() << " Actual: " << left.AsStdWstring();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherInt_WhenRightHandIsAnIntWithPlusEquals)
    {
        FText left = FText("foo");
        int right = 42;
        FText expected = FText("foo42");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected.AsStdString() << " Actual: " << left.AsStdString();
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherFloat_WhenRightHandIsAnFloatWithPlusEquals)
    {
        FText left = FText("foo");
        float right = 42.421f;
        FText expected = FText("foo42.42");

        left += right;

        std::string cutActual = CutStringToSize(left.AsStdString(), expected.AsStdString().size());
        ASSERT_TRUE(expected == cutActual) << "Expected: " << expected.AsStdString() << " Actual: " << cutActual;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherDouble_WhenRightHandIsAnDoubleWithPlusEquals)
    {
        FText left = FText("foo");
        double right = 42.421;
        FText expected = FText("foo42.42");

        left += right;

        std::string cutActual = CutStringToSize(left.AsStdString(), expected.AsStdString().size());
        ASSERT_TRUE(expected == cutActual) << "Expected: " << expected << " Actual: " << cutActual;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherLongInt_WhenRightHandIsAnLongIntWithPlusEquals)
    {
        FText left = FText("foo");
        long int right = 42;
        FText expected = FText("foo42");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected << " Actual: " << left;
    }

    TEST(FTextTest, OperatorPlus_JoinsTogetherUnsignedLongInt_WhenRightHandIsAnUnsignedLongIntWithPlusEquals)
    {
        FText left = FText("foo");
        unsigned long int right = 42;
        FText expected = FText("foo42");

        left += right;

        ASSERT_TRUE(expected == left) << "Expected: " << expected << " Actual: " << left;
    }
#pragma endregion

#pragma region Operator Condition Equals
    TEST(FTextTest, OperatorEquals_ReturnsGiven_WhenGivenStringValueViaEqualsOperator)
    {
        FText given = FText("foo");
        std::string expected = "bar";

        given = expected;

        ASSERT_TRUE(given == expected) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, OperatorEquals_ReturnsGiven_WhenGivenWstringValueViaEqualsOperator)
    {
        FText given = FText("foo");
        std::wstring expected = L"bar";

        given = expected;

        ASSERT_TRUE(given == expected) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, OperatorEquals_ReturnsGiven_WhenGivenFTextValueViaEqualsOperator)
    {
        FText given = FText("foo");
        FText expected = "bar";

        given = expected;

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region Operator Condition Equals
    TEST(FTextTest, OperatorEquals_ReturnsFalse_WhenTwoFTextDoNotEqual)
    {
        FText left = FText("foo");
        FText right = FText("bar");

        ASSERT_FALSE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FTextTest, OperatorEquals_ReturnsTrue_WhenTwoFTextEqual)
    {
        FText left = FText("foo");
        FText right = FText("foo");

        ASSERT_TRUE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FTextTest, OperatorEquals_ReturnsFalse_WhenStringComparedAndAreNotEqual)
    {
        FText left = FText("foo");
        std::string right = "bar";

        ASSERT_FALSE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FTextTest, OperatorEquals_ReturnsTrue_WhenStringComparedAndEqual)
    {
        FText left = FText("foo");
        std::string right = "foo";

        ASSERT_TRUE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FTextTest, OperatorEquals_ReturnsFalse_WhenWstringComparedAndAreNotEqual)
    {
        FText left = FText("foo");
        std::wstring right = L"bar";

        ASSERT_FALSE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FTextTest, OperatorEquals_ReturnsTrue_WhenWstringComparedAndEqual)
    {
        FText left = FText("foo");
        std::wstring right = L"foo";

        ASSERT_TRUE(left == right) << "Condition: " << left << " == " << right;
    }
#pragma endregion

#pragma region Convertion
    TEST(FTextTest, AsStdString_ReturnsAnEqualString)
    {
        FText given = FText("foo");
        std::string expected = "foo";

        std::string actual = given.AsStdString();

        ASSERT_EQ(expected, actual);
    }

    TEST(FTextTest, AsCharArr_ReturnsAnEqualCharArr)
    {
        FText given = FText("foo");
        std::wstring expectedString = L"foo";
        const wchar_t* expected = expectedString.c_str();

        const wchar_t* actual = given.AsCharArr();

        ASSERT_EQ(sizeof(expected), sizeof(actual));
        for (unsigned int c = 0; c < sizeof(expected); ++c)
        {
            ASSERT_EQ(expected[c], actual[c])
                << "Character: " << c << " was not equal. Expected: " << expected[c] << " Actual: " << actual[c];
        }
    }
#pragma endregion

#pragma region ToLower
    TEST(FTextTest, ToLower_ReturnsAllLowerCase_WhenGivenAnUpperCaseString)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("uppercase string");

        FText actual = given.ToLower();

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FTextTest, ToLower_DoesNotAffectOriginalString_WhenPerformed)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("UpperCase String");

        given.ToLower();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, ToLower_ReturnsAllLowerCase_WhenGivenAnUpperCaseWstring)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"uppercase string";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        FText actual = given.ToLower();

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FTextTest, ToLower_DoesNotAffectOriginalWstring_WhenPerformed)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"UpperCase String";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        given.ToLower();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region ToUpper
    TEST(FTextTest, ToUpper_ReturnsAllUpperCase_WhenGivenAnUpperCaseString)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("UPPERCASE STRING");

        FText actual = given.ToUpper();

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FTextTest, ToUpper_DoesNotAffectOriginalString_WhenPerformed)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("UpperCase String");

        given.ToUpper();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, ToUpper_ReturnsAllUpperCase_WhenGivenAnUpperCaseWstring)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"UPPERCASE STRING";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        FText actual = given.ToUpper();

        ASSERT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FTextTest, ToUpper_DoesNotAffectOriginalWstring_WhenPerformed)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"UpperCase String";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        given.ToUpper();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region ConvertToLowerAndUpper
    TEST(FTextTest, ConvertToLower_ChangesValueToLowerCase)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("uppercase string");

        given.ConvertToLower();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, ConvertToUpper_ChangesValueToUpperCase)
    {
        FText given = FText("UpperCase String");
        FText expected = FText("UPPERCASE STRING");

        given.ConvertToUpper();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, ConvertToLower_ChangesValueToLowerCase_WhenGivenWstring)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"uppercase string";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        given.ConvertToLower();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FTextTest, ConvertToUpper_ChangesValueToUpperCase_WhenGivenWstring)
    {
        std::wstring givenWString = L"UpperCase String";
        std::wstring expectedWString = L"UPPERCASE STRING";
        FText given = FText(givenWString);
        FText expected = FText(expectedWString);

        given.ConvertToUpper();

        ASSERT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region IsEmptyOrWhitespace
    TEST(FTextTest, IsEmptyOrWhitespace_ReturnsTrue_WhenFTextConstructedEmpty)
    {
        FText given = FText();

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespace_ReturnsTrue_WhenFTextSetToNothing)
    {
        FText given = FText("Something");
        given = FText("");

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespace_ReturnsTrue_WhenFTextContainsASingleSpace)
    {
        FText given = FText(" ");

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespace_ReturnsTrue_WhenFTextContainsAManySpace)
    {
        FText given = FText("    ");

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespace_ReturnsFalse_WhenFTextContainsACharacterNotASpace)
    {
        FText given = FText("   t   ");

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_FALSE(actual);
    }
#pragma endregion

#pragma region IsEmptyOrWhitespace - Given WString
    TEST(FTextTest, IsEmptyOrWhitespaceWstring_ReturnsTrue_WhenFTextSetToNothing)
    {
        std::wstring givenWstring = L"Something";
        FText given = FText(givenWstring);
        given = FText("");

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespaceWstring_ReturnsTrue_WhenFTextContainsASingleSpace)
    {
        std::wstring givenWstring = L" ";
        FText given = FText(givenWstring);

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespaceWstring_ReturnsTrue_WhenFTextContainsAManySpace)
    {
        std::wstring givenWstring = L"    ";
        FText given = FText(givenWstring);

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_TRUE(actual);
    }

    TEST(FTextTest, IsEmptyOrWhitespaceWstring_ReturnsFalse_WhenFTextContainsACharacterNotASpace)
    {
        std::wstring givenWstring = L"   t   ";
        FText given = FText(givenWstring);

        bool actual = given.IsEmptyOrWhitespace();

        ASSERT_FALSE(actual);
    }
#pragma endregion

    std::string CutStringToSize(std::string toCut, size_t size)
    {
        std::string cutActual;
        cutActual.resize(size);
        for (int c = 0; c < size; ++c)
        {
            cutActual[c] += toCut[c];
        }

        return cutActual;
    }
}