#include "../LibraryIncludes.h"
#include "../../StandardCLibrary/Structural/FVector2D.h"

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
}