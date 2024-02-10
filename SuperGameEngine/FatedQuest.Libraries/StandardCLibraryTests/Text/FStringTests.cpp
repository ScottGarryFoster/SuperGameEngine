#include <cstring>

#include "../LibraryIncludes.h"
#include "../../StandardCLibrary/Text/FString.h"

using namespace StandardCLibrary;
namespace StandardCLibraryTests_Text_FStringTests
{
    std::string CutStringToSize(std::string toCut, size_t size);

    TEST(FStringTest, OnConstruction_ReturnsEmptyString_WhenGivenNoInput)
    {
        std::string expected = "";

        FString actual = FString();
        
        EXPECT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

    TEST(FStringTest, OnConstruction_ReturnsAMatching_WhenGivenAnInput)
    {
        std::string expected = "something";

        FString actual = FString(expected);

        EXPECT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

    TEST(FStringTest, OnConstruction_ReturnsAFlattenedString_WhenGivenAVectorInput)
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
        FString actual = FString(given);

        // Assert
        EXPECT_TRUE(actual == expected) << "Expected: " << expected << " Actual: " << actual.AsStdString();
    }

#pragma region Operator Plus
    TEST(FStringTest, OperatorPlus_JoinsTogetherTwoFStrings_WhenRightHandIsAnFString)
    {
        FString left = FString("foo");
        FString right = "bar";
        FString expected = FString("foobar");
        
        FString actual = left + right;

        EXPECT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherFStringAndString_WhenRightHandIsAString)
    {
        FString left = FString("foo");
        std::string right = "bar";
        FString expected = FString("foobar");

        FString actual = left + right;

        EXPECT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherInt_WhenRightHandIsAnInt)
    {
        FString left = FString("foo");
        int right = 42;
        FString expected = FString("foo42");

        FString actual = left + right;

        EXPECT_TRUE(expected == actual) << "Expected: " << expected.AsStdString() << " Actual: " << actual.AsStdString();
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherFloat_WhenRightHandIsAnFloat)
    {
        FString left = FString("foo");
        float right = 42.421f;
        FString expected = FString("foo42.42");

        FString actual = left + right; 

        std::string cutActual = CutStringToSize(actual.AsStdString(), expected.AsStdString().size());
        EXPECT_TRUE(expected == cutActual) << "Expected: " << expected.AsStdString() << " Actual: " << cutActual;
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherDouble_WhenRightHandIsAnDouble)
    {
        FString left = FString("foo");
        double right = 42.421;
        FString expected = FString("foo42.42");

        FString actual = left + right;

        std::string cutActual = CutStringToSize(actual.AsStdString(), expected.AsStdString().size());
        EXPECT_TRUE(expected == cutActual) << "Expected: " << expected << " Actual: " << cutActual;
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherLongInt_WhenRightHandIsAnLongInt)
    {
        FString left = FString("foo");
        long int right = 42;
        FString expected = FString("foo42");

        FString actual = left + right;

        EXPECT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FStringTest, OperatorPlus_JoinsTogetherUnsignedLongInt_WhenRightHandIsAnUnsignedLongInt)
    {
        FString left = FString("foo");
        unsigned long int right = 42;
        FString expected = FString("foo42");

        FString actual = left + right;

        EXPECT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }
#pragma endregion

#pragma region Operator Equals
    TEST(FStringTest, OperatorEquals_ReturnsFalse_WhenTwoFStringDoNotEqual)
    {
        FString left = FString("foo");
        FString right = FString("bar");

        EXPECT_FALSE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FStringTest, OperatorEquals_ReturnsTrue_WhenTwoFStringEqual)
    {
        FString left = FString("foo");
        FString right = FString("foo");

        EXPECT_TRUE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FStringTest, OperatorEquals_ReturnsFalse_WhenStringComparedAndAreNotEqual)
    {
        FString left = FString("foo");
        std::string right = "bar";

        EXPECT_FALSE(left == right) << "Condition: " << left << " == " << right;
    }

    TEST(FStringTest, OperatorEquals_ReturnsTrue_WhenStringComparedAndEqual)
    {
        FString left = FString("foo");
        std::string right = "foo";

        EXPECT_TRUE(left == right) << "Condition: " << left << " == " << right;
    }
#pragma endregion

#pragma region Convertion
    TEST(FStringTest, AsStdString_ReturnsAnEqualString)
    {
        FString given = FString("foo");
        std::string expected = "foo";

        std::string actual = given.AsStdString();

        EXPECT_EQ(expected, actual);
    }

    TEST(FStringTest, AsCharArr_ReturnsAnEqualCharArr)
    {
        FString given = FString("foo");
        const char* expected = "foo";

        const char* actual = given.AsCharArr();

        EXPECT_EQ(std::strlen(expected), std::strlen(actual));
        for (unsigned int c = 0; c < std::strlen(actual); ++c)
        {
            EXPECT_EQ(expected[c], actual[c])
                << "Character: " << c << " was not equal. Expected: " << expected[c] << " Actual: " << actual[c];
        }
    }
#pragma endregion

#pragma region ToLower
    TEST(FStringTest, ToLower_ReturnsAllLowerCase_WhenGivenAnUpperCaseString)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("uppercase string");

        FString actual = given.ToLower();

        EXPECT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FStringTest, ToLower_DoesNotAffectOriginalString_WhenPerformed)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("UpperCase String");

        given.ToLower();

        EXPECT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region ToUpper
    TEST(FStringTest, ToUpper_ReturnsAllUpperCase_WhenGivenAnUpperCaseString)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("UPPERCASE STRING");

        FString actual = given.ToUpper();

        EXPECT_TRUE(expected == actual) << "Expected: " << expected << " Actual: " << actual;
    }

    TEST(FStringTest, ToUpper_DoesNotAffectOriginalString_WhenPerformed)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("UpperCase String");

        given.ToUpper();

        EXPECT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }
#pragma endregion

#pragma region ConvertToLowerAndUpper
    TEST(FStringTest, ConvertToLower_ChangesValueToLowerCase)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("uppercase string");

        given.ConvertToLower();

        EXPECT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
    }

    TEST(FStringTest, ConvertToUpper_ChangesValueToUpperCase)
    {
        FString given = FString("UpperCase String");
        FString expected = FString("UPPERCASE STRING");

        given.ConvertToUpper();

        EXPECT_TRUE(expected == given) << "Expected: " << expected << " Actual: " << given;
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