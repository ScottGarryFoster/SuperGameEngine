#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector3FTests : public ::testing::Test
    {
    public:
        FVector3FTests()
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

        float Distance(float x1, float y1, float z1, float x2, float y2, float z2) const
        {
            return static_cast<float>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector3FTests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector3F testCase = FVector3F();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
    }

    TEST_F(FVector3FTests, OnConstruction_XYZReturnsGivenValues_WhenGivenAtConstruction)
    {
        float givenX = 42.2f;
        float givenY = 12.5f;
        float givenZ = 19.1f;

        FVector3F testCase = FVector3F(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3FTests, OnConstruction_XYZReturnsGivenValues_WhenGivenNegativeValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        float givenZ = -1.4f;

        FVector3F testCase = FVector3F(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3FTests, OnConstruction_XYZReturnsGivenValues_WhenGivenVectorWithValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        float givenZ = -15.9f;
        FVector3F givenVector = FVector3F(givenX, givenY, givenZ);

        FVector3F testCase = FVector3F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3FTests, OnConstruction_XYZReturnsGivenValues_WhenGivenPointWithValues)
    {
        float givenX = 57;
        float givenY = 20;
        float expectedZ = 0;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector3F testCase = FVector3F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector3FTests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3I(1, 2, 3);

        auto testCase = FVector3F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
    }

    TEST_F(FVector3FTests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenNegatives)
    {
        auto given = FVector3I(-5, -7, -10);

        auto testCase = FVector3F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector3FTests, OnConstructionWithFVector3F_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3D(1.5, 9.5, 15.6);
        float expectedX = 1.5f;
        float expectedY = 9.5f;
        float expectedZ = 15.6f;

        auto testCase = FVector3F(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
    }

    TEST_F(FVector3FTests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector3D(-5.3, -7.9, -6.2);
        float expectedX = -5.3f;
        float expectedY = -7.9f;
        float expectedZ = -6.2f;

        auto testCase = FVector3F(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector3FTests, SetX_UpdatesValueOfX)
    {
        float expectedX = 23.5f;
        FVector3F testCase = FVector3F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector3FTests, SetY_UpdatesValueOfY)
    {
        float expectedY = 98.4f;
        FVector3F testCase = FVector3F();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector3FTests, SetXY_UpdatesXYValues_WhenGivenfloatValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        float expectedZ = 0;

        FVector3F testCase = FVector3F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3FTests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        float expectedZ = 0;
        FVector3F given = FVector3F(expectedX, expectedY, expectedZ);

        FVector3F testCase = FVector3F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3FTests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        int expectedZ = 0;
        FPoint given = FPoint(expectedX, expectedY);

        FVector3F testCase = FVector3F();
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
    TEST_F(FVector3FTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3F expected = FVector3F(2, 1, 5);
        FVector3F left = FVector3F(1, 1, 2);
        FVector3F right = FVector3F(1, 0, 3);

        FVector3F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3F expected = FVector3F(1, 2, 5);
        FVector3F left = FVector3F(1, 1, 2);
        FVector3F right = FVector3F(0, 1, 3);

        FVector3F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3F expected = FVector3F(1, 1, 4);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(0, 0, 3);

        FVector3F actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector3FTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3F expected = FVector3F(2, 1, 5);
        FVector3F left = FVector3F(1, 1, 2);
        FVector3F right = FVector3F(1, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3FTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3F expected = FVector3F(1, 2, 5);
        FVector3F left = FVector3F(1, 1, 2);
        FVector3F right = FVector3F(0, 1, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3FTests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3F expected = FVector3F(1, 1, 4);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector3FTests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3F expected = FVector3F(1, 0, 0);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(0, 1, 1);

        FVector3F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3F expected = FVector3F(0, 1, 0);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 0, 1);

        FVector3F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, SubtractOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3F expected = FVector3F(0, 0, 1);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 1, 0);

        FVector3F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector3FTests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3F expected = FVector3F(0, 1, 0);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3FTests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3F expected = FVector3F(1, 0, 0);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3FTests, SubtractEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3F expected = FVector3F(0, 0, 1);
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector3FTests, MultiplyOperator_floatsVector_WhenGivenScalarOf2)
    {
        FVector3F expected = FVector3F(2, 2, 2);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 2;

        FVector3F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3F expected = FVector3F(-2, -2, -2);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = -2;

        FVector3F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector3FTests, MultiplyEqualsOperator_floatsVector_WhenGivenScalarOf2)
    {
        FVector3F expected = FVector3F(2, 2, 2);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3FTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3F expected = FVector3F(-2, -2, -2);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector3FTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3F expected = FVector3F(0.5f, 0.5f, 0.5);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 2;

        FVector3F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3F expected = FVector3F(0.1f, 0.1f, 0.1f);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 10;

        FVector3F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3F expected = FVector3F(-0.5f, -0.5f, -0.5f);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = -2;

        FVector3F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector3FTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3F expected = FVector3F(0.5f, 0.5f, 0.5f);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3FTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3F expected = FVector3F(0.1f, 0.1f, 0.1f);
        FVector3F given = FVector3F(1, 1, 1);
        float scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector3FTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3F expected = FVector3F(-0.5f, -0.5f, -0.5f);
        FVector3F given = FVector3F(1, 1, 1);
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
    TEST_F(FVector3FTests, Normalize_DividesPositionByMagnitude)
    {
        FVector3F given = FVector3F(2, 2, 2);
        float magnitude = given.Magnitude();
        FVector3F expected = given / magnitude;

        FVector3F actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector3FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2+ 2 * 2 = 12
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        float expected = 3.46410f;
        FVector3F given = FVector3F(2, 2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector3FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 = 110 
        // then sq(110) = 10.48809 (the epsilon rounds this to 5dp)
        float expected = 10.48809f;
        FVector3F given = FVector3F(2, -5, -9);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector3FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector3F left = FVector3F(1.1f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector3F left = FVector3F(1.01f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector3F left = FVector3F(1.001f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector3F left = FVector3F(1.0001f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector3F left = FVector3F(1.00001f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector3F left = FVector3F(1.000001f, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector3FTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 4 + 2 * 5 + 3 * 6 = 32
        float expected = 32;
        FVector3F left = FVector3F(1, 2, 3);
        FVector3F right = FVector3F(4, 5, 6);

        float actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector3FTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector3F left = FVector3F(1, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        FVector3F left = FVector3F(2, 1, 1);
        FVector3F right = FVector3F(1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        FVector3F left = FVector3F(1, 2, 1);
        FVector3F right = FVector3F(1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        float expected = 1;
        FVector3F left = FVector3F(1, 1, 2);
        FVector3F right = FVector3F(1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3FTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8, 9, 10);
        FVector3F left = FVector3F(5, 6, 7);
        FVector3F right = FVector3F(8, 9, 10);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the float helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}