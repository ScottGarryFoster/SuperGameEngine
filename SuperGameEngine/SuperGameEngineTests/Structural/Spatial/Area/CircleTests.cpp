#include "../../../LibraryIncludes.h"
#include "../../../../SuperGameEngine/Structural/Spatial/Area/Circle.h"
#include "../../../../SuperGameEngine/Structural/Spatial/Area/Rectangle.h"

using namespace SuperGameEngine;
namespace SuperGameEngineTests_Structural_Spatial_Area
{
    class CircleTests : public ::testing::Test
    {
    public:
        CircleTests()
        {
            m_testCircle = nullptr;
            m_otherTestCircle = nullptr;
            m_testRectangle = nullptr;
            m_otherTestRectangle = nullptr;
        }

    protected:

        Circle* m_testCircle;
        Circle* m_otherTestCircle;

        Rectangle* m_testRectangle;
        Rectangle* m_otherTestRectangle;

        void SetUp() override
        {

        }

        void TearDown() override
        {
            if (m_testCircle != nullptr)
            {
                delete m_testCircle;
            }
            
            if (m_otherTestCircle != nullptr)
            {
                delete m_otherTestCircle;
            }

            if (m_testRectangle != nullptr)
            {
                delete m_testRectangle;
            }

            if (m_otherTestRectangle != nullptr)
            {
                delete m_otherTestRectangle;
            }
        }

        /// <summary>
        /// Creates a basic rectangle for testing.
        /// </summary>
        /// <returns>A Unit 1 by 1 rectangle at (1, 1). </returns>
        Rectangle* CreateBasicRectangle()
        {
            float originalXY = 1;
            float originalWidthHeight = 1;
            return new Rectangle(originalXY, originalWidthHeight);
        }

        /// <summary>
        /// Creates a basic circle for testing.
        /// </summary>
        /// <returns>A Unit 1 by 1 circle at (1, 1). </returns>
        Circle* CreateBasicCircle()
        {
            float originalXY = 1;
            int validRadius = 1;
            return new Circle(originalXY, originalXY, validRadius);
        }
    };

#pragma region Construction
    TEST_F(CircleTests, OnContruction_ReturnsGivenLocation_WhenGivenAsXY)
    {
        float givenX = 6;
        float givenY = 10;
        int validRadius = 5;

        m_testCircle = new Circle(givenX, givenY, validRadius);

        ASSERT_EQ(givenX, m_testCircle->GetLocation().GetX());
        ASSERT_EQ(givenY, m_testCircle->GetLocation().GetY());
    }

    TEST_F(CircleTests, OnContruction_ReturnsRadius_WhenGivenValidRadius)
    {
        float givenX = 6;
        float givenY = 10;
        int validRadius = 5;

        m_testCircle = new Circle(givenX, givenY, validRadius);

        ASSERT_EQ(validRadius, m_testCircle->GetRadius());
    }

    TEST_F(CircleTests, OnContruction_ReturnsRadius_WhenJustGivenValidRadius)
    {
        int validRadius = 50;

        m_testCircle = new Circle(validRadius);

        ASSERT_EQ(validRadius, m_testCircle->GetRadius());
    }

    TEST_F(CircleTests, OnContruction_Returns00Location_WhenJustGivenRadius)
    {
        float expectedXY = 0;
        int validRadius = 5;

        m_testCircle = new Circle(validRadius);

        ASSERT_EQ(expectedXY, m_testCircle->GetLocation().GetX());
        ASSERT_EQ(expectedXY, m_testCircle->GetLocation().GetY());
    }

    TEST_F(CircleTests, OnContruction_ReturnsRadiusAsZero_WhenGivenRadiusBelow0)
    {
        float validXY = 0;
        int invalidRadius = -1;
        int expectedRadius = 0;

        m_testCircle = new Circle(validXY, validXY, invalidRadius);
        m_otherTestCircle = new Circle(invalidRadius);

        ASSERT_EQ(expectedRadius, m_testCircle->GetRadius());
        ASSERT_EQ(expectedRadius, m_otherTestCircle->GetRadius());
    }
#pragma endregion

#pragma region SetLocation
    TEST_F(CircleTests, SetGetLocation_UpdatesLocation_WhenNewLocationSet)
    {
        m_testCircle = CreateBasicCircle();
        FVector2D givenLocation = FVector2D(6, 10);
        int validRadius = 5;

        m_testCircle->SetLocation(givenLocation);
        FVector2D actual = m_testCircle->GetLocation();

        ASSERT_EQ(givenLocation.GetX(), actual.GetX());
        ASSERT_EQ(givenLocation.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region SetRadius
    TEST_F(CircleTests, SetGetRadius_UpdatesRadius_WhenGivenValidRadius)
    {
        m_testCircle = CreateBasicCircle();
        int givenRadius = 5;

        m_testCircle->SetRadius(givenRadius);
        int actual = m_testCircle->GetRadius();

        ASSERT_EQ(givenRadius, actual);
    }

    TEST_F(CircleTests, SetGetRadius_UpdatesRadiusAsZero_WhenRadiusSetToNegativeNumber)
    {
        m_testCircle = CreateBasicCircle();
        ASSERT_TRUE(m_testCircle->GetRadius() > 0) << "Radius must begin bigger than zero for this test.";
        int givenRadius = -1;
        int expected = 0;

        m_testCircle->SetRadius(givenRadius);
        int actual = m_testCircle->GetRadius();

        ASSERT_EQ(expected, actual);
    }
#pragma endregion

#pragma region Overlaps Circle
    TEST_F(CircleTests, Overlaps_ReturnsFalse_WhenTwoCirclesAreFarApart)
    {
        // Arrange
        FVector2D givenFirstLocation = FVector2D(10, 10);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);

        // Act
        bool actual = m_testCircle->Overlaps(*m_otherTestCircle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(CircleTests, Overlaps_ReturnsTrue_WhenCirclesOverlapOnTheX)
    {
        // Arrange
        int radius = 1;
        float touchingX = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(touchingX, 0);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->Overlaps(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, Overlaps_ReturnsTrue_WhenCirclesOverlapOnTheY)
    {
        // Arrange
        int radius = 1;
        float touchingY = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(0, touchingY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->Overlaps(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, Overlaps_ReturnsTrue_WhenCirclesOverlapOnBothXAndY)
    {
        // Arrange
        int radius = 1;
        float touchingXY = radius + radius - 0.6f;

        FVector2D givenFirstLocation = FVector2D(touchingXY, touchingXY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->Overlaps(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapsOrTouching Circle
    TEST_F(CircleTests, OverlapsOrTouches_ReturnsFalse_WhenTwoCirclesAreFarApart)
    {
        // Arrange
        FVector2D givenFirstLocation = FVector2D(10, 10);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(CircleTests, OverlapsOrTouches_ReturnsTrue_WhenCirclesOverlapOnTheX)
    {
        // Arrange
        int radius = 1;
        float touchingX = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(touchingX, 0);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsOrTouches_ReturnsTrue_WhenCirclesTouchOnTheX)
    {
        // Arrange
        int radius = 1;
        float touchingX = radius + radius;

        FVector2D givenFirstLocation = FVector2D(touchingX, 0);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsOrTouches_ReturnsTrue_WhenCirclesOverlapOnTheY)
    {
        // Arrange
        int radius = 1;
        float touchingY = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(0, touchingY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsOrTouches_ReturnsTrue_WhenCirclesTouchesOnTheY)
    {
        // Arrange
        int radius = 1;
        float touchingY = radius + radius;

        FVector2D givenFirstLocation = FVector2D(0, touchingY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsOrTouches_ReturnsTrue_WhenCirclesOverlapOnBothXAndY)
    {
        // Arrange
        int radius = 1;
        float touchingXY = radius + radius - 0.6f;

        FVector2D givenFirstLocation = FVector2D(touchingXY, touchingXY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_otherTestCircle = CreateBasicCircle();
        m_otherTestCircle->SetLocation(givenSecondLocation);
        m_otherTestCircle->SetRadius(radius);

        // Act
        bool actual = m_testCircle->OverlapsOrTouches(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region Overlaps Rectangle
    TEST_F(CircleTests, OverlapsRectangle_ReturnsFalse_WhenExtentsOfRectangleAreNotWithinCircle)
    {
        // Arrange
        FVector2D givenFirstLocation = FVector2D(10, 10);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testCircle->Overlaps(*m_testRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(CircleTests, OverlapsRectangle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheX)
    {
        // Arrange
        int radius = 1;
        float touchingX = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(touchingX, 0);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testCircle->Overlaps(*m_testRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsRectangle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheY)
    {
        // Arrange
        int radius = 1;
        float touchingY = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(0, touchingY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testCircle->Overlaps(*m_testRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsRectangle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheXAndY)
    {
        // Arrange
        int radius = 1;

        FVector2D givenFirstLocation = FVector2D(0.5f, 0.5f);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(1, 1);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testCircle->Overlaps(*m_testRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, OverlapsRectangle_ReturnsTrue_WhenCircleIsContainedCompletelyInTheRectangle)
    {
        // Arrange
        int radius = 1;

        FVector2D givenFirstLocation = FVector2D(5, 5);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());
        m_testRectangle->SetSize(10, 10);

        // Act
        bool actual = m_testCircle->Overlaps(*m_testRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region PointIsWithin
    TEST_F(CircleTests, PointIsWithin_ReturnsFalse_WhenPointIsBeyond)
    {
        // Arrange
        FVector2D testLocation = FVector2D(0, 0);
        FVector2D circleLocation = FVector2D(10, 10);
        int givenRadius = 1;
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(circleLocation);
        m_testCircle->SetRadius(givenRadius);

        // Act
        bool actual = m_testCircle->PointIsWithin(testLocation);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(CircleTests, PointIsWithin_ReturnsTrue_WhenPointEqualsCenterOfCircle)
    {
        // Arrange
        FVector2D testLocation = FVector2D(0, 0);
        FVector2D circleLocation = testLocation;
        int givenRadius = 1;
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(circleLocation);
        m_testCircle->SetRadius(givenRadius);

        // Act
        bool actual = m_testCircle->PointIsWithin(testLocation);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(CircleTests, PointIsWithin_ReturnsTrue_WhenPointIsWithinCircle)
    {
        // Arrange
        int givenRadius = 1;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);

        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(circleLocation);
        m_testCircle->SetRadius(givenRadius);

        // Act
        bool actual = m_testCircle->PointIsWithin(testLocation);

        // Assert
        ASSERT_TRUE(actual);
    }

#pragma endregion

#pragma region OverlapAmount
    TEST_F(CircleTests, OverlapAmount_ReturnsCorrectOverlap_WhenYIsTheSame)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the first circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the second circle
        // Meaning we would expect an overlap of 7.5f (/ means half)

        // Arrange
        float expectedOverlap = 7.5f;
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(2.5f, 5);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        float actual = m_testCircle->OverlapAmount(*m_otherTestCircle);

        // Assert
        ASSERT_EQ(expectedOverlap, actual);
    }

    TEST_F(CircleTests, OverlapAmount_ReturnsCorrectOverlap_WhenXIsTheSame)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the first circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the second circle
        // Meaning we would expect an overlap of 7.5f (/ means half)
        
        // Arrange
        float expectedOverlap = 7.5f;
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(5, 2.5f);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        float actual = m_testCircle->OverlapAmount(*m_otherTestCircle);

        // Assert
        ASSERT_EQ(expectedOverlap, actual);
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap
    TEST_F(CircleTests, GetNewLocationToNotOverlap_MovesToTheRight_WhenRightIsClosest)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the first circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the second circle
        // Meaning we would expect an overlap of 7.5f (/ means half)
        // We would expect it to move left and be at an X of 12.5.

        // Arrange
        FVector2D expectedFinalLocation = FVector2D(12.5f, 5);
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(2.5f, 5);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        FVector2D actual = m_testCircle->GetNewLocationToNotOverlap(*m_otherTestCircle);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetX(), actual.GetX()));
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetY(), actual.GetY()));
    }

    TEST_F(CircleTests, GetNewLocationToNotOverlap_MovesToTheLeft_WhenLeftIsClosest)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the second circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the first circle
        // Meaning we would expect an overlap of 7.5f (/ means half)
        // We would expect it to move left and be at an X of -5
        // (we flip circles from previous test)

        // Arrange
        FVector2D expectedFinalLocation = FVector2D(-5, 5);
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(2.5f, 5);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        FVector2D actual = m_otherTestCircle->GetNewLocationToNotOverlap(*m_testCircle);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetX(), actual.GetX()));
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetY(), actual.GetY()));
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf
    TEST_F(CircleTests, MoveOutOfOverlapRangeOf_MovesToTheRight_WhenRightIsClosest)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the first circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the second circle
        // Meaning we would expect an overlap of 7.5f (/ means half)
        // We would expect it to move left and be at an X of 12.5.

        // Arrange
        FVector2D expectedFinalLocation = FVector2D(12.5f, 5);
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(2.5f, 5);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        m_testCircle->MoveOutOfOverlapRangeOf(*m_otherTestCircle);

        // Assert
        FVector2D actual = m_testCircle->GetLocation();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetX(), actual.GetX()));
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetY(), actual.GetY()));
    }

    TEST_F(CircleTests, MoveOutOfOverlapRangeOf_MovesToTheLeft_WhenLeftIsClosest)
    {
        // Setup
        // 0 1 2 3 4 5 6 7 8 9 10
        // Center of the second circle
        // - - - - - \/ - - - - -
        // O O O O O O O / X X X
        // - - /\ - - - -
        // This is the center of the first circle
        // Meaning we would expect an overlap of 7.5f (/ means half)
        // We would expect it to move left and be at an X of -5
        // (we flip circles from previous test)

        // Arrange
        FVector2D expectedFinalLocation = FVector2D(-5, 5);
        int givenRadius = 5;
        FVector2D circleLocation = FVector2D(5, 5);
        FVector2D testLocation = FVector2D(
            circleLocation.GetX() + 0.1f,
            circleLocation.GetY() + 0.1f);
        FVector2D circleSecondLocation = FVector2D(2.5f, 5);

        m_testCircle = new Circle(
            circleLocation.GetX(), circleLocation.GetY(), givenRadius);
        m_otherTestCircle = new Circle(
            circleSecondLocation.GetX(), circleSecondLocation.GetY(), givenRadius);

        // Act
        m_otherTestCircle->MoveOutOfOverlapRangeOf(*m_testCircle);

        // Assert
        FVector2D actual = m_otherTestCircle->GetLocation();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetX(), actual.GetX()));
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(expectedFinalLocation.GetY(), actual.GetY()));
    }
#pragma endregion
}