#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector2FTests : public ::testing::Test
    {
    public:
        FVector2FTests()
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
    TEST_F(FVector2FTests, OnConstruction_XYReturnZero_WhenNothingIsPassedIn)
    {
        FVector2F testCase = FVector2F();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstruction_XYReturnsGivenValues_WhenGivenAtConstruction)
    {
        float givenX = 42.2f;
        float givenY = 12.5f;

        FVector2F testCase = FVector2F(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstruction_XYReturnsGivenValues_WhenGivenNegativeValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;

        FVector2F testCase = FVector2F(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstruction_XYReturnsGivenValues_WhenGivenVectorWithValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        FVector2F givenVector = FVector2F(givenX, givenY);

        FVector2F testCase = FVector2F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstruction_XYReturnsGivenValues_WhenGivenPointWithValues)
    {
        float givenX = 57;
        float givenY = 20;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector2F testCase = FVector2F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector2FTests, OnConstructionWithFVector2I_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2I(1, 2);

        auto testCase = FVector2F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstructionWithFVector2I_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2I(-5, -7);

        auto testCase = FVector2F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector2FTests, OnConstructionWithFVector2D_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2D(1.5, 9.5);
        float expectedX = 1.5f;
        float expectedY = 9.5f;

        auto testCase = FVector2F(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2FTests, OnConstructionWithFVector2D_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2D(-5.3, -7.9);
        double expectedX = -5.3f;
        double expectedY = -7.9f;

        auto testCase = FVector2F(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector2FTests, SetX_UpdatesValueOfX)
    {
        float expectedX = 23.5f;
        FVector2F testCase = FVector2F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector2FTests, SetY_UpdatesValueOfY)
    {
        float expectedY = 98.4f;
        FVector2F testCase = FVector2F();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2FTests, SetXY_UpdatesXYValues_WhenGivenFloatValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;

        FVector2F testCase = FVector2F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2FTests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        FVector2F given = FVector2F(expectedX, expectedY);

        FVector2F testCase = FVector2F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2FTests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        FPoint given = FPoint(expectedX, expectedY);

        FVector2F testCase = FVector2F();
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
    TEST_F(FVector2FTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2F expected = FVector2F(2, 1);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 0);

        FVector2F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2F expected = FVector2F(1, 2);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(0, 1);

        FVector2F actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector2FTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2F expected = FVector2F(2, 1);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2FTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2F expected = FVector2F(1, 2);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(0, 1);

        left += right;

        ASSERT_EQ(expected, left);
    }
#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector2FTests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2F expected = FVector2F(0, 1);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 0);

        FVector2F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2F expected = FVector2F(1, 0);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(0, 1);

        FVector2F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector2FTests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2F expected = FVector2F(0, 1);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2FTests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2F expected = FVector2F(1, 0);
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector2FTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector2F expected = FVector2F(2, 2);
        FVector2F given = FVector2F(1, 1);
        float scalar = 2;

        FVector2F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector2F expected = FVector2F(-2, -2);
        FVector2F given = FVector2F(1, 1);
        float scalar = -2;

        FVector2F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector2FTests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector2F expected = FVector2F(2, 2);
        FVector2F given = FVector2F(1, 1);
        float scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2FTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector2F expected = FVector2F(-2, -2);
        FVector2F given = FVector2F(1, 1);
        float scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector2FTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector2F expected = FVector2F(0.5f, 0.5f);
        FVector2F given = FVector2F(1, 1);
        float scalar = 2;

        FVector2F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector2F expected = FVector2F(0.1f, 0.1f);
        FVector2F given = FVector2F(1, 1);
        float scalar = 10;

        FVector2F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2F expected = FVector2F(-0.5f, -0.5f);
        FVector2F given = FVector2F(1, 1);
        float scalar = -2;

        FVector2F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector2FTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector2F expected = FVector2F(0.5f, 0.5f);
        FVector2F given = FVector2F(1, 1);
        float scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2FTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector2F expected = FVector2F(0.1f, 0.1f);
        FVector2F given = FVector2F(1, 1);
        float scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2FTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2F expected = FVector2F(-0.5f, -0.5f);
        FVector2F given = FVector2F(1, 1);
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
    TEST_F(FVector2FTests, Normalize_DividesPositionByMagnitude)
    {
        FVector2F given = FVector2F(2, 2);
        float magnitude = given.Magnitude();
        FVector2F expected = given / magnitude;

        FVector2F actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector2FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 = 8 
        // then sq(8) = 2.82843f (the eplision rounds this to 5dp)
        float expected = 2.82843f;
        FVector2F given = FVector2F(2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector2FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 = 29 
        // then sq(29) = 5.38516 (the epsilon rounds this to 5dp)
        float expected = 5.38516f;
        FVector2F given = FVector2F(2, -5);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector2FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector2F left = FVector2F(1.1f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector2F left = FVector2F(1.01f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector2F left = FVector2F(1.001f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector2F left = FVector2F(1.0001f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector2F left = FVector2F(1.00001f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector2F left = FVector2F(1.000001f, 1);
        FVector2F right = FVector2F(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector2FTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 3 + 2 * 4 = 3 + 8 = 11
        float expected = 11;
        FVector2F left = FVector2F(1, 2);
        FVector2F right = FVector2F(3, 4);

        float actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector2FTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector2F left = FVector2F(1, 1);
        FVector2F right = FVector2F(1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        FVector2F left = FVector2F(2, 1);
        FVector2F right = FVector2F(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        FVector2F left = FVector2F(1, 2);
        FVector2F right = FVector2F(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2FTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8);
        FVector2F left = FVector2F(5, 6);
        FVector2F right = FVector2F(7, 8);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the float helper compare.
        ASSERT_EQ(expected, actual);        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}