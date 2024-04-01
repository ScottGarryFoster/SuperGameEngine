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
            m_testRectangle = nullptr;
            m_otherTestRectangle = nullptr;
        }

    protected:

        Rectangle* m_testRectangle;
        Rectangle* m_otherTestRectangle;

        void SetUp() override
        {

        }

        void TearDown() override
        {
            if (m_testRectangle != nullptr)
            {
                delete m_testRectangle;
            }
            else if (m_otherTestRectangle != nullptr)
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
}