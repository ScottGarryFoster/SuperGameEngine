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

        double Distance(float x1, float y1, float x2, float y2) const
        {
            return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        }
    };



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