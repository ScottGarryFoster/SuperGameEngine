#include "../LibraryIncludes.h"
#include "../../StandardCLibrary/Structural/FVector2D.h"
#include <cmath>

using namespace StandardCLibrary;

namespace StandardCLibraryTests_Structural
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

        float Distance(float x1, float y1, float x2, float y2) const
        {
            return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
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
        float givenX = 42.2f;
        float givenY = 12.5f;

        FVector2D testCase = FVector2D(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenNegativeValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;

        FVector2D testCase = FVector2D(givenX, givenY);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenVectorWithValues)
    {
        float givenX = -54.9f;
        float givenY = -21.9f;
        FVector2D givenVector = FVector2D(givenX, givenY);

        FVector2D testCase = FVector2D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

    TEST_F(FVector2DTests, OnConstruction_XYReturnsGivenValues_WhenGivenPointWithValues)
    {
        float givenX = 57;
        float givenY = 20;
        FPoint givenVector = FPoint(givenX, givenY);

        FVector2D testCase = FVector2D(givenVector);

        ASSERT_EQ(givenX, testCase.GetX());
        ASSERT_EQ(givenY, testCase.GetY());
    }

#pragma endregion

#pragma region SetXY
    TEST_F(FVector2DTests, SetX_UpdatesValueOfX)
    {
        float expectedX = 23.5f;
        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedX, testCase.GetX()) << "X should not equal expected on construction. ";

        testCase.SetX(expectedX);

        ASSERT_EQ(expectedX, testCase.GetX());
    }

    TEST_F(FVector2DTests, SetY_UpdatesValueOfY)
    {
        float expectedY = 98.4f;
        FVector2D testCase = FVector2D();
        ASSERT_NE(expectedY, testCase.GetY()) << "Y should not equal expected on construction. ";

        testCase.SetY(expectedY);

        ASSERT_EQ(expectedY, testCase.GetY());
    }

    TEST_F(FVector2DTests, SetXY_UpdatesXYValues_WhenGivenFloatValues)
    {
        // Arrange
        float expectedX = 14.5f;
        float expectedY = 98.4f;

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
        float expectedX = 14.5f;
        float expectedY = 98.4f;
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

#pragma region Operator-
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

#pragma region Operator*
    TEST_F(FVector2DTests, MultiplyOperator_DoublesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(2, 2);
        FVector2D given = FVector2D(1, 1);
        float scalar = 2;

        FVector2D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, MultiplyOperator_ChangesPositivityOfVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-2, -2);
        FVector2D given = FVector2D(1, 1);
        float scalar = -2;

        FVector2D actual = given * scalar;

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Operator/
    TEST_F(FVector2DTests, DivideOperator_HalvesVector_WhenGivenScalarOf2)
    {
        FVector2D expected = FVector2D(0.5f, 0.5f);
        FVector2D given = FVector2D(1, 1);
        float scalar = 2;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, DivideOperator_ReturnsATenth_WhenGivenScalarOf10)
    {
        FVector2D expected = FVector2D(0.1f, 0.1f);
        FVector2D given = FVector2D(1, 1);
        float scalar = 10;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, DivideOperator_FlipsVector_WhenGivenScalarOfMinus2)
    {
        FVector2D expected = FVector2D(-0.5f, -0.5f);
        FVector2D given = FVector2D(1, 1);
        float scalar = -2;

        FVector2D actual = given / scalar;

        ASSERT_EQ(expected, actual);
    }
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
        float magnitude = given.Magnitude();
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
        float expected = 2.82843f;
        FVector2D given = FVector2D(2, 2);

        float actual = given.Magnitude();

        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expected, actual))
            << "expected: " << expected << " actual: " << actual;
    }

    TEST_F(FVector2DTests, Magnitude_CalculatesMagnitudeFromZero_WhenXYAreDifferent)
    {
        // The expected Magnitude will be: 2 * 2 + -5 * -5 = 29 
        // then sq(29) = 5.38516 (the eplision rounds this to 5dp)
        float expected = 5.38516f;
        FVector2D given = FVector2D(2, -5);

        float actual = given.Magnitude();

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
        FVector2D left = FVector2D(1.1f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe2ndPlace)
    {
        FVector2D left = FVector2D(1.01f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe3thPlace)
    {
        FVector2D left = FVector2D(1.001f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe4thPlace)
    {
        FVector2D left = FVector2D(1.0001f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsFalse_WhenTwoValuesAreOnlyUnequalAtThe5thPlace)
    {
        FVector2D left = FVector2D(1.00001f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_FALSE(left == right);
    }

    TEST_F(FVector2DTests, EqualsOperator_ReturnsTrue_WhenTwoValuesAreOnlyUnequalAtThe6thPlace)
    {
        FVector2D left = FVector2D(1.000001f, 1);
        FVector2D right = FVector2D(1, 1);

        bool actual = left == right;

        ASSERT_TRUE(left == right);
    }
#pragma endregion

#pragma region DotProduct
    TEST_F(FVector2DTests, DotProduct_ReturnsDotProductOfVector)
    {
        // 1 * 3 + 2 * 4 = 3 + 8 = 11
        float expected = 11;
        FVector2D left = FVector2D(1, 2);
        FVector2D right = FVector2D(3, 4);

        float actual = left.DotProduct(right);

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Distance

    TEST_F(FVector2DTests, Distance_ReturnsZero_WhenTwoValuesEqual)
    {
        FVector2D left = FVector2D(1, 1);
        FVector2D right = FVector2D(1, 1);
        float expected = 0;

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_Returns1_WhenGivenIsOneAwayOnX)
    {
        float expected = 1;
        FVector2D left = FVector2D(2, 1);
        FVector2D right = FVector2D(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_Returns1_WhenGivenIsOneAwayOnY)
    {
        float expected = 1;
        FVector2D left = FVector2D(1, 2);
        FVector2D right = FVector2D(1, 1);

        float actual = left.DistanceBetween(right);

        ASSERT_EQ(expected, actual);
    }

    TEST_F(FVector2DTests, Distance_ReturnsCorrectValue_WhenGivenTwoPoints)
    {
        float expected = Distance(5, 6, 7, 8);
        FVector2D left = FVector2D(5, 6);
        FVector2D right = FVector2D(7, 8);

        float actual = left.DistanceBetween(right);

        // This should be fine to compare.
        // If flakey use the float helper compare.
        ASSERT_EQ(expected, actual);
    }

#pragma endregion


}