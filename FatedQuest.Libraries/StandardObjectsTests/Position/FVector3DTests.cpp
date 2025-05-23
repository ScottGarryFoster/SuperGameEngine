#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector3DTests : public ::testing::Test
    {
    public:
        FVector3DTests()
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

        double Distance(double x1, double y1, double z1, double x2, double y2, double z2) const
        {
            return static_cast<double>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector3DTests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector3D testCase = FVector3D();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
    }

    TEST_F(FVector3DTests, OnConstruction_XYZReturnsGivenValues_WhenGivenAtConstruction)
    {
        double givenX = 42.2;
        double givenY = 12.5;
        double givenZ = 19.1;

        FVector3D testCase = FVector3D(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3DTests, OnConstruction_XYZReturnsGivenValues_WhenGivenNegativeValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;
        double givenZ = -1.4;

        FVector3D testCase = FVector3D(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3DTests, OnConstruction_XYZReturnsGivenValues_WhenGivenVectorWithValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;
        double givenZ = -15.9;
        FVector3D givenVector = FVector3D(givenX, givenY, givenZ);

        FVector3D testCase = FVector3D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3DTests, OnConstruction_XYZReturnsGivenValues_WhenGivenPointWithValues)
    {
        double givenX = 57;
        double givenY = 20;
        double expectedZ = 0;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector3D testCase = FVector3D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector3DTests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3I(1, 2, 3);

        auto testCase = FVector3D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
    }

    TEST_F(FVector3DTests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenNegatives)
    {
        auto given = FVector3I(-5, -7, -10);

        auto testCase = FVector3D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Float

    TEST_F(FVector3DTests, OnConstructionWithFVector3F_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3F(1.5f, 9.5f, 15.6f);
        double expectedX = 1.5;
        double expectedY = 9.5;
        double expectedZ = 15.6;

        auto testCase = FVector3D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
    }

    TEST_F(FVector3DTests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector3F(-5.3f, -7.9f, -6.2f);
        double expectedX = -5.3;
        double expectedY = -7.9;
        double expectedZ = -6.2;

        auto testCase = FVector3D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector3DTests, SetX_UpdatesValueOfX)
    {
        double expectedX = 23.5;
        FVector3D testCase = FVector3D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector3DTests, SetY_UpdatesValueOfY)
    {
        double expectedY = 98.4;
        FVector3D testCase = FVector3D();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector3DTests, SetXY_UpdatesXYValues_WhenGivendoubleValues)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        double expectedZ = 0;

        FVector3D testCase = FVector3D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3DTests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        double expectedZ = 0;
        FVector3D given = FVector3D(expectedX, expectedY, expectedZ);

        FVector3D testCase = FVector3D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3DTests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        int expectedZ = 0;
        FPoint given = FPoint(expectedX, expectedY);

        FVector3D testCase = FVector3D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }
#pragma endregion

#pragma region Operator+
#pragma region Operator+ As New Vector
    TEST_F(FVector3DTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3D expected = FVector3D(2, 1, 5);
        FVector3D left = FVector3D(1, 1, 2);
        FVector3D right = FVector3D(1, 0, 3);

        FVector3D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3D expected = FVector3D(1, 2, 5);
        FVector3D left = FVector3D(1, 1, 2);
        FVector3D right = FVector3D(0, 1, 3);

        FVector3D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3D expected = FVector3D(1, 1, 4);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(0, 0, 3);

        FVector3D actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector3DTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3D expected = FVector3D(2, 1, 5);
        FVector3D left = FVector3D(1, 1, 2);
        FVector3D right = FVector3D(1, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3DTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3D expected = FVector3D(1, 2, 5);
        FVector3D left = FVector3D(1, 1, 2);
        FVector3D right = FVector3D(0, 1, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3DTests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3D expected = FVector3D(1, 1, 4);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector3DTests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3D expected = FVector3D(1, 0, 0);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(0, 1, 1);

        FVector3D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3D expected = FVector3D(0, 1, 0);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 0, 1);

        FVector3D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, SubtractOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3D expected = FVector3D(0, 0, 1);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 1, 0);

        FVector3D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector3DTests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3D expected = FVector3D(0, 1, 0);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3DTests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3D expected = FVector3D(1, 0, 0);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3DTests, SubtractEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3D expected = FVector3D(0, 0, 1);
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector3DTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector3D expected = FVector3D(2, 2, 2);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 2;

        FVector3D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3D expected = FVector3D(-2, -2, -2);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = -2;

        FVector3D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector3DTests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector3D expected = FVector3D(2, 2, 2);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3DTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3D expected = FVector3D(-2, -2, -2);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector3DTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3D expected = FVector3D(0.5f, 0.5f, 0.5);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 2;

        FVector3D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3D expected = FVector3D(0.1f, 0.1f, 0.1f);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 10;

        FVector3D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3D expected = FVector3D(-0.5f, -0.5f, -0.5f);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = -2;

        FVector3D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector3DTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3D expected = FVector3D(0.5f, 0.5f, 0.5f);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3DTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3D expected = FVector3D(0.1f, 0.1f, 0.1f);
        FVector3D given = FVector3D(1, 1, 1);
        double scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3DTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3D expected = FVector3D(-0.5f, -0.5f, -0.5f);
        FVector3D given = FVector3D(1, 1, 1);
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
    TEST_F(FVector3DTests, Normalize_DividesPositionByMagnitude)
    {
        FVector3D given = FVector3D(2, 2, 2);
        double magnitude = given.Magnitude();
        FVector3D expected = given / magnitude;

        FVector3D actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector3DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2+ 2 * 2 = 12
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        double expected = 3.46410f;
        FVector3D given = FVector3D(2, 2, 2);

        double actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector3DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 = 110 
        // then sq(110) = 10.48809 (the epsilon rounds this to 5dp)
        double expected = 10.48809f;
        FVector3D given = FVector3D(2, -5, -9);

        double actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector3DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector3D left = FVector3D(1.1, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector3D left = FVector3D(1.01, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector3D left = FVector3D(1.001, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector3D left = FVector3D(1.0001, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector3D left = FVector3D(1.00001, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector3D left = FVector3D(1.000001, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector3DTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 4 + 2 * 5 + 3 * 6 = 32
        double expected = 32;
        FVector3D left = FVector3D(1, 2, 3);
        FVector3D right = FVector3D(4, 5, 6);

        double actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector3DTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector3D left = FVector3D(1, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);
        double expected = 0;

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        double expected = 1;
        FVector3D left = FVector3D(2, 1, 1);
        FVector3D right = FVector3D(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        double expected = 1;
        FVector3D left = FVector3D(1, 2, 1);
        FVector3D right = FVector3D(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        double expected = 1;
        FVector3D left = FVector3D(1, 1, 2);
        FVector3D right = FVector3D(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3DTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        double expected = Distance(5, 6, 7, 8, 9, 10);
        FVector3D left = FVector3D(5, 6, 7);
        FVector3D right = FVector3D(8, 9, 10);

        double actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_EQ(expected, actual);
    }

#pragma endregion


}