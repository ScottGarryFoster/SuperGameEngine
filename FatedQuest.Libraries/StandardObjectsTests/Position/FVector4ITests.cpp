#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector4ITests : public ::testing::Test
    {
    public:
        FVector4ITests()
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
    TEST_F(FVector4ITests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector4I testCase = FVector4I();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
        ASSERT_EQ(0, testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstruction_XYZWReturnsGivenValues_WhenGivenAtConstruction)
    {
        int givenX = 42;
        int givenY = 12;
        int givenZ = 19;
        int givenW = 10;

        FVector4I testCase = FVector4I(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstruction_XYZWReturnsGivenValues_WhenGivenNegativeValues)
    {
        int givenX = -54;
        int givenY = -21;
        int givenZ = -1;
        int givenW = -3;

        FVector4I testCase = FVector4I(givenX, givenY, givenZ, givenW);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstruction_XYZWReturnsGivenValues_WhenGivenVectorWithValues)
    {
        int givenX = -54;
        int givenY = -21;
        int givenZ = -15;
        int givenW = -76;
        FVector4I givenVector = FVector4I(givenX, givenY, givenZ, givenW);

        FVector4I testCase = FVector4I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
        ASSERT_EQ(givenW, testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstruction_XYZWReturnsGivenValues_WhenGivenPointWithValues)
    {
        int givenX = 57;
        int givenY = 20;
        int expectedZ = 0;
        int expectedW = 0;
        FPoint givenVector = FPoint(static_cast<int>(givenX), static_cast<int>(givenY));

        FVector4I testCase = FVector4I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Int

    TEST_F(FVector4ITests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4I(1, 2, 3, 4);

        auto testCase = FVector4I(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstructionWithFVector4I_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4I(-5, -7, -10, -8);

        auto testCase = FVector4I(given);

        ASSERT_EQ(given.GetX(), testCase.GetX());
        ASSERT_EQ(given.GetY(), testCase.GetY());
        ASSERT_EQ(given.GetZ(), testCase.GetZ());
        ASSERT_EQ(given.GetW(), testCase.GetW());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector4ITests, OnConstructionWithFVector4D_CopiesXYZWValues_WhenGivenPositives)
    {
        auto given = FVector4D(1.5, 9.5, 15.6, 9.1);
        int expectedX = 1;
        int expectedY = 9;
        int expectedZ = 15;
        int expectedW = 9;

        auto testCase = FVector4I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

    TEST_F(FVector4ITests, OnConstructionWithFVector4D_CopiesXYZWValues_WhenGivenNegatives)
    {
        auto given = FVector4D(-5.3, -7.9, -6.2, -9.1);
        int expectedX = -5;
        int expectedY = -7;
        int expectedZ = -6;
        int expectedW = -9;

        auto testCase = FVector4I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
        ASSERT_EQ(expectedW, testCase.GetW());
    }

#pragma endregion

#pragma region SetXYZW
    TEST_F(FVector4ITests, SetX_UpdatesValueOfX)
    {
        int expectedX = 23;
        FVector4I testCase = FVector4I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector4ITests, SetY_UpdatesValueOfY)
    {
        int expectedY = 98;
        FVector4I testCase = FVector4I();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector4ITests, SetZ_UpdatesValueOfZ)
    {
        int expectedY = 25;
        FVector4I testCase = FVector4I();
        ASSERT_NE(expectedY, testCase.GetZ()) << "Z should not equal expected on construction. ";

        testCase.SetZ(expectedY);

        ASSERT_EQ(expectedY, testCase.GetZ());
    }

    TEST_F(FVector4ITests, SetW_UpdatesValueOfW)
    {
        int expectedW = 13;
        FVector4I testCase = FVector4I();
        ASSERT_NE(expectedW, testCase.GetW()) << "W should not equal expected on construction. ";

        testCase.SetW(expectedW);

        ASSERT_EQ(expectedW, testCase.GetW());
    }

    TEST_F(FVector4ITests, SetXY_UpdatesXYValues_WhenGivendoubleValues)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        int expectedZ = 0;

        FVector4I testCase = FVector4I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector4ITests, SetXYZ_UpdatesXYZValues_WhenGivendoubleValues)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        int expectedZ = 12;

        FVector4I testCase = FVector4I();
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

    TEST_F(FVector4ITests, SetXYZW_UpdatesXYZWValues_WhenGivendoubleValues)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        int expectedZ = 12;
        int expectedW = 34;

        FVector4I testCase = FVector4I();
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
    TEST_F(FVector4ITests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4I expected = FVector4I(2, 1, 5, 1);
        FVector4I left = FVector4I(1, 1, 2, 1);
        FVector4I right = FVector4I(1, 0, 3, 0);

        FVector4I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4I expected = FVector4I(1, 2, 5, 1);
        FVector4I left = FVector4I(1, 1, 2, 1);
        FVector4I right = FVector4I(0, 1, 3, 0);

        FVector4I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4I expected = FVector4I(1, 1, 4, 1);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(0, 0, 3, 0);

        FVector4I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, AddOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4I expected = FVector4I(1, 1, 1, 5);
        FVector4I left = FVector4I(1, 1, 1, 2);
        FVector4I right = FVector4I(0, 0, 0, 3);

        FVector4I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator+=
    TEST_F(FVector4ITests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector4I expected = FVector4I(2, 1, 5, 1);
        FVector4I left = FVector4I(1, 1, 2, 1);
        FVector4I right = FVector4I(1, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector4I expected = FVector4I(1, 2, 5, 1);
        FVector4I left = FVector4I(1, 1, 2, 1);
        FVector4I right = FVector4I(0, 1, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector4I expected = FVector4I(1, 1, 4, 1);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(0, 0, 3, 0);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, AddEqualsOperator_ReturnsWAdd_WhenSecondWHasValue)
    {
        FVector4I expected = FVector4I(1, 1, 1, 5);
        FVector4I left = FVector4I(1, 1, 1, 2);
        FVector4I right = FVector4I(0, 0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector4ITests, SubtractOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4I expected = FVector4I(1, 0, 0, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(0, 1, 1, 1);

        FVector4I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, SubtractOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4I expected = FVector4I(0, 1, 0, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 0, 1, 1);

        FVector4I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, SubtractOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4I expected = FVector4I(0, 0, 1, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 0, 1);

        FVector4I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, SubtractOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4I expected = FVector4I(0, 0, 0, 1);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 0);

        FVector4I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector4ITests, SubtractEqualsOperator_ReturnsXOperation_WhenSecondXHasValue)
    {
        FVector4I expected = FVector4I(0, 1, 0, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, SubtractEqualsOperator_ReturnsYOperation_WhenSecondYHasValue)
    {
        FVector4I expected = FVector4I(1, 0, 0, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(0, 1, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, SubtractEqualsOperator_ReturnsZOperation_WhenSecondZHasValue)
    {
        FVector4I expected = FVector4I(0, 0, 1, 0);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector4ITests, SubtractEqualsOperator_ReturnsWOperation_WhenSecondWHasValue)
    {
        FVector4I expected = FVector4I(0, 0, 0, 1);
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector4ITests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4I expected = FVector4I(2, 2, 2, 2);
        FVector4I given = FVector4I(1, 1, 1, 1);
        int scalar = 2;

        FVector4I actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4I expected = FVector4I(-2, -2, -2, -2);
        FVector4I given = FVector4I(1, 1, 1, 1);
        int scalar = -2;

        FVector4I actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector4ITests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector4I expected = FVector4I(2, 2, 2, 2);
        FVector4I given = FVector4I(1, 1, 1, 1);
        int scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4ITests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector4I expected = FVector4I(-2, -2, -2, -2);
        FVector4I given = FVector4I(1, 1, 1, 1);
        int scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given);
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector4ITests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4I expected = FVector4I(2, 2, 2, 2);
        FVector4I given = FVector4I(4, 4, 4, 4);
        int scalar = 2;

        FVector4I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4I expected = FVector4I(1, 1, 1, 1);
        FVector4I given = FVector4I(10, 10, 10, 10);
        int scalar = 10;

        FVector4I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4I expected = FVector4I(-1, -1, -1, -1);
        FVector4I given = FVector4I(2, 2, 2, 2);
        int scalar = -2;

        FVector4I actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector4ITests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector4I expected = FVector4I(2, 2, 2, 2);
        FVector4I given = FVector4I(4, 4, 4, 4);
        float scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4ITests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector4I expected = FVector4I(1, 1, 1, 1);
        FVector4I given = FVector4I(10, 10, 10, 10);
        int scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given);
    }

    TEST_F(FVector4ITests, DivideEqualsOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector4I expected = FVector4I(-1, -1, -1, -1);
        FVector4I given = FVector4I(2, 2, 2, 2);
        int scalar = -2;

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
    TEST_F(FVector4ITests, Normalize_DividesPositionByMagnitude)
    {
        FVector4I given = FVector4I(2, 2, 2, 2);
        float magnitude = given.Magnitude();
        FVector4I expected = given / static_cast<int>(magnitude);

        FVector4I actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector4ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2 + 2 * 2 + 2 * 2 = 16
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        float expected = 4;
        FVector4I given = FVector4I(2, 2, 2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector4ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 + 4 * 4 = 126 
        // then sq(126) = 11.22497 (the epsilon rounds this to 5dp)
        float expected = 11.22497f;
        FVector4I given = FVector4I(2, -5, -9, 4);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector4ITests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreEqualToZeroPlaces)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector4ITests, EqualsOperator_ReturnsFalse_WhenXDiffers)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(2, 1, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4ITests, EqualsOperator_ReturnsFalse_WhenYDiffers)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 2, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4ITests, EqualsOperator_ReturnsFalse_WhenZDiffers)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 2, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector4ITests, EqualsOperator_ReturnsFalse_WhenWDiffers)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 2);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

#pragma endregion

#pragma region DotProduct
    TEST_F(FVector4ITests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8 = 70
        int expected = 70;
        FVector4I left = FVector4I(1, 2, 3, 4);
        FVector4I right = FVector4I(5, 6, 7, 8);

        int actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector4ITests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector4I left = FVector4I(1, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        FVector4I left = FVector4I(2, 1, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        FVector4I left = FVector4I(1, 2, 1, 1);
        FVector4I right = FVector4I(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        float expected = 1;
        FVector4I left = FVector4I(1, 1, 2, 1);
        FVector4I right = FVector4I(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, Distance_Returns1_WhenGivenIsOneAwayOnW)
    {
        float expected = 1;
        FVector4I left = FVector4I(1, 1, 1, 2);
        FVector4I right = FVector4I(1, 1, 1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector4ITests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8, 9, 10, 11, 12);
        FVector4I left = FVector4I(5, 6, 7, 8);
        FVector4I right = FVector4I(9, 10, 11, 12);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}