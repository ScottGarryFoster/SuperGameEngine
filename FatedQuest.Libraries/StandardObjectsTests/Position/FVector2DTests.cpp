#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector2DTests : public ::testing::Test
    {
    public:
        FVector2DTests()
        {
        }

    protected:

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        double Distance(double x1, double y1, double x2, double y2) const
        {
            return static_cast<double>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector2DTests, OnConstruction_XYReturnZero_WhenNothingIsPassedIn)
    {
        FVector2D testCase = FVector2D();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenAtConstruction)
    {
        double givenX = 42.2;
        double givenY = 12.5;

        FVector2D testCase = FVector2D(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenNegativeValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;

        FVector2D testCase = FVector2D(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenVectorWithValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;
        FVector2D givenVector = FVector2D(givenX, givenY);

        FVector2D testCase = FVector2D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenPointWithValues)
    {
        double givenX = 57;
        double givenY = 20;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector2D testCase = FVector2D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector2DTests, OnConstructionWithFVector2I_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2I(1, 2);

        auto testCase = FVector2D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstructionWithFVector2I_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2I(-5, -7);

        auto testCase = FVector2D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
    }

#pragma endregion

#pragma region Constructor From Float

    TEST_F(FVector2DTests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenPositives)
    {
        auto given = FVector2F(1.5f, 9.5f);
        double expectedX = 1.5;
        double expectedY = 9.5;

        auto testCase = FVector2D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
    }

    TEST_F(FVector2DTests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector2F(-5.3f, -7.9f);
        double expectedX = -5.3;
        double expectedY = -7.9;

        auto testCase = FVector2D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector2DTests, SetX_UpdatesValueOfX)
    {
        double expectedX = 23.5;
        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector2DTests, SetY_UpdatesValueOfY)
    {
        double expectedY = 98.4;
        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2DTests, SetXY_UpdatesXYValues_WhenGivendoubleValues)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;

        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2DTests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        FVector2D given = FVector2D(expectedX, expectedY);

        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2DTests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        FPoint given = FPoint(expectedX, expectedY);

        FVector2D testCase = FVector2D();
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
    TEST_F(FVector2DTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2D expected = FVector2D(2, 1);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 0);

        FVector2D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2D expected = FVector2D(1, 2);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(0, 1);

        FVector2D actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector2DTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2D expected = FVector2D(2, 1);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2DTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2D expected = FVector2D(1, 2);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(0, 1);

        left += right;

        ASSERT_EQ(expected, left);
    }
#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector2DTests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2D expected = FVector2D(0, 1);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 0);

        FVector2D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2D expected = FVector2D(1, 0);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(0, 1);

        FVector2D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector2DTests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector2D expected = FVector2D(0, 1);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector2DTests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector2D expected = FVector2D(1, 0);
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector2DTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(2, 2);
        FVector2D given = FVector2D(1, 1);
        double scalar = 2;

        FVector2D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-2, -2);
        FVector2D given = FVector2D(1, 1);
        double scalar = -2;

        FVector2D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector2DTests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(2, 2);
        FVector2D given = FVector2D(1, 1);
        double scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2DTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-2, -2);
        FVector2D given = FVector2D(1, 1);
        double scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector2DTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(0.5f, 0.5f);
        FVector2D given = FVector2D(1, 1);
        double scalar = 2;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector2D expected = FVector2D(0.1f, 0.1f);
        FVector2D given = FVector2D(1, 1);
        double scalar = 10;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-0.5f, -0.5f);
        FVector2D given = FVector2D(1, 1);
        double scalar = -2;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector2DTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(0.5f, 0.5f);
        FVector2D given = FVector2D(1, 1);
        double scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2DTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector2D expected = FVector2D(0.1f, 0.1f);
        FVector2D given = FVector2D(1, 1);
        double scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector2DTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-0.5f, -0.5f);
        FVector2D given = FVector2D(1, 1);
        double scalar = -2;

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
    TEST_F(FVector2DTests, Normalize_DividesPositionByMagnitude)
    {
        FVector2D given = FVector2D(2, 2);
        double magnitude = given.Magnitude();
        FVector2D expected = given / magnitude;

        FVector2D actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector2DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 = 8 
        // then sq(8) = 2.82843f (the eplision rounds this to 5dp)
        double expected = 2.82843f;
        FVector2D given = FVector2D(2, 2);

        double actual = given.Magnitude();

         ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
             << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector2DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 = 29 
        // then sq(29) = 5.38516 (the epsilon rounds this to 5dp)
        double expected = 5.38516f;
        FVector2D given = FVector2D(2, -5);

        double actual = given.Magnitude();

         ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
             << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector2DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector2D left = FVector2D(1.1, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector2D left = FVector2D(1.01, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector2D left = FVector2D(1.001, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector2D left = FVector2D(1.0001, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector2D left = FVector2D(1.00001, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector2D left = FVector2D(1.000001, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector2DTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 3 + 2 * 4 = 3 + 8 = 11
        double expected = 11;
        FVector2D left = FVector2D(1, 2);
        FVector2D right = FVector2D(3, 4);

        double actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector2DTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 1);
        double expected = 0;

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        double expected = 1;
        FVector2D left = FVector2D(2, 1);
        FVector2D right = FVector2D(1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        double expected = 1;
        FVector2D left = FVector2D(1, 2);
        FVector2D right = FVector2D(1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        double expected = Distance(5, 6, 7, 8);
        FVector2D left = FVector2D(5, 6);
        FVector2D right = FVector2D(7, 8);

        double actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}