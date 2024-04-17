#include "../../../LibraryIncludes.h"
#include "../../../../SuperGameEngine/Structural/Spatial/Area/Rectangle.h"
#include "../../../../SuperGameEngine/Structural/Spatial/Area/Circle.h"

using namespace SuperGameEngine;
namespace SuperGameEngine_Structural_Spatial_Area
{
    class RectangleTests : public ::testing::Test
    {
    public:
        RectangleTests()
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
    TEST_F(RectangleTests, OnContruction_ReturnsGivenLocation_WhenGivenAsXY)
    {
        float givenX = 6;
        float givenY = 10;
        float validWidthHeight = 1;

        m_testRectangle = new Rectangle(givenX, givenY, validWidthHeight, validWidthHeight);

        ASSERT_EQ(givenX, m_testRectangle->GetLeft());
        ASSERT_EQ(givenY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsWidthHeight)
    {
        float givenWidth = 21;
        float givenHeight = 42;
        float validXY = 1;

        m_testRectangle = new Rectangle(validXY, validXY, givenWidth, givenHeight);

        ASSERT_EQ(givenWidth, m_testRectangle->GetWidth());
        ASSERT_EQ(givenHeight, m_testRectangle->GetHeight());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenLocation_WhenGivenAsSingleLocation)
    {
        float givenXY = 6;
        float validWidthHeight = 1;

        m_testRectangle = new Rectangle(givenXY, validWidthHeight);

        ASSERT_EQ(givenXY, m_testRectangle->GetLeft());
        ASSERT_EQ(givenXY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsSingleSize)
    {
        float givenWidthHeight = 21;
        float validXY = 1;

        m_testRectangle = new Rectangle(validXY, givenWidthHeight);

        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetWidth());
        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetHeight());
    }

#pragma endregion

#pragma region SetAndGet
    TEST_F(RectangleTests, GetSetX_ChangesLeftValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenX = 42;
        ASSERT_NE(m_testRectangle->GetLeft(), givenX) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetX(givenX);
        float actual = m_testRectangle->GetLeft();

        ASSERT_EQ(givenX, actual);
    }

    TEST_F(RectangleTests, GetSetY_ChangesTopValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenY = 98;
        ASSERT_NE(m_testRectangle->GetTop(), givenY) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetY(givenY);
        float actual = m_testRectangle->GetTop();

        ASSERT_EQ(givenY, actual);
    }

    TEST_F(RectangleTests, GetSetWidth_ChangesWidthValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenWidth = 100;
        ASSERT_NE(m_testRectangle->GetWidth(), givenWidth) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetWidth(givenWidth);
        float actual = m_testRectangle->GetWidth();

        ASSERT_EQ(givenWidth, actual);
    }

    TEST_F(RectangleTests, GetSetHeight_ChangesHeightValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenHeight = 21;
        ASSERT_NE(m_testRectangle->GetHeight(), givenHeight) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetHeight(givenHeight);
        float actual = m_testRectangle->GetHeight();

        ASSERT_EQ(givenHeight, actual);
    }

    TEST_F(RectangleTests, SetLocation_ChangesLeftAndTopValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenX = 42;
        float givenY = 87;
        ASSERT_NE(m_testRectangle->GetLeft(), givenX) << "Ensure the given is not the original, otherwise test means nothing";
        ASSERT_NE(m_testRectangle->GetTop(), givenY) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetLocation(givenX, givenY);
        float actualX = m_testRectangle->GetLeft();
        float actualY = m_testRectangle->GetTop();

        ASSERT_EQ(givenX, actualX);
        ASSERT_EQ(givenY, actualY);
    }

    TEST_F(RectangleTests, SetSize_ChangesWidthHeightValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenWidth = 12;
        float givenHeight = 87;
        ASSERT_NE(m_testRectangle->GetWidth(), givenWidth) << "Ensure the given is not the original, otherwise test means nothing";
        ASSERT_NE(m_testRectangle->GetHeight(), givenHeight) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetSize(givenWidth, givenHeight);
        float actualWidth = m_testRectangle->GetWidth();
        float actualHeight = m_testRectangle->GetHeight();

        ASSERT_EQ(givenWidth, actualWidth);
        ASSERT_EQ(givenHeight, actualHeight);
    }

    TEST_F(RectangleTests, MoveShape_IncreasesXAndY_WhenGivenPositiveValues)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0);

        float givenWidthHeight = 2;
        m_testRectangle->SetSize(givenWidthHeight, givenWidthHeight);

        float expectedLeft = 2;
        float expectedRight = expectedLeft + givenWidthHeight;
        float expectedTop = 56;
        float expectedBottom = expectedTop + givenWidthHeight;
        FVector2D given = FVector2D(expectedLeft, expectedTop);

        // Act
        m_testRectangle->MoveShape(given);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleTests, MoveShape_DecreasesXAndY_WhenGivenNegativeValues)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0);

        float givenWidthHeight = 2;
        m_testRectangle->SetSize(givenWidthHeight, givenWidthHeight);

        float expectedLeft = -2;
        float expectedRight = expectedLeft + givenWidthHeight;
        float expectedTop = -9;
        float expectedBottom = expectedTop + givenWidthHeight;
        FVector2D given = FVector2D(expectedLeft, expectedTop);

        // Act
        m_testRectangle->MoveShape(given);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }
#pragma endregion

#pragma region Extents
    TEST_F(RectangleTests, GetRight_ReturnsLeftPlusWidth)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenLeft = 21;
        m_testRectangle->SetX(givenLeft);
        float givenWidth = 76;
        m_testRectangle->SetWidth(givenWidth);
        float expectedRight = givenLeft + givenWidth;

        float actual = m_testRectangle->GetRight();

        ASSERT_EQ(expectedRight, actual);
    }

    TEST_F(RectangleTests, GetBottom_ReturnsTopPlusHeight)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenTop = 21;
        m_testRectangle->SetY(givenTop);
        float givenHeight = 76;
        m_testRectangle->SetHeight(givenHeight);
        float expectedBottom = givenTop + givenHeight;

        float actual = m_testRectangle->GetBottom();

        ASSERT_EQ(expectedBottom, actual);
    }

    TEST_F(RectangleTests, GetTopLeft_ReturnsTopAndLeft)
    {
        m_testRectangle = CreateBasicRectangle();
        float givenTop = 21;
        m_testRectangle->SetY(givenTop);
        float givenLeft = 76;
        m_testRectangle->SetX(givenLeft);

        FVector2D actual = m_testRectangle->GetTopLeft();

        ASSERT_EQ(givenLeft, actual.GetX());
        ASSERT_EQ(givenTop, actual.GetY());
    }

    TEST_F(RectangleTests, GetBottomRight_ReturnsTopPlusHeightAndLeftPlusWidth)
    {
        // Arrange
        m_testRectangle = CreateBasicRectangle();

        float givenTop = 21;
        m_testRectangle->SetY(givenTop);
        float givenHeight = 76;
        m_testRectangle->SetHeight(givenHeight);
        float expectedBottom = givenTop + givenHeight;

        float givenLeft = 76;
        m_testRectangle->SetX(givenLeft);
        float givenWidth = 76;
        m_testRectangle->SetWidth(givenWidth);
        float expectedRight = givenLeft + givenWidth;

        // Act
        FVector2D actual = m_testRectangle->GetBottomRight();

        // Assert
        ASSERT_EQ(expectedRight, actual.GetX());
        ASSERT_EQ(expectedBottom, actual.GetY());
    }
#pragma endregion

#pragma region Overlaps
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleTests, Overlaps_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;
       
        float selfX = 5;
        float otherX = selfX - bothWidthHeight;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, Overlaps_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX + bothWidthHeight;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, Overlaps_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX - (bothWidthHeight / 2.0f);

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, Overlaps_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY - bothWidthHeight;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, Overlaps_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY + bothWidthHeight;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, Overlaps_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY - (bothWidthHeight / 2.0f);

        m_testRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapsOrIsTouching
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX - bothWidthHeight - 1;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX + bothWidthHeight + 1;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherRightIsTouchingSelfLeft)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX - bothWidthHeight;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherLeftIsTouchingSelfRight)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX + bothWidthHeight;

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(selfX + bothWidthHeight, otherX));
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothY = 0;

        float selfX = 5;
        float otherX = selfX - (bothWidthHeight / 2.0f);

        m_testRectangle = new Rectangle(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY - bothWidthHeight - 1;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY + bothWidthHeight + 1;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherBottomIsTouchingSelfTop)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY - bothWidthHeight;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherTopIsTouchingSelfBottom)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY + bothWidthHeight;

        m_testRectangle = new Rectangle(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        float bothWidthHeight = 10;
        float bothX = 0;

        float selfY = 5;
        float otherY = selfY - (bothWidthHeight / 2.0f);

        m_testRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = new Rectangle(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region PointIsWithin
    TEST_F(RectangleTests, PointIsWithin_ReturnsFalse_WhenPointIsEasilyOutsideRectangle)
    {
        // Arrange
        FVector2D givenLocation = FVector2D(5, 5);

        m_testRectangle = CreateBasicRectangle();

        // Act
        bool actual = m_testRectangle->PointIsWithin(givenLocation);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, PointIsWithin_ReturnsTrue_WhenPointEqualsCenterOfRectangle)
    {
        // Arrange
        FVector2D givenLocation = FVector2D(1, 1);

        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(0, 0);
        m_testRectangle->SetSize(2, 2);

        // Act
        bool actual = m_testRectangle->PointIsWithin(givenLocation);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region Overlaps Circle
    TEST_F(RectangleTests, OverlapsCircle_ReturnsFalse_WhenExtentsOfRectangleAreNotWithinCircle)
    {
        // Arrange
        FVector2D givenFirstLocation = FVector2D(10, 10);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);

        FVector2D givenSecondLocation = FVector2D(0, 0);
        m_testRectangle = CreateBasicRectangle();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheX)
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
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheY)
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
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheXAndY)
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
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OverlapsCircle_ReturnsTrue_WhenCircleIsContainedCompletelyInTheRectangle)
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
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapAmount
    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheX)
    {
        // Arrange
        
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(3, 0, 3, 1);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 1);
        FVector2D expectedOverlap = FVector2D(1, 1);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = new Rectangle(1, 0, 3, 1);
        m_otherTestRectangle = new Rectangle(2, 0, 6, 1);
        FVector2D expectedOverlap = FVector2D(2, 1);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = new Rectangle(1, 0, 6, 1);
        m_otherTestRectangle = new Rectangle(5, 0, 3, 1);
        FVector2D expectedOverlap = FVector2D(2, 1);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInX_WhenLeftIsOnTheRightInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = new Rectangle(1, 0, 6, 1);
        m_otherTestRectangle = new Rectangle(5, 0, 3, 1);
        FVector2D expectedOverlap = FVector2D(2, 1);

        // Act
        FVector2D actual = m_otherTestRectangle->OverlapAmount(*m_testRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheY)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(0, 3, 1, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 1, 1);
        FVector2D expectedOverlap = FVector2D(1, 1);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = new Rectangle(0, 1, 1, 3);
        m_otherTestRectangle = new Rectangle(0, 2, 1, 6);
        FVector2D expectedOverlap = FVector2D(1, 2);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = new Rectangle(0, 1, 1, 6);
        m_otherTestRectangle = new Rectangle(0, 5, 1, 3);
        FVector2D expectedOverlap = FVector2D(1, 2);

        // Act
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleTests, OverlapAmount_ReturnsTheDifferencesInY_WhenLeftIsBelowInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = new Rectangle(0, 1, 1, 6);
        m_otherTestRectangle = new Rectangle(0, 5, 1, 3);
        FVector2D expectedOverlap = FVector2D(1, 2);

        // Act
        FVector2D actual = m_otherTestRectangle->OverlapAmount(*m_testRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf
    TEST_F(RectangleTests, MoveOutOfOverlapRangeOf_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 2;
        float expectedRight = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOf_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(5, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 6;
        float expectedRight = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOf_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        float expectedTop = 2;
        float expectedBottom = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOf_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(0, 5, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        float expectedTop = 6;
        float expectedBottom = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOf_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 2;
        float expectedRight = 5;
        float expectedTop = 0;
        float expectedBottom = 10;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap
    TEST_F(RectangleTests, GetNewLocationToNotOverlap_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 2;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlap_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(5, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlap_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        float expectedTop = 2;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlap_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(0, 5, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        float expectedTop = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlap_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        float expectedLeft = 2;
        float expectedTop = 0;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region Overlap Amount With Location
    TEST_F(RectangleTests, OverlapAmountWithLoc_ReturnsTheDifferenceInPreviousLocationX_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resitance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = new Rectangle(0, 0, 2, 1);
        m_otherTestRectangle = new Rectangle(1, 0, 3, 1);
        FVector2D givenLocation = FVector2D(7, 1);
        FVector2D expectedOverlap = FVector2D(4, 1);

        // Check the least resitance path
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetX()) << "Least resitance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetX(), actual.GetX()) << "Least resitance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmountWithLoc_ReturnsLeastResistanceX_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resitance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = new Rectangle(0, 0, 2, 1);
        m_otherTestRectangle = new Rectangle(1, 0, 3, 1);
        FVector2D givenLocation = FVector2D(-7, 1);
        FVector2D expectedOverlap = FVector2D(1, 1);

        // Check the least resitance path
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetX()) << "Least resitance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX()) << "Least resitance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleTests, OverlapAmountWithLoc_ReturnsTheDifferenceInPreviousLocationY_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resitance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = new Rectangle(0, 0, 1, 2);
        m_otherTestRectangle = new Rectangle(0, 1, 1, 3);
        FVector2D givenLocation = FVector2D(1, 7);
        FVector2D expectedOverlap = FVector2D(1, 4);

        // Check the least resitance path
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetY()) << "Least resitance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetY(), actual.GetY()) << "Least resitance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleTests, OverlapAmountWithLoc_ReturnsLeastResistanceY_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resitance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = new Rectangle(0, 0, 1, 2);
        m_otherTestRectangle = new Rectangle(0, 1, 1, 3);
        FVector2D givenLocation = FVector2D(1, -7);
        FVector2D expectedOverlap = FVector2D(1, 1);

        // Check the least resitance path
        FVector2D actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetY()) << "Least resitance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY()) << "Least resitance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap With Location
    TEST_F(RectangleTests, GetNewLocationToNotOverlapWithLocation_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        FVector2D givenLocation = FVector2D(0, 1);
        float expectedLeft = 2;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlapWithLocation_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        FVector2D givenLocation = FVector2D(7, 1);
        float expectedLeft = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlapWithLocation_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        FVector2D givenLocation = FVector2D(1, 0);
        float expectedTop = 2;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleTests, GetNewLocationToNotOverlapWithLocation_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        FVector2D givenLocation = FVector2D(1, 7);
        float expectedTop = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf With Location
    TEST_F(RectangleTests, MoveOutOfOverlapRangeOfWithLocation_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        FVector2D givenLocation = FVector2D(0, 1);
        float expectedLeft = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOfWithLocation_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = new Rectangle(3, 0, 3, 10);
        m_otherTestRectangle = new Rectangle(5, 0, 1, 10);
        FVector2D givenLocation = FVector2D(7, 1);
        float expectedLeft = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOfWithLocation_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        FVector2D givenLocation = FVector2D(1, 0);
        float expectedTop = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }

    TEST_F(RectangleTests, MoveOutOfOverlapRangeOfWithLocation_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = new Rectangle(0, 3, 10, 3);
        m_otherTestRectangle = new Rectangle(0, 5, 10, 1);
        FVector2D givenLocation = FVector2D(1, 7);
        float expectedTop = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }
#pragma endregion

#pragma region CloestPointTo
    TEST_F(RectangleTests, CloestPointTo_MatchesY_WhenToTheLeftOrRight)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationLeft = FVector2D(-5, 7);
        FVector2D givenLocationRight = FVector2D(12, 5);

        // Act
        FVector2D actualLeft = m_testRectangle->CloestPointTo(givenLocationLeft);
        FVector2D actualRight = m_testRectangle->CloestPointTo(givenLocationRight);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(givenLocationLeft.GetY(), actualLeft.GetY()))
            << "Expected: " << givenLocationLeft.GetY() << " Actual: " << actualLeft.GetY();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(givenLocationRight.GetY(), actualRight.GetY()))
            << "Expected: " << givenLocationRight.GetY() << " Actual: " << actualRight.GetY();
    }

    TEST_F(RectangleTests, CloestPointTo_MatchesXLeft_WhenToTheLeft)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationLeft = FVector2D(-5, 7);

        // Act
        FVector2D actualLeft = m_testRectangle->CloestPointTo(givenLocationLeft);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(m_testRectangle->GetLeft(), actualLeft.GetX()))
            << "Expected: " << m_testRectangle->GetLeft() << " Actual: " << actualLeft.GetX();
    }

    TEST_F(RectangleTests, CloestPointTo_MatchesXRight_WhenToTheRight)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationRight = FVector2D(12, 5);

        // Act
        FVector2D actualRight = m_testRectangle->CloestPointTo(givenLocationRight);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(m_testRectangle->GetRight(), actualRight.GetX()))
            << "Expected: " << m_testRectangle->GetRight() << " Actual: " << actualRight.GetX();
    }

    TEST_F(RectangleTests, CloestPointTo_MatchesX_WhenAboveOrBelow)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationAbove = FVector2D(7, -5);
        FVector2D givenLocationBelow = FVector2D(5, 12);

        // Act
        FVector2D actualAbove = m_testRectangle->CloestPointTo(givenLocationAbove);
        FVector2D actualBelow = m_testRectangle->CloestPointTo(givenLocationBelow);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(givenLocationAbove.GetX(), actualAbove.GetX()))
            << "Expected: " << givenLocationAbove.GetX() << " Actual: " << actualAbove.GetX();
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(givenLocationBelow.GetX(), actualBelow.GetX()))
            << "Expected: " << givenLocationBelow.GetX() << " Actual: " << actualBelow.GetX();
    }

    TEST_F(RectangleTests, CloestPointTo_MatchesYAbove_WhenAbove)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationAbove = FVector2D(7, -5);

        // Act
        FVector2D actualAbove = m_testRectangle->CloestPointTo(givenLocationAbove);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(m_testRectangle->GetTop(), actualAbove.GetY()))
            << "Expected: " << m_testRectangle->GetTop() << " Actual: " << actualAbove.GetY();
    }

    TEST_F(RectangleTests, CloestPointTo_MatchesYBelow_WhenBelow)
    {
        // Arrange
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        FVector2D givenLocationRight = FVector2D(5, 12);

        // Act
        FVector2D actualBelow = m_testRectangle->CloestPointTo(givenLocationRight);

        // Assert
        ASSERT_TRUE(FloatingPointHelpers::AreEqual(m_testRectangle->GetBottom(), actualBelow.GetY()))
            << "Expected: " << m_testRectangle->GetBottom() << " Actual: " << actualBelow.GetY();
    }
#pragma endregion

#pragma region Operator==
    TEST_F(RectangleTests, OperatorEquals_ReturnsTrue_WhenBothSideAreFuntionallyTheSame)
    {
        m_testRectangle = new Rectangle(0, 0, 10, 10);
        m_otherTestRectangle = new Rectangle(0, 0, 10, 10);

        bool actual = *m_testRectangle == *m_otherTestRectangle;

        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleTests, OperatorEquals_ReturnsFalse_WhenBothSideAreDifferent)
    {
        m_testRectangle = new Rectangle(1, 2, 3, 4);
        m_otherTestRectangle = new Rectangle(0, 0, 10, 10);

        bool actual = *m_testRectangle == *m_otherTestRectangle;

        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleTests, OperatorEquals_ReturnsTrue_WhenBothSideAreFuntionallyTheSameFloatWize)
    {
        m_testRectangle = new Rectangle(0.000001f, 0.000001f, 10.000001f, 10.000001f);
        m_otherTestRectangle = new Rectangle(0, 0, 10, 10);

        bool actual = *m_testRectangle == *m_otherTestRectangle;

        ASSERT_TRUE(actual);
    }
#pragma endregion
}