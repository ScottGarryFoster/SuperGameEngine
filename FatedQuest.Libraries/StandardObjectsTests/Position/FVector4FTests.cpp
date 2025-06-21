#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector4FTests : public ::testing::Test
    {
    public:
        FVector4FTests()
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

        float Distance(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2) const
        {
            return static_cast<float>(sqrt(
                pow(x2 - x1, 2) +
                pow(y2 - y1, 2) +
                pow(z2 - z1, 2) +
                pow(w2 - w1, 2)));
        }
    };

#pragma region Construction
    TEST_F(FVector4FTests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector4F testCase = FVector4F();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
        ASSERT_EQ(0, testCase.GetW());
    }

    TEST_F(FVector4FTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenAtConstruction)
    {
        float givenX = 42.2f;
        float givenY = 12.5f;
        float givenZ = 19.1f;
        float givenW = 10.4f;

        FVector4F testCase = FVector4F(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4FTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenNegativeValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        float givenZ = -1.4f;
        float givenW = -3.23f;

        FVector4F testCase = FVector4F(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4FTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenVectorWithValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        float givenZ = -15.9f;
        float givenW = -76.9f;
        FVector4F givenVector = FVector4F(givenX, givenY, givenZ, givenW);

        FVector4F testCase = FVector4F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4FTests, OnConstruction_XYZWReturnsGivenValues_WhenGivenPointWithValues)
    {
        float givenX = 57;
        float givenY = 20;
        float expectedZ = 0;
        float expectedW = 0;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector4F testCase = FVector4F(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector4FTests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4I(1, 2, 3, 4);

        auto testCase = FVector4F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

    TEST_F(FVector4FTests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4I(-5, -7, -10, -8);

        auto testCase = FVector4F(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector4FTests, OnConstructionWithFVector4D_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4D(1.5, 9.5, 15.6, 9.1);
        float expectedX = 1.5f;
        float expectedY = 9.5f;
        float expectedZ = 15.6f;
        float expectedW = 9.1f;

        auto testCase = FVector4F(given);

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedX, testCase.GetX()))
            << "expected: " << expectedX << " actual: " << testCase.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedY, testCase.GetY()))
            << "expected: " << expectedY << " actual: " << testCase.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedZ, testCase.GetZ()))
            << "expected: " << expectedZ << " actual: " << testCase.GetZ();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedW, testCase.GetW()))
            << "expected: " << expectedW << " actual: " << testCase.GetW();
    }

    TEST_F(FVector4FTests, OnConstructionWithFVector4D_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4D(-5.3, -7.9, -6.2, -9.1);
        float expectedX = -5.3f;
        float expectedY = -7.9f;
        float expectedZ = -6.2f;
        float expectedW = -9.1f;

        auto testCase = FVector4F(given);

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
    TEST_F(FVector4FTests, SetX_UpdatesValueOfX)
    {
        float expectedX = 23.5f;
        FVector4F testCase = FVector4F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector4FTests, SetY_UpdatesValueOfY)
    {
        float expectedY = 98.4f;
        FVector4F testCase = FVector4F();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector4FTests, SetZ_UpdatesValueOfZ)
    {
        float expectedY = 25.1f;
        FVector4F testCase = FVector4F();
        ASSERT_NE(expectedY, testCase.GetZ()) << "Z should not equal expected on construction. ";

        testCase.SetZ(expectedY);

        ASSERT_EQ(expectedY, testCase.GetZ());
    }

    TEST_F(FVector4FTests, SetW_UpdatesValueOfW)
    {
        float expectedW = 13.1f;
        FVector4F testCase = FVector4F();
        ASSERT_NE(expectedW, testCase.GetW()) << "W should not equal expected on construction. ";

        testCase.SetW(expectedW);

        ASSERT_EQ(expectedW, testCase.GetW());
    }

    TEST_F(FVector4FTests, SetXY_UpdatesXYValues_WhenGivendoubleValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        float expectedZ = 0;

        FVector4F testCase = FVector4F();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector4FTests, SetXYZ_UpdatesXYZValues_WhenGivendoubleValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        float expectedZ = 12.5f;

        FVector4F testCase = FVector4F();
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

    TEST_F(FVector4FTests, SetXYZW_UpdatesXYZWValues_WhenGivendoubleValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;
        float expectedZ = 12.5f;
        float expectedW = 34.1f;

        FVector4F testCase = FVector4F();
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
    TEST_F(FVector4FTests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4F expected = FVector4F(2, 1, 5, 1);
        FVector4F left = FVector4F(1, 1, 2, 1);
        FVector4F right = FVector4F(1, 0, 3, 0);

        FVector4F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4F expected = FVector4F(1, 2, 5, 1);
        FVector4F left = FVector4F(1, 1, 2, 1);
        FVector4F right = FVector4F(0, 1, 3, 0);

        FVector4F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4F expected = FVector4F(1, 1, 4, 1);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(0, 0, 3, 0);

        FVector4F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, AddOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4F expected = FVector4F(1, 1, 1, 5);
        FVector4F left = FVector4F(1, 1, 1, 2);
        FVector4F right = FVector4F(0, 0, 0, 3);

        FVector4F actual = left + right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator+=
    TEST_F(FVector4FTests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4F expected = FVector4F(2, 1, 5, 1);
        FVector4F left = FVector4F(1, 1, 2, 1);
        FVector4F right = FVector4F(1, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4F expected = FVector4F(1, 2, 5, 1);
        FVector4F left = FVector4F(1, 1, 2, 1);
        FVector4F right = FVector4F(0, 1, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4F expected = FVector4F(1, 1, 4, 1);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(0, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, AddEqualsOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4F expected = FVector4F(1, 1, 1, 5);
        FVector4F left = FVector4F(1, 1, 1, 2);
        FVector4F right = FVector4F(0, 0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector4FTests, SubtractOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4F expected = FVector4F(1, 0, 0, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(0, 1, 1, 1);

        FVector4F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, SubtractOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4F expected = FVector4F(0, 1, 0, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 0, 1, 1);

        FVector4F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, SubtractOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4F expected = FVector4F(0, 0, 1, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 0, 1);

        FVector4F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, SubtractOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4F expected = FVector4F(0, 0, 0, 1);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 0);

        FVector4F actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector4FTests, SubtractEqualsOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4F expected = FVector4F(0, 1, 0, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, SubtractEqualsOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4F expected = FVector4F(1, 0, 0, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(0, 1, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, SubtractEqualsOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4F expected = FVector4F(0, 0, 1, 0);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4FTests, SubtractEqualsOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4F expected = FVector4F(0, 0, 0, 1);
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector4FTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4F expected = FVector4F(2, 2, 2, 2);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 2;

        FVector4F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4F expected = FVector4F(-2, -2, -2, -2);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = -2;

        FVector4F actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector4FTests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4F expected = FVector4F(2, 2, 2, 2);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4FTests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4F expected = FVector4F(-2, -2, -2, -2);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector4FTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4F expected = FVector4F(0.5f, 0.5f, 0.5f, 0.5f);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 2;

        FVector4F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4F expected = FVector4F(0.1f, 0.1f, 0.1f, 0.1f);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 10;

        FVector4F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4F expected = FVector4F(-0.5f, -0.5f, -0.5f, -0.5f);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = -2;

        FVector4F actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector4FTests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4F expected = FVector4F(0.5f, 0.5f, 0.5f, 0.5f);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4FTests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4F expected = FVector4F(0.1f, 0.1f, 0.1f, 0.1f);
        FVector4F given = FVector4F(1, 1, 1, 1);
        float scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4FTests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4F expected = FVector4F(-0.5f, -0.5f, -0.5f, -0.5f);
        FVector4F given = FVector4F(1, 1, 1, 1);
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
    TEST_F(FVector4FTests, Normalize_DividesPositionByMagnitude)
    {
        FVector4F given = FVector4F(2, 2, 2, 2);
        float magnitude = given.Magnitude();
        FVector4F expected = given / magnitude;

        FVector4F actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector4FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 + 2 * 2 + 2 * 2 = 16
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        float expected = 4;
        FVector4F given = FVector4F(2, 2, 2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector4FTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 + 4 * 4 = 126 
        // then sq(126) = 11.22497 (the epsilon rounds this to 5dp)
        float expected = 11.22497f;
        FVector4F given = FVector4F(2, -5, -9, 4);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector4FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe1stPlace)
    {
        FVector4F left = FVector4F(1.1f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector4F left = FVector4F(1.01f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector4F left = FVector4F(1.001f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector4F left = FVector4F(1.0001f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector4F left = FVector4F(1.00001f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4FTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector4F left = FVector4F(1.000001f, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector4FTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8 = 70
        float expected = 70;
        FVector4F left = FVector4F(1, 2, 3, 4);
        FVector4F right = FVector4F(5, 6, 7, 8);

        float actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector4FTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector4F left = FVector4F(1, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        FVector4F left = FVector4F(2, 1, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        FVector4F left = FVector4F(1, 2, 1, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        float expected = 1;
        FVector4F left = FVector4F(1, 1, 2, 1);
        FVector4F right = FVector4F(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, Distance_Returns1_WhenGivenIsOneAwayOnW)
    {
        float expected = 1;
        FVector4F left = FVector4F(1, 1, 1, 2);
        FVector4F right = FVector4F(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4FTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8, 9, 10, 11, 12);
        FVector4F left = FVector4F(5, 6, 7, 8);
        FVector4F right = FVector4F(9, 10, 11, 12);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}