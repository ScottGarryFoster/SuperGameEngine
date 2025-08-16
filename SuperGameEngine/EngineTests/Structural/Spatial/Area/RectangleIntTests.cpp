#include "../../../../Engine/Structural/Spatial/Area/Circle.h"
#include "../../../../Engine/Structural/Spatial/Area/Rectangle.h"
#include "../../../../Engine/Structural/Spatial/Area/RectangleInt.h"
#include "../../../../Engine/FatedQuestReferences.h"
#include <memory>
#include <gtest/gtest.h>

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
namespace SuperGameEngineTests_Structural_Spatial_Area
{
    class RectangleIntTests : public ::testing::Test
    {
    public:
        RectangleIntTests()
        {
        }

    protected:

        std::shared_ptr<Circle> m_testCircle;
        std::shared_ptr<Circle> m_otherTestCircle;

        std::shared_ptr<SuperGameEngine::Rectangle> m_testRectangleOriginal;
        std::shared_ptr<SuperGameEngine::Rectangle> m_otherTestRectangleOriginal;

        std::shared_ptr<RectangleInt> m_testRectangle;
        std::shared_ptr<RectangleInt> m_otherTestRectangle;

        void SetUp() override
        {

        }

        void TearDown() override
        {
        }

        /// <summary>
        /// Creates a basic rectangle for testing.
        /// </summary>
        /// <returns>A Unit 1 by 1 rectangle at (1, 1). </returns>
        std::shared_ptr<RectangleInt> CreateBasicRectangleInt()
        {
            int originalXY = 1;
            int originalWidthHeight = 1;
            return std::make_shared<RectangleInt>(originalXY, originalWidthHeight);
        }

        /// <summary>
        /// Creates a basic circle for testing.
        /// </summary>
        /// <returns>A Unit 1 by 1 circle at (1, 1). </returns>
        std::shared_ptr<Circle> CreateBasicCircle()
        {
            float originalXY = 1;
            int validRadius = 1;
            return std::make_shared<Circle>(originalXY, originalXY, validRadius);
        }
    };

#pragma region Construction
    TEST_F(RectangleIntTests, OnContruction_ReturnsGivenLocation_WhenGivenAsXY)
    {
        int givenX = 6;
        int givenY = 10;
        int validWidthHeight = 1;

        m_testRectangle = std::make_shared<RectangleInt>(givenX, givenY, validWidthHeight, validWidthHeight);

        ASSERT_EQ(givenX, m_testRectangle->GetLeft());
        ASSERT_EQ(givenY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleIntTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsWidthHeight)
    {
        int givenWidth = 21;
        int givenHeight = 42;
        int validXY = 1;

        m_testRectangle = std::make_shared<RectangleInt>(validXY, validXY, givenWidth, givenHeight);

        ASSERT_EQ(givenWidth, m_testRectangle->GetWidth());
        ASSERT_EQ(givenHeight, m_testRectangle->GetHeight());
    }

    TEST_F(RectangleIntTests, OnContruction_ReturnsGivenLocation_WhenGivenAsSingleLocation)
    {
        int givenXY = 6;
        int validWidthHeight = 1;

        m_testRectangle = std::make_shared<RectangleInt>(givenXY, validWidthHeight);

        ASSERT_EQ(givenXY, m_testRectangle->GetLeft());
        ASSERT_EQ(givenXY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleIntTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsSingleSize)
    {
        int givenWidthHeight = 21;
        int validXY = 1;

        m_testRectangle = std::make_shared<RectangleInt>(validXY, givenWidthHeight);

        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetWidth());
        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetHeight());
    }

    TEST_F(RectangleIntTests, OnContruction_ReturnsLocationAndSize_WhenGivenVector4I)
    {
        FVector4I given = FVector4I(1, 2, 3, 4);

        m_testRectangle = std::make_shared<RectangleInt>(given);

        ASSERT_EQ(given.GetX(), m_testRectangle->GetLeft());
        ASSERT_EQ(given.GetY(), m_testRectangle->GetTop());
        ASSERT_EQ(given.GetZ(), m_testRectangle->GetWidth());
        ASSERT_EQ(given.GetW(), m_testRectangle->GetHeight());
    }

    TEST_F(RectangleIntTests, OnContruction_ReturnsLocationAndSize_WhenGivenVector4IPointer)
    {
        auto given = std::make_shared<FVector4I>(1, 2, 3, 4);

        m_testRectangle = std::make_shared<RectangleInt>(given);

        ASSERT_EQ(given->GetX(), m_testRectangle->GetLeft());
        ASSERT_EQ(given->GetY(), m_testRectangle->GetTop());
        ASSERT_EQ(given->GetZ(), m_testRectangle->GetWidth());
        ASSERT_EQ(given->GetW(), m_testRectangle->GetHeight());
    }

#pragma endregion

#pragma region SetAndGet
    TEST_F(RectangleIntTests, GetSetX_ChangesLeftValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenX = 42;
        ASSERT_NE(m_testRectangle->GetLeft(), givenX) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetX(givenX);
        int actual = m_testRectangle->GetLeft();

        ASSERT_EQ(givenX, actual);
    }

    TEST_F(RectangleIntTests, GetSetY_ChangesTopValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenY = 98;
        ASSERT_NE(m_testRectangle->GetTop(), givenY) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetY(givenY);
        int actual = m_testRectangle->GetTop();

        ASSERT_EQ(givenY, actual);
    }

    TEST_F(RectangleIntTests, GetSetWidth_ChangesWidthValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenWidth = 100;
        ASSERT_NE(m_testRectangle->GetWidth(), givenWidth) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetWidth(givenWidth);
        int actual = m_testRectangle->GetWidth();

        ASSERT_EQ(givenWidth, actual);
    }

    TEST_F(RectangleIntTests, GetSetHeight_ChangesHeightValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenHeight = 21;
        ASSERT_NE(m_testRectangle->GetHeight(), givenHeight) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetHeight(givenHeight);
        int actual = m_testRectangle->GetHeight();

        ASSERT_EQ(givenHeight, actual);
    }

    TEST_F(RectangleIntTests, SetLocation_ChangesLeftAndTopValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenX = 42;
        int givenY = 87;
        ASSERT_NE(m_testRectangle->GetLeft(), givenX) << "Ensure the given is not the original, otherwise test means nothing";
        ASSERT_NE(m_testRectangle->GetTop(), givenY) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetLocation(givenX, givenY);
        int actualX = m_testRectangle->GetLeft();
        int actualY = m_testRectangle->GetTop();

        ASSERT_EQ(givenX, actualX);
        ASSERT_EQ(givenY, actualY);
    }

    TEST_F(RectangleIntTests, SetSize_ChangesWidthHeightValue_WhenGivenNewValue)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenWidth = 12;
        int givenHeight = 87;
        ASSERT_NE(m_testRectangle->GetWidth(), givenWidth) << "Ensure the given is not the original, otherwise test means nothing";
        ASSERT_NE(m_testRectangle->GetHeight(), givenHeight) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetSize(givenWidth, givenHeight);
        int actualWidth = m_testRectangle->GetWidth();
        int actualHeight = m_testRectangle->GetHeight();

        ASSERT_EQ(givenWidth, actualWidth);
        ASSERT_EQ(givenHeight, actualHeight);
    }

    TEST_F(RectangleIntTests, MoveShape_IncreasesXAndY_WhenGivenPositiveValues)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0);

        int givenWidthHeight = 2;
        m_testRectangle->SetSize(givenWidthHeight, givenWidthHeight);

        int expectedLeft = 2;
        int expectedRight = expectedLeft + givenWidthHeight;
        int expectedTop = 56;
        int expectedBottom = expectedTop + givenWidthHeight;
        FPoint given = FPoint(expectedLeft, expectedTop);

        // Act
        m_testRectangle->MoveShape(given);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleIntTests, MoveShape_DecreasesXAndY_WhenGivenNegativeValues)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0);

        int givenWidthHeight = 2;
        m_testRectangle->SetSize(givenWidthHeight, givenWidthHeight);

        int expectedLeft = -2;
        int expectedRight = expectedLeft + givenWidthHeight;
        int expectedTop = -9;
        int expectedBottom = expectedTop + givenWidthHeight;
        FPoint given = FPoint(expectedLeft, expectedTop);

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
    TEST_F(RectangleIntTests, GetRight_ReturnsLeftPlusWidth)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenLeft = 21;
        m_testRectangle->SetX(givenLeft);
        int givenWidth = 76;
        m_testRectangle->SetWidth(givenWidth);
        int expectedRight = givenLeft + givenWidth;

        int actual = m_testRectangle->GetRight();

        ASSERT_EQ(expectedRight, actual);
    }

    TEST_F(RectangleIntTests, GetBottom_ReturnsTopPlusHeight)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenTop = 21;
        m_testRectangle->SetY(givenTop);
        int givenHeight = 76;
        m_testRectangle->SetHeight(givenHeight);
        int expectedBottom = givenTop + givenHeight;

        int actual = m_testRectangle->GetBottom();

        ASSERT_EQ(expectedBottom, actual);
    }

    TEST_F(RectangleIntTests, GetTopLeft_ReturnsTopAndLeft)
    {
        m_testRectangle = CreateBasicRectangleInt();
        int givenTop = 21;
        m_testRectangle->SetY(givenTop);
        int givenLeft = 76;
        m_testRectangle->SetX(givenLeft);

        FPoint actual = m_testRectangle->GetTopLeft();

        ASSERT_EQ(givenLeft, actual.GetX());
        ASSERT_EQ(givenTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetBottomRight_ReturnsTopPlusHeightAndLeftPlusWidth)
    {
        // Arrange
        m_testRectangle = CreateBasicRectangleInt();

        int givenTop = 21;
        m_testRectangle->SetY(givenTop);
        int givenHeight = 76;
        m_testRectangle->SetHeight(givenHeight);
        int expectedBottom = givenTop + givenHeight;

        int givenLeft = 76;
        m_testRectangle->SetX(givenLeft);
        int givenWidth = 76;
        m_testRectangle->SetWidth(givenWidth);
        int expectedRight = givenLeft + givenWidth;

        // Act
        FPoint actual = m_testRectangle->GetBottomRight();

        // Assert
        ASSERT_EQ(expectedRight, actual.GetX());
        ASSERT_EQ(expectedBottom, actual.GetY());
    }
#pragma endregion

#pragma region Overlaps
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleIntTests, Overlaps_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, Overlaps_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, Overlaps_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - (bothWidthHeight / 2.0f);

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, Overlaps_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, Overlaps_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, Overlaps_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = (int)(selfY - (bothWidthHeight / 2.0f));

        m_testRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region Overlaps Rectangle (floats)
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - (bothWidthHeight / 2.0f);

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsRec_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = (int)(selfY - (bothWidthHeight / 2.0f));

        m_testRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapsOrIsTouching
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight - 1;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight + 1;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherRightIsTouchingSelfLeft)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherLeftIsTouchingSelfRight)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);
        ASSERT_EQ(selfX + bothWidthHeight, otherX);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = (int)(selfX - (bothWidthHeight / 2.0f));

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight - 1;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight + 1;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherBottomIsTouchingSelfTop)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherTopIsTouchingSelfBottom)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouching_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - (bothWidthHeight / 2.0f);

        m_testRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapsOrIsTouching
    //  For these tests, 'self' refers to the testing object and 'other' the object passed in.

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsFalse_WhenOtherRightIsToTheLeftOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight - 1;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsFalse_WhenOtherLeftIsToTheRightOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight + 1;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsTrue_WhenOtherRightIsTouchingSelfLeft)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsFalse_WhenOtherLeftIsTouchingSelfRight)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = selfX + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);
        ASSERT_EQ(selfX + bothWidthHeight, otherX);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsTrue_WhenOtherRightIsWithinBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothY = 0;

        int selfX = 5;
        int otherX = (int)(selfX - (bothWidthHeight / 2.0f));

        m_testRectangle = std::make_shared<RectangleInt>(selfX, bothY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(otherX, bothY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsFalse_WhenOtherBottomIsAboveSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight - 1;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsFalse_WhenOtherTopIsBelowSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight + 1;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsTrue_WhenOtherBottomIsTouchingSelfTop)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsTrue_WhenOtherTopIsTouchingSelfBottom)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY + bothWidthHeight;

        m_testRectangle = std::make_shared<RectangleInt>(bothX, selfY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsOrIsTouchingRec_ReturnsTrue_WhenOtherTopIsInBodyOfSelf)
    {
        // Arrange
        int bothWidthHeight = 10;
        int bothX = 0;

        int selfY = 5;
        int otherY = selfY - (bothWidthHeight / 2.0f);

        m_testRectangle = std::make_shared<RectangleInt>(bothX, otherY, bothWidthHeight, bothWidthHeight);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(bothX, otherY, bothWidthHeight, bothWidthHeight);

        // Act
        bool actual = m_testRectangle->OverlapsOrIsTouching(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region PointIsWithin
    TEST_F(RectangleIntTests, PointIsWithin_ReturnsFalse_WhenPointIsEasilyOutsideRectangle)
    {
        // Arrange
        FPoint givenLocation = FPoint(5, 5);

        m_testRectangle = CreateBasicRectangleInt();

        // Act
        bool actual = m_testRectangle->PointIsWithin(givenLocation);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, PointIsWithin_ReturnsTrue_WhenPointEqualsCenterOfRectangle)
    {
        // Arrange
        FPoint givenLocation = FPoint(1, 1);

        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(0, 0);
        m_testRectangle->SetSize(2, 2);

        // Act
        bool actual = m_testRectangle->PointIsWithin(givenLocation);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region Overlaps Circle
    TEST_F(RectangleIntTests, OverlapsCircle_ReturnsFalse_WhenExtentsOfRectangleAreNotWithinCircle)
    {
        // Arrange
        FVector2D givenFirstLocation = FVector2D(10, 10);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);

        FPoint givenSecondLocation = FPoint(0, 0);
        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheX)
    {
        // Arrange
        int radius = 1;
        float touchingX = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(touchingX, 0);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FPoint givenSecondLocation = FPoint(0, 0);
        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheY)
    {
        // Arrange
        int radius = 1;
        float touchingY = radius + radius - 0.1f;

        FVector2D givenFirstLocation = FVector2D(0, touchingY);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FPoint givenSecondLocation = FPoint(0, 0);
        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsCircle_ReturnsTrue_WhenCircleAndRectangleOverlapOnTheXAndY)
    {
        // Arrange
        int radius = 1;

        FVector2D givenFirstLocation = FVector2D(0.5f, 0.5f);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FPoint givenSecondLocation = FPoint(1, 1);
        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OverlapsCircle_ReturnsTrue_WhenCircleIsContainedCompletelyInTheRectangle)
    {
        // Arrange
        int radius = 1;

        FVector2D givenFirstLocation = FVector2D(5, 5);
        m_testCircle = CreateBasicCircle();
        m_testCircle->SetLocation(givenFirstLocation);
        m_testCircle->SetRadius(radius);

        FPoint givenSecondLocation = FPoint(0, 0);
        m_testRectangle = CreateBasicRectangleInt();
        m_testRectangle->SetLocation(givenSecondLocation.GetX(), givenSecondLocation.GetY());
        m_testRectangle->SetSize(10, 10);

        // Act
        bool actual = m_testRectangle->Overlaps(*m_testCircle);

        // Assert
        ASSERT_TRUE(actual);
    }
#pragma endregion

#pragma region OverlapAmount
    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheX)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = std::make_shared<RectangleInt>(1, 0, 3, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(2, 0, 6, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(1, 0, 6, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 3, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInX_WhenLeftIsOnTheRightInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(1, 0, 6, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 3, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_otherTestRectangle->OverlapAmount(*m_testRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheY)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 1, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 1, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 1, 1, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 2, 1, 6);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 1, 1, 6);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 1, 3);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmount_ReturnsTheDifferencesInY_WhenLeftIsBelowInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 1, 1, 6);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 1, 3);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_otherTestRectangle->OverlapAmount(*m_testRectangle);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region OverlapAmount
    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheX)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = std::make_shared<RectangleInt>(1, 0, 3, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(2, 0, 6, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInX_WhenTwoRectanglesOverlapOnTheXAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(1, 0, 6, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 3, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInX_WhenLeftIsOnTheRightInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(5, 0, 3, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(1, 0, 6, 1);
        FPoint expectedOverlap = FPoint(2, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheY)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 1, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 1, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndOtherOverlapsLess)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X O O Y Y Y Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 2/3, Other overlaps 1/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 1, 1, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 2, 1, 6);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInY_WhenTwoRectanglesOverlapOnTheYAndYouOverlapMore)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 1, 1, 6);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 1, 3);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmountRec_ReturnsTheDifferencesInY_WhenLeftIsBelowInTheWorld)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - X X X X O O Y
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // Given overlaps 1/3, Other overlaps 2/3

        m_testRectangle = std::make_shared<RectangleInt>(0, 5, 1, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 1, 1, 6);
        FPoint expectedOverlap = FPoint(1, 2);

        // Act
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf
    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOf_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedRight = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOf_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(5, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 6;
        int expectedRight = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOf_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        int expectedTop = 2;
        int expectedBottom = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOf_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 5, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        int expectedTop = 6;
        int expectedBottom = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOf_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedRight = 5;
        int expectedTop = 0;
        int expectedBottom = 10;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf
    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfRec_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedRight = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfRec_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(5, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 6;
        int expectedRight = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfRec_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        int expectedTop = 2;
        int expectedBottom = 5;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfRec_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 5, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        int expectedTop = 6;
        int expectedBottom = 9;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfRec_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedRight = 5;
        int expectedTop = 0;
        int expectedBottom = 10;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
        ASSERT_EQ(expectedRight, m_testRectangle->GetRight());
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
        ASSERT_EQ(expectedBottom, m_testRectangle->GetBottom());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap
    TEST_F(RectangleIntTests, GetNewLocationToNotOverlap_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlap_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(5, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlap_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        int expectedTop = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlap_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 5, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        int expectedTop = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlap_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedTop = 0;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap
    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapRec_MovesToTheLeftByOverlap_WhenOverlappingMostOnRight)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapRec_MovesToTheRightByOverlap_WhenOverlappingMostOnLeft)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(5, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapRec_MovesUpByOverlap_WhenOverlappingMostBelow)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        int expectedTop = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapRec_MovesdOWNByOverlap_WhenOverlappingMostAbove)
    {
        // Arrange

        // Setup
        // (Remember lower numbers means higher in the viewport)
        // 0 1 2 3 4 5 6 7 8
        // - - - - - O X X -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(0, 5, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        int expectedTop = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapRec_MovesX_WhenXIsLowerThanYWhenMovingAway)
    {
        // Arrange

        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - -
        // X -> m_testRectangle
        // O -> overlap

        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        int expectedLeft = 2;
        int expectedTop = 0;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region Overlap Amount With Location
    TEST_F(RectangleIntTests, OverlapAmountWithLoc_ReturnsTheDifferenceInPreviousLocationX_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 2, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(1, 0, 3, 1);
        FPoint givenLocation = FPoint(7, 1);
        FPoint expectedOverlap = FPoint(4, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetX()) << "Least resistance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetX(), actual.GetX()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLoc_ReturnsLeastResistanceX_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 2, 1);
        m_otherTestRectangle = std::make_shared<RectangleInt>(1, 0, 3, 1);
        FPoint givenLocation = FPoint(-7, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetX()) << "Least resistance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLoc_ReturnsTheDifferenceInPreviousLocationY_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 1, 2);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 1, 1, 3);
        FPoint givenLocation = FPoint(1, 7);
        FPoint expectedOverlap = FPoint(1, 4);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetY()) << "Least resistance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetY(), actual.GetY()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLoc_ReturnsLeastResistanceY_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 1, 2);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 1, 1, 3);
        FPoint givenLocation = FPoint(1, -7);
        FPoint expectedOverlap = FPoint(1, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle);
        ASSERT_EQ(1, actual.GetY()) << "Least resistance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region Overlap Amount With Location
    TEST_F(RectangleIntTests, OverlapAmountWithLocRec_ReturnsTheDifferenceInPreviousLocationX_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 2, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(1, 0, 3, 1);
        FPoint givenLocation = FPoint(7, 1);
        FPoint expectedOverlap = FPoint(4, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);
        ASSERT_EQ(1, actual.GetX()) << "Least resistance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetX(), actual.GetX()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLocRec_ReturnsLeastResistanceX_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 2, 1);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(1, 0, 3, 1);
        FPoint givenLocation = FPoint(-7, 1);
        FPoint expectedOverlap = FPoint(1, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);
        ASSERT_EQ(1, actual.GetX()) << "Least resistance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetX(), actual.GetX());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLocRec_ReturnsTheDifferenceInPreviousLocationY_WhenLeastResitanceWouldDictateOtherwise)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 1, 2);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 1, 1, 3);
        FPoint givenLocation = FPoint(1, 7);
        FPoint expectedOverlap = FPoint(1, 4);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);
        ASSERT_EQ(1, actual.GetY()) << "Least resistance setup was not correct.";
        ASSERT_NE(expectedOverlap.GetY(), actual.GetY()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }

    TEST_F(RectangleIntTests, OverlapAmountWithLocRec_ReturnsLeastResistanceY_WhenDirectionImpliesItWouldBeTheCase)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // X O Y Y - - - -
        // X -> m_testRectangle
        // O -> overlap
        // Y -> m_otherTestRectangle
        // The path of least resistance is 1 (move to the left)
        // however say test rec moved from the right, it would need to move
        // 4 to the right to not overlap - this is the test.
        // We are giving a position to the left so it should move 1 to the left.

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 1, 2);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 1, 1, 3);
        FPoint givenLocation = FPoint(1, -7);
        FPoint expectedOverlap = FPoint(1, 1);

        // Check the least resistance path
        FPoint actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal);
        ASSERT_EQ(1, actual.GetY()) << "Least resistance setup was not correct.";
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY()) << "Least resistance setup was not correct.";

        // Act
        actual = m_testRectangle->OverlapAmount(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedOverlap.GetY(), actual.GetY());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap With Location
    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocation_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(0, 1);
        float expectedLeft = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocation_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(7, 1);
        float expectedLeft = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocation_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 0);
        int expectedTop = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocation_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 7);
        int expectedTop = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region GetNewLocationToNotOverlap With Location
    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocationRec_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(0, 1);
        float expectedLeft = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocationRec_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(7, 1);
        float expectedLeft = 6;

        // Act
        FVector2D actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, actual.GetX());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocationRec_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 0);
        int expectedTop = 2;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }

    TEST_F(RectangleIntTests, GetNewLocationToNotOverlapWithLocationRec_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 7);
        int expectedTop = 6;

        // Act
        FPoint actual = m_testRectangle->GetNewLocationToNotOverlap(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, actual.GetY());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf With Location
    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocation_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(0, 1);
        int expectedLeft = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocation_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(7, 1);
        int expectedLeft = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocation_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 0);
        int expectedTop = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocation_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 7);
        int expectedTop = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangle, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }
#pragma endregion

#pragma region MoveOutOfOverlapRangeOf With Location
    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocationRec_MovesToTheLeftByOverlap_WhenLocationGivenIsToTheLeft)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(0, 1);
        int expectedLeft = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocationRec_MovesToTheRightByOverlap_WhenLocationGivenIsToTheRight)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(3, 0, 3, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(5, 0, 1, 10);
        FPoint givenLocation = FPoint(7, 1);
        int expectedLeft = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedLeft, m_testRectangle->GetLeft());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocationRec_MovesAboveByOverlap_WhenLocationGivenIsToTheAbove)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // L - - X X O - -
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 0);
        int expectedTop = 2;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }

    TEST_F(RectangleIntTests, MoveOutOfOverlapRangeOfWithLocationRec_MovesBelowByOverlap_WhenLocationGivenIsBelow)
    {
        // Setup
        // 0 1 2 3 4 5 6 7
        // - - - X X O - L
        // X -> m_testRectangle
        // O -> overlap
        // L -> Previous Location
        // Note the only thing changed from previous test is the location!

        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 3, 10, 3);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 5, 10, 1);
        FPoint givenLocation = FPoint(1, 7);
        int expectedTop = 6;

        // Act
        m_testRectangle->MoveOutOfOverlapRangeOf(*m_otherTestRectangleOriginal, givenLocation);

        // Assert
        ASSERT_EQ(expectedTop, m_testRectangle->GetTop());
    }
#pragma endregion

#pragma region CloestPointTo
    TEST_F(RectangleIntTests, CloestPointTo_MatchesY_WhenToTheLeftOrRight)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationLeft = FPoint(-5, 7);
        FPoint givenLocationRight = FPoint(12, 5);

        // Act
        FPoint actualLeft = m_testRectangle->ClosestPointTo(givenLocationLeft);
        FPoint actualRight = m_testRectangle->ClosestPointTo(givenLocationRight);

        // Assert
        ASSERT_EQ(givenLocationLeft.GetY(), actualLeft.GetY());
        ASSERT_EQ(givenLocationRight.GetY(), actualRight.GetY());
    }

    TEST_F(RectangleIntTests, CloestPointTo_MatchesXLeft_WhenToTheLeft)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationLeft = FPoint(-5, 7);

        // Act
        FPoint actualLeft = m_testRectangle->ClosestPointTo(givenLocationLeft);

        // Assert
        ASSERT_EQ(m_testRectangle->GetLeft(), actualLeft.GetX());
    }

    TEST_F(RectangleIntTests, CloestPointTo_MatchesXRight_WhenToTheRight)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationRight = FPoint(12, 5);

        // Act
        FPoint actualRight = m_testRectangle->ClosestPointTo(givenLocationRight);

        // Assert
        ASSERT_EQ(m_testRectangle->GetRight(), actualRight.GetX());
    }

    TEST_F(RectangleIntTests, CloestPointTo_MatchesX_WhenAboveOrBelow)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationAbove = FPoint(7, -5);
        FPoint givenLocationBelow = FPoint(5, 12);

        // Act
        FPoint actualAbove = m_testRectangle->ClosestPointTo(givenLocationAbove);
        FPoint actualBelow = m_testRectangle->ClosestPointTo(givenLocationBelow);

        // Assert
        ASSERT_EQ(givenLocationAbove.GetX(), actualAbove.GetX());
        ASSERT_EQ(givenLocationBelow.GetX(), actualBelow.GetX());
    }

    TEST_F(RectangleIntTests, CloestPointTo_MatchesYAbove_WhenAbove)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationAbove = FPoint(7, -5);

        // Act
        FPoint actualAbove = m_testRectangle->ClosestPointTo(givenLocationAbove);

        // Assert
        ASSERT_EQ(m_testRectangle->GetTop(), actualAbove.GetY());
    }

    TEST_F(RectangleIntTests, CloestPointTo_MatchesYBelow_WhenBelow)
    {
        // Arrange
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        FPoint givenLocationRight = FPoint(5, 12);

        // Act
        FPoint actualBelow = m_testRectangle->ClosestPointTo(givenLocationRight);

        // Assert
        ASSERT_EQ(m_testRectangle->GetBottom(), actualBelow.GetY());
    }
#pragma endregion

#pragma region Operator==
    TEST_F(RectangleIntTests, OperatorEquals_ReturnsTrue_WhenBothSideAreFuntionallyTheSame)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);

        bool actual = *m_testRectangle == *m_otherTestRectangle;

        ASSERT_TRUE(actual);
    }

    TEST_F(RectangleIntTests, OperatorEquals_ReturnsFalse_WhenBothSideAreDifferent)
    {
        m_testRectangle = std::make_shared<RectangleInt>(1, 2, 3, 4);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);

        bool actual = *m_testRectangle == *m_otherTestRectangle;

        ASSERT_FALSE(actual);
    }
#pragma endregion

#pragma region Contains RectangleInt

    TEST_F(RectangleIntTests, Contains_ReturnsTrue_WhenLeftIsEqual)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_TRUE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsToTheLeft)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(1, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsAbove)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 1, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsRight)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(11, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsBelow)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 11, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsTooWide)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 0, 11, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

    TEST_F(RectangleIntTests, Contains_ReturnsFalse_WhenRightIsTooTall)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangle = std::make_shared<RectangleInt>(0, 0, 10, 11);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangle->ToString();
    }

#pragma endregion

#pragma region Contains Rectangle

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsTrue_WhenLeftIsEqual)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_TRUE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsToTheLeft)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(1, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsAbove)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 1, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsRight)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(11, 0, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsBelow)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 11, 10, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsTooWide)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 0, 11, 10);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

    TEST_F(RectangleIntTests, ContainsRectangle_ReturnsFalse_WhenRightIsTooTall)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_otherTestRectangleOriginal = std::make_shared<SuperGameEngine::Rectangle>(0, 0, 10, 11);

        bool actual = m_testRectangle->Contains(*m_otherTestRectangleOriginal);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_otherTestRectangleOriginal->ToString();
    }

#pragma endregion

#pragma region Contains Rectangle

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsTrue_WhenCircleIsWithin)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(5, 5, 5);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_TRUE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsFalse_WhenCircleIsToTheLeft)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(4, 5, 5);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsFalse_WhenCircleIsToTheRight)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(6, 5, 5);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsFalse_WhenCircleIsAbove)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(5, 4, 5);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsFalse_WhenCircleIsBelow)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(5, 6, 5);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

    TEST_F(RectangleIntTests, ContainsCircle_ReturnsFalse_WhenCircleIsTooBig)
    {
        m_testRectangle = std::make_shared<RectangleInt>(0, 0, 10, 10);
        m_testCircle = std::make_shared<Circle>(5, 6, 6);

        bool actual = m_testRectangle->Contains(*m_testCircle);

        ASSERT_FALSE(actual) << "Left:" << m_testRectangle->ToString() << " Right: " << m_testCircle->ToString();
    }

#pragma endregion

}