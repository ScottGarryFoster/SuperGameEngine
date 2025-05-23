#include "../../StandardObjects/AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector2ITests : public ::testing::Test
    {
    public:
        FVector2ITests()
        {
        }

    protected:

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        float Distance(float x1, float y1, float x2, float y2) const
        {
            return static_cast<float>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector2ITests, OnConstruction_XYReturnZero_WhenNothingIsPassedIn)
    {
        FVector2I testCase = FVector2I();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstruction_XYReturnsGivenValues_WhenGivenAtConstruction)
    {
        int givenX = 42;
        int givenY = 12;

        FVector2I testCase = FVector2I(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstruction_XYReturnsGivenValues_WhenGivenNegativeValues)
    {
        int givenX = -54;
        int givenY = -21;

        FVector2I testCase = FVector2I(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstruction_XYReturnsGivenValues_WhenGivenVectorWithValues)
    {
        int givenX = -54;
        int givenY = -21;
        FVector2I givenVector = FVector2I(givenX, givenY);

        FVector2I testCase = FVector2I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstruction_XYReturnsGivenValues_WhenGivenPointWithValues)
    {
        int givenX = 57;
        int givenY = 20;
        FPoint givenVector = FPoint(givenX, givenY);

        FVector2I testCase = FVector2I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Float

    TEST_F(FVector2ITests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2F(1.5F, 9.5F);
        int expectedX = 1;
        int expectedY = 9;

        auto testCase = FVector2I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2F(-5.3f, -7.9f);
        int expectedX = -5;
        int expectedY = -7;

        auto testCase = FVector2I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector2ITests, OnConstructionWithFVector2D_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2D(1.5, 9.5);
        int expectedX = 1;
        int expectedY = 9;

        auto testCase = FVector2I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2ITests, OnConstructionWithFVector2D_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2D(-5.3, -7.9);
        int expectedX = -5;
        int expectedY = -7;

        auto testCase = FVector2I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector2ITests, SetX_UpdatesValueOfX)
    {
        int expectedX = 23;
        FVector2I testCase = FVector2I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector2ITests, SetY_UpdatesValueOfY)
    {
        int expectedY = 98;
        FVector2I testCase = FVector2I();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2ITests, SetXY_UpdatesXYValues_WhenGivenFloatValues)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;

        FVector2I testCase = FVector2I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2ITests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        FVector2I given = FVector2I(expectedX, expectedY);

        FVector2I testCase = FVector2I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2ITests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        FPoint given = FPoint(expectedX, expectedY);

        FVector2I testCase = FVector2I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }
#pragma endregion

#pragma region Operator+
#pragma region Operator+ As New Vector
    TEST_F(FVector2ITests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        auto expected = FVector2I(2, 1);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(1, 0);

        FVector2I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        auto expected = FVector2I(1, 2);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(0, 1);

        FVector2I actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector2ITests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        auto expected = FVector2I(2, 1);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(1, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2ITests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        auto expected = FVector2I(1, 2);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(0, 1);

        left += right;

        ASSERT_EQ(expected, left);
    }
#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector2ITests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        auto expected = FVector2I(0, 1);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(1, 0);

        FVector2I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        auto expected = FVector2I(1, 0);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(0, 1);

        FVector2I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector2ITests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        auto expected = FVector2I(0, 1);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2ITests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        auto expected = FVector2I(1, 0);
        auto left = FVector2I(1, 1);
        auto right = FVector2I(0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector2ITests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        auto expected = FVector2I(2, 2);
        auto given = FVector2I(1, 1);
        int scalar = 2;

        FVector2I actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        auto expected = FVector2I(-2, -2);
        auto given = FVector2I(1, 1);
        int scalar = -2;

        FVector2I actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector2ITests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        auto expected = FVector2I(2, 2);
        auto given = FVector2I(1, 1);
        int scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2ITests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        auto expected = FVector2I(-2, -2);
        auto given = FVector2I(1, 1);
        int scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector2ITests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        auto expected = FVector2I(2, 2);
        auto given = FVector2I(4, 4);
        int scalar = 2;

        FVector2I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        auto expected = FVector2I(1, 1);
        auto given = FVector2I(10, 10);
        int scalar = 10;

        FVector2I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        auto expected = FVector2I(-2, -2);
        auto given = FVector2I(4, 4);
        int scalar = -2;

        FVector2I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector2ITests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        auto expected = FVector2I(2, 2);
        auto given = FVector2I(4, 4);
        int scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2ITests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        auto expected = FVector2I(1, 1);
        auto given = FVector2I(10, 10);
        int scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2ITests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2I expected = FVector2I(-2, -2);
        FVector2I given = FVector2I(4, 4);
        float scalar = -2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Normalize
    /// <remark>
    /// These are none perfect tests because they replicate what the 
    /// implementation does but the operation is simple and mathematical
    /// so there is not a much better way of doing it.
    /// </remark>
    TEST_F(FVector2ITests, Normalize_DividesPositionByMagnitude)
    {
        FVector2I given = FVector2I(2, 2);
        float magnitude = given.Magnitude();
        FVector2I expected = given / static_cast<int>(magnitude);

        FVector2I actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector2ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 = 8 
        // then sq(8) = 2.82843f (the eplision rounds this to 5dp)
        float expected = 2.82843f;
        FVector2I given = FVector2I(2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector2ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 = 29 
        // then sq(29) = 5.38516 (the epsilon rounds this to 5dp)
        float expected = 5.38516f;
        FVector2I given = FVector2I(2, -5);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector2ITests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqual)
    {
        FVector2I left = FVector2I(1, 1);
        FVector2I right = FVector2I(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector2ITests, EqualsOperator_ReturnsFalse_WhenFirstValueIsNotEqual)
    {
        FVector2I left = FVector2I(2, 1);
        FVector2I right = FVector2I(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2ITests, EqualsOperator_ReturnsFalse_WhenSecondValueIsNotEqual)
    {
        FVector2I left = FVector2I(1, 2);
        FVector2I right = FVector2I(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

#pragma endregion

#pragma region DotProduct
    TEST_F(FVector2ITests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 3 + 2 * 4 = 3 + 8 = 11
        int expected = 11;
        auto left = FVector2I(1, 2);
        auto right = FVector2I(3, 4);

        int actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector2ITests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        auto left = FVector2I(1, 1);
        auto right = FVector2I(1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        auto left = FVector2I(2, 1);
        auto right = FVector2I(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        auto left = FVector2I(1, 2);
        auto right = FVector2I(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2ITests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8);
        auto left = FVector2I(5, 6);
        auto right = FVector2I(7, 8);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the float helper compare.
        ASSERT_EQ(expected, actual);
    }

#pragma endregion


}