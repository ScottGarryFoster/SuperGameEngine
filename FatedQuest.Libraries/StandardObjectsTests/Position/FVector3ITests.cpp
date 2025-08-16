#include "../../StandardObjects//AllReferences.h"
#include "../../StandardOperations/AllReferences.h"
#include <gtest/gtest.h>

#include <cmath>

using namespace FatedQuestLibraries;

namespace StandardObjectsTests
{
    class FVector3ITests : public ::testing::Test
    {
    public:
        FVector3ITests()
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
    TEST_F(FVector3ITests, OnConstruction_XYZReturnZero_WhenNothingIsPassedIn)
    {
        FVector3I testCase = FVector3I();

        ASSERT_EQ(0, testCase.GetX());
        ASSERT_EQ(0, testCase.GetY());
        ASSERT_EQ(0, testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstruction_XYZReturnsGivenValues_WhenGivenAtConstruction)
    {
        int givenX = 42;
        int givenY = 12;
        int givenZ = 19;

        FVector3I testCase = FVector3I(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstruction_XYZReturnsGivenValues_WhenGivenNegativeValues)
    {
        int givenX = -54;
        int givenY = -21;
        int givenZ = -1;

        FVector3I testCase = FVector3I(givenX, givenY, givenZ);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstruction_XYZReturnsGivenValues_WhenGivenVectorWithValues)
    {
        int givenX = -54;
        int givenY = -21;
        int givenZ = -15;
        FVector3I givenVector = FVector3I(givenX, givenY, givenZ);

        FVector3I testCase = FVector3I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(givenZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstruction_XYZReturnsGivenValues_WhenGivenPointWithValues)
    {
        int givenX = 57;
        int givenY = 20;
        int expectedZ = 0;
        FPoint givenVector = FPoint(givenX, givenY);

        FVector3I testCase = FVector3I(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Double

    TEST_F(FVector3ITests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3D(1.5, 2.3, 3.9);
        auto expected = FVector3I(1, 2, 3);

        auto testCase = FVector3I(given);

        ASSERT_EQ(expected.GetX(), testCase.GetX());
        ASSERT_EQ(expected.GetY(), testCase.GetY());
        ASSERT_EQ(expected.GetZ(), testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstructionWithFVector3I_CopiesXYZValues_WhenGivenNegatives)
    {
        auto given = FVector3D(-5.5, -7.1, -10.6);
        auto expected = FVector3I(-5, -7, -10);

        auto testCase = FVector3I(given);

        ASSERT_EQ(expected.GetX(), testCase.GetX());
        ASSERT_EQ(expected.GetY(), testCase.GetY());
        ASSERT_EQ(expected.GetZ(), testCase.GetZ());
    }

#pragma endregion

#pragma region Constructor From Float

    TEST_F(FVector3ITests, OnConstructionWithFVector3F_CopiesXYZValues_WhenGivenPositives)
    {
        auto given = FVector3F(1.5f, 9.5f, 15.6f);
        int expectedX = 1;
        int expectedY = 9;
        int expectedZ = 15;

        auto testCase = FVector3I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, OnConstructionWithFVector2F_CopiesXYValues_WhenGivenNegatives)
    {
        auto given = FVector3F(-5.3f, -7.9f, -6.2f);
        double expectedX = -5;
        double expectedY = -7;
        double expectedZ = -6;

        auto testCase = FVector3I(given);

        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector3ITests, SetX_UpdatesValueOfX)
    {
        int expectedX = 23;
        FVector3I testCase = FVector3I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector3ITests, SetY_UpdatesValueOfY)
    {
        int expectedY = 98;
        FVector3I testCase = FVector3I();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector3ITests, SetXY_UpdatesXYValues_WhenGivenTwoValues)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        int expectedZ = 0;

        FVector3I testCase = FVector3I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(expectedX, expectedY);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, SetXY_UpdatesXYValues_WhenGivenVectorValue)
    {
        // Arrange
        int expectedX = 14;
        int expectedY = 98;
        int expectedZ = 0;
        FVector3I given = FVector3I(expectedX, expectedY, expectedZ);

        FVector3I testCase = FVector3I();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        // Act
        testCase.SetXYValue(given);

        // Assert
        ASSERT_EQ(expectedX, testCase.GetX());
        ASSERT_EQ(expectedY, testCase.GetY());
        ASSERT_EQ(expectedZ, testCase.GetZ());
    }

    TEST_F(FVector3ITests, SetXY_UpdatesXYValues_WhenGivenPointValue)
    {
        // Arrange
        int expectedX = 16;
        int expectedY = 91;
        int expectedZ = 0;
        FPoint given = FPoint(expectedX, expectedY);

        FVector3I testCase = FVector3I();
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
    TEST_F(FVector3ITests, AddOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3I expected = FVector3I(2, 1, 5);
        FVector3I left = FVector3I(1, 1, 2);
        FVector3I right = FVector3I(1, 0, 3);

        FVector3I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, AddOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3I expected = FVector3I(1, 2, 5);
        FVector3I left = FVector3I(1, 1, 2);
        FVector3I right = FVector3I(0, 1, 3);

        FVector3I actual = left + right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, AddOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3I expected = FVector3I(1, 1, 4);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(0, 0, 3);

        FVector3I actual = left + right;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion
#pragma region Operator+=
    TEST_F(FVector3ITests, AddEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3I expected = FVector3I(2, 1, 5);
        FVector3I left = FVector3I(1, 1, 2);
        FVector3I right = FVector3I(1, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3ITests, AddEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3I expected = FVector3I(1, 2, 5);
        FVector3I left = FVector3I(1, 1, 2);
        FVector3I right = FVector3I(0, 1, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3ITests, AddEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3I expected = FVector3I(1, 1, 4);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(0, 0, 3);

        left += right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator-
#pragma region Operator- As new Vector
    TEST_F(FVector3ITests, SubtractOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3I expected = FVector3I(1, 0, 0);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(0, 1, 1);

        FVector3I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, SubtractOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3I expected = FVector3I(0, 1, 0);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 0, 1);

        FVector3I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, SubtractOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3I expected = FVector3I(0, 0, 1);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 1, 0);

        FVector3I actual = left - right;

        ASSERT_EQ(expected, actual);
    }

#pragma endregion
#pragma region Operator-=
    TEST_F(FVector3ITests, SubtractEqualsOperator_ReturnsXAdd_WhenSecondXHasValue)
    {
        FVector3I expected = FVector3I(0, 1, 0);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 0, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3ITests, SubtractEqualsOperator_ReturnsYAdd_WhenSecondYHasValue)
    {
        FVector3I expected = FVector3I(1, 0, 0);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(0, 1, 1);

        left -= right;

        ASSERT_EQ(expected, left);
    }

    TEST_F(FVector3ITests, SubtractEqualsOperator_ReturnsZAdd_WhenSecondZHasValue)
    {
        FVector3I expected = FVector3I(0, 0, 1);
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 1, 0);

        left -= right;

        ASSERT_EQ(expected, left);
    }

#pragma endregion
#pragma endregion

#pragma region Operator*
#pragma region Operator* As new Vector
    TEST_F(FVector3ITests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector3I expected = FVector3I(2, 2, 2);
        FVector3I given = FVector3I(1, 1, 1);
        int scalar = 2;

        FVector3I actual = given * scalar;

        ASSERT_EQ(expected, actual) << "Expected: " << expected.Print() << " Actual: " << actual.Print();
    }

    TEST_F(FVector3ITests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3I expected = FVector3I(-2, -2, -2);
        FVector3I given = FVector3I(1, 1, 1);
        int scalar = -2;

        FVector3I actual = given * scalar;

        ASSERT_EQ(expected, actual) << "Expected: " << expected.Print() << " Actual: " << actual.Print();
    }
#pragma endregion
#pragma region Operator*=
    TEST_F(FVector3ITests, MultiplyEqualsOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector3I expected = FVector3I(2, 2, 2);
        FVector3I given = FVector3I(1, 1, 1);
        int scalar = 2;

        given *= scalar;

        ASSERT_EQ(expected, given) << "Expected: " << expected.Print() << " Given: " << given.Print();
    }

    TEST_F(FVector3ITests, MultiplyEqualsOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector3I expected = FVector3I(-2, -2, -2);
        FVector3I given = FVector3I(1, 1, 1);
        int scalar = -2;

        given *= scalar;

        ASSERT_EQ(expected, given) << "Expected: " << expected.Print() << " Given: " << given.Print();
    }
#pragma endregion
#pragma endregion

#pragma region Operator/
#pragma region Operator/ As new Vector
    TEST_F(FVector3ITests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3I expected = FVector3I(2, 2, 2);
        FVector3I given = FVector3I(4, 4, 4);
        int scalar = 2;

        FVector3I actual = given / scalar;

        ASSERT_EQ(expected, actual) << "Expected: " << expected.Print() << " Actual: " << actual.Print();
    }

    TEST_F(FVector3ITests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3I expected = FVector3I(1, 1, 1);
        FVector3I given = FVector3I(10, 10, 10);
        int scalar = 10;

        FVector3I actual = given / scalar;

        ASSERT_EQ(expected, actual) << "Expected: " << expected.Print() << " Actual: " << actual.Print();
    }

    TEST_F(FVector3ITests, DivideOperator_HalvesAndFlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3I expected = FVector3I(-1, -1, -1);
        FVector3I given = FVector3I(2, 2, 2);
        int scalar = -2;

        FVector3I actual = given / scalar;

        ASSERT_EQ(expected, actual) << "Expected: " << expected.Print() << " Actual: " << actual.Print();
    }
#pragma endregion
#pragma region Operator/=
    TEST_F(FVector3ITests, DivideEqualsOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector3I expected = FVector3I(2, 2, 2);
        FVector3I given = FVector3I(4, 4, 4);
        int scalar = 2;

        given /= scalar;

        ASSERT_EQ(expected, given) << "Expected: " << expected.Print() << " Given: " << given.Print();
    }

    TEST_F(FVector3ITests, DivideEqualsOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector3I expected = FVector3I(1, 1, 1);
        FVector3I given = FVector3I(10, 10, 10);
        int scalar = 10;

        given /= scalar;

        ASSERT_EQ(expected, given) << "Expected: " << expected.Print() << " Given: " << given.Print();
    }

    TEST_F(FVector3ITests, DivideEqualsOperator_HalvesAndFlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector3I expected = FVector3I(-1, -1, -1);
        FVector3I given = FVector3I(2, 2, 2);
        int scalar = -2;

        given /= scalar;

        ASSERT_EQ(expected, given) << "Expected: " << expected.Print() << " Given: " << given.Print();
    }
#pragma endregion
#pragma endregion

#pragma region Normalize
    /// <remark>
    /// These are none perfect tests because they replicate what the 
    /// implementation does but the operation is simple and mathematical
    /// so there is not a much better way of doing it.
    /// </remark>
    TEST_F(FVector3ITests, Normalize_DividesPositionByMagnitude)
    {
        FVector3I given = FVector3I(2, 2, 2);
        float magnitude = given.Magnitude();
        FVector3I expected = given / static_cast<int>(magnitude);

        FVector3I actual = given.Normalize();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Magnitude
    TEST_F(FVector3ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreTheSame)
    {
        // The expected Magnitude will be: 2 * 2 + 2 * 2+ 2 * 2 = 12
        // then sq(12) = 3.46410f (the epsilon rounds this to 5dp)
        float expected = 3.46410f;
        FVector3I given = FVector3I(2, 2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector3ITests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 + -9 * -9 = 110 
        // then sq(110) = 10.48809 (the epsilon rounds this to 5dp)
        float expected = 10.48809f;
        FVector3I given = FVector3I(2, -5, -9);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }
#pragma endregion

#pragma region Operator==
    TEST_F(FVector3ITests, EqualsOperator_ReturnsTrue_WhenBothVectorsAreEqual)
    {
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }

    TEST_F(FVector3ITests, EqualsOperator_ReturnsFalse_WhenBothVectorsAreNotEqualOnX)
    {
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(2, 1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3ITests, EqualsOperator_ReturnsFalse_WhenBothVectorsAreNotEqualOnY)
    {
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 2, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector3ITests, EqualsOperator_ReturnsFalse_WhenBothVectorsAreNotEqualOnZ)
    {
        FVector3I left = FVector3I(1, 1, 1);
        FVector3I right = FVector3I(1, 1, 2);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

#pragma endregion

#pragma region DotProduct
    TEST_F(FVector3ITests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 4 + 2 * 5 + 3 * 6 = 32
        int expected = 32;
        auto left = FVector3I(1, 2, 3);
        auto right = FVector3I(4, 5, 6);

        double actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector3ITests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        auto left = FVector3I(1, 1, 1);
        auto right = FVector3I(1, 1, 1);
        double expected = 0;

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        double expected = 1;
        auto left = FVector3I(2, 1, 1);
        auto right = FVector3I(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        double expected = 1;
        auto left = FVector3I(1, 2, 1);
        auto right = FVector3I(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, Distance_Returns1_WhenGivenIsOneAwayOnZ)
    {
        double expected = 1;
        auto left = FVector3I(1, 1, 2);
        auto right = FVector3I(1, 1, 1);

        double actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector3ITests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        double expected = Distance(5, 6, 7, 8, 9, 10);
        auto left = FVector3I(5, 6, 7);
        auto right = FVector3I(8, 9, 10);

        double actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flaky use the double helper compare.
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

#pragma endregion


}