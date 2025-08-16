#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector4DTests : public ::testing::Test
    {
    public:
        FVector4DTests()
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

        double Distance(double x1, double y1, double z1, double w1, double x2, double y2, double z2, double w2) const
        {
            return static_cast<double>(sqrt(
                pow(x2 - x1, 2) + 
                pow(y2 - y1, 2) + 
                pow(z2 - z1, 2) + 
                pow(w2 - w1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector4DTests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector4D testCase = FVector4D();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
        ASSERT_EQ(0, testCase.GetW());
    }

    TEST_F(FVector4DTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenAtConstruction)
    {
        double givenX = 42.2;
        double givenY = 12.5;
        double givenZ = 19.1;
        double givenW = 10.4;

        FVector4D testCase = FVector4D(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4DTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenNegativeValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;
        double givenZ = -1.4;
        double givenW = -3.23;

        FVector4D testCase = FVector4D(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4DTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenVectorWithValues)
    {
        double givenX = -54.9;
        double givenY = -21.9;
        double givenZ = -15.9;
        double givenW = -76.9;
        FVector4D givenVector = FVector4D(givenX, givenY, givenZ, givenW);

        FVector4D testCase = FVector4D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4DTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenPointWithValues)
    {
        double givenX = 57;
        double givenY = 20;
        double expectedZ = 0;
        double expectedW = 0;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector4D testCase = FVector4D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector4DTests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4I(1, 2, 3, 4);

        auto testCase = FVector4D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

    TEST_F(FVector4DTests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4I(-5, -7, -10, -8);

        auto testCase = FVector4D(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Float

    TEST_F(FVector4DTests, OnConstructionWithFVector4F_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4F(1.5f, 9.5f, 15.6f, 9.1f);
        double expectedX = 1.5;
        double expectedY = 9.5;
        double expectedZ = 15.6;
        double expectedW = 9.1;

        auto testCase = FVector4D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedW, testCase.GetW()))
            << "expected: " << expectedW << " actual: " << testCase.GetW();
    }

    TEST_F(FVector4DTests, OnConstructionWithFVector4F_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4F(-5.3f, -7.9f, -6.2f, -9.1f);
        double expectedX = -5.3;
        double expectedY = -7.9;
        double expectedZ = -6.2;
        double expectedW = -9.1;

        auto testCase = FVector4D(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedW, testCase.GetW()))
            << "expected: " << expectedW << " actual: " << testCase.GetW();
    }

#pragma endregion

#pragma region SetXYZW
    TEST_F(FVector4DTests, SetX_UpdatesValueOfX)
    {
        double expectedX = 23.5;
        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector4DTests, SetY_UpdatesValueOfY)
    {
        double expectedY = 98.4;
        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector4DTests, SetZ_UpdatesValueOfZ)
    {
        double expectedY = 25.1;
        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedY, testCase.GetZ()) << "Z should not equal expected on construction. ";

        testCase.SetZ(expectedY);

        ASSERT_EQ(expectedY, testCase.GetZ());
    }

    TEST_F(FVector4DTests, SetW_UpdatesValueOfW)
    {
        double expectedW = 13.1;
        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedW, testCase.GetW()) << "W should not equal expected on construction. ";

        testCase.SetW(expectedW);

        ASSERT_EQ(expectedW, testCase.GetW());
    }

    TEST_F(FVector4DTests, SetXY_UpdatesXYValues_WhenGivendoubleValues)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        double expectedZ = 0;

        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector4DTests, SetXYZ_UpdatesXYZValues_WhenGivendoubleValues)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        double expectedZ = 12.5;

        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";
        ASSERT_NE(expectedZ, testCase.GetZ()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYZValue(expectedX, expectedY, expectedZ);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector4DTests, SetXYZW_UpdatesXYZWValues_WhenGivendoubleValues)
    {
        // Arrange
        double expectedX = 14.5;
        double expectedY = 98.4;
        double expectedZ = 12.5;
        double expectedW = 34.1;

        FVector4D testCase = FVector4D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";
        ASSERT_NE(expectedZ, testCase.GetZ()) << "Y should not equal expected on construction. ";
        ASSERT_NE(expectedW, testCase.GetW()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYZWValue(expectedX, expectedY, expectedZ, expectedW);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

#pragma endregion

#pragma region Operator+
#pragma region Operator+ As New Vector
    TEST_F(FVector4DTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4D expected = FVector4D(2, 1, 5, 1);
        FVector4D left = FVector4D(1, 1, 2 , 1);
        FVector4D right = FVector4D(1, 0, 3, 0);

        FVector4D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4D expected = FVector4D(1, 2, 5, 1);
        FVector4D left = FVector4D(1, 1, 2, 1);
        FVector4D right = FVector4D(0, 1, 3, 0);

        FVector4D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4D expected = FVector4D(1, 1, 4, 1);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(0, 0, 3, 0);

        FVector4D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, AddOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4D expected = FVector4D(1, 1, 1, 5);
        FVector4D left = FVector4D(1, 1, 1, 2);
        FVector4D right = FVector4D(0, 0, 0, 3);

        FVector4D actual = left + right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator+=
    TEST_F(FVector4DTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4D expected = FVector4D(2, 1, 5, 1);
        FVector4D left = FVector4D(1, 1, 2, 1);
        FVector4D right = FVector4D(1, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4D expected = FVector4D(1, 2, 5, 1);
        FVector4D left = FVector4D(1, 1, 2, 1);
        FVector4D right = FVector4D(0, 1, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4D expected = FVector4D(1, 1, 4, 1);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(0, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, AddEqualsOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4D expected = FVector4D(1, 1, 1, 5);
        FVector4D left = FVector4D(1, 1, 1, 2);
        FVector4D right = FVector4D(0, 0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector4DTests, SubtractOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4D expected = FVector4D(1, 0, 0, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(0, 1, 1, 1);

        FVector4D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, SubtractOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4D expected = FVector4D(0, 1, 0, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 0, 1, 1);

        FVector4D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, SubtractOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4D expected = FVector4D(0, 0, 1, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 0, 1);

        FVector4D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, SubtractOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4D expected = FVector4D(0, 0, 0, 1);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 0);

        FVector4D actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector4DTests, SubtractEqualsOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4D expected = FVector4D(0, 1, 0, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, SubtractEqualsOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4D expected = FVector4D(1, 0, 0, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(0, 1, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, SubtractEqualsOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4D expected = FVector4D(0, 0, 1, 0);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4DTests, SubtractEqualsOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4D expected = FVector4D(0, 0, 0, 1);
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector4DTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4D expected = FVector4D(2, 2, 2, 2);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 2;

        FVector4D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4D expected = FVector4D(-2, -2, -2, -2);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = -2;

        FVector4D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector4DTests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4D expected = FVector4D(2, 2, 2, 2);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4DTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4D expected = FVector4D(-2, -2, -2, -2);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector4DTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4D expected = FVector4D(0.5, 0.5, 0.5, 0.5);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 2;

        FVector4D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4D expected = FVector4D(0.1, 0.1, 0.1, 0.1);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 10;

        FVector4D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4D expected = FVector4D(-0.5, -0.5, -0.5, -0.5);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = -2;

        FVector4D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector4DTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4D expected = FVector4D(0.5, 0.5, 0.5, 0.5);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4DTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4D expected = FVector4D(0.1, 0.1, 0.1, 0.1);
        FVector4D given = FVector4D(1, 1, 1, 1);
        double scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4DTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4D expected = FVector4D(-0.5, -0.5, -0.5, -0.5);
        FVector4D given = FVector4D(1, 1, 1, 1);
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
    TEST_F(FVector4DTests, Normalize_DividesPositionByMagnitude)
    {
        FVector4D given = FVector4D(2, 2, 2, 2);
        double magnitude = given.Magnitude();
        FVector4D expected = given / magnitude;

        FVector4D actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector4DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 + 2 * 2 + 2 * 2 = 16
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        double expected = 4;
        FVector4D given = FVector4D(2, 2, 2, 2);

        double actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector4DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 + 4 * 4 = 126 
        // then sq(126) = 11.22497 (the epsilon rounds this to 5dp)
        double expected = 11.22497;
        FVector4D given = FVector4D(2, -5, -9, 4);

        double actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector4DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector4D left = FVector4D(1.1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector4D left = FVector4D(1.01, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector4D left = FVector4D(1.001, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector4D left = FVector4D(1.0001, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector4D left = FVector4D(1.00001, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector4D left = FVector4D(1.000001, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector4DTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8 = 70
        double expected = 70;
        FVector4D left = FVector4D(1, 2, 3 ,4);
        FVector4D right = FVector4D(5, 6, 7, 8);

        double actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector4DTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector4D left = FVector4D(1, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);
        double expected = 0;

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        double expected = 1;
        FVector4D left = FVector4D(2, 1, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        double expected = 1;
        FVector4D left = FVector4D(1, 2, 1, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        double expected = 1;
        FVector4D left = FVector4D(1, 1, 2, 1);
        FVector4D right = FVector4D(1, 1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, Distance_Returns1_WhenGivenIsOneAwayOnW)
    {
        double expected = 1;
        FVector4D left = FVector4D(1, 1, 1, 2);
        FVector4D right = FVector4D(1, 1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4DTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        double expected = Distance(5, 6, 7, 8, 9, 10, 11, 12);
        FVector4D left = FVector4D(5, 6, 7, 8);
        FVector4D right = FVector4D(9, 10, 11, 12);

        double actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}