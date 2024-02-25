#include "../../../LibraryIncludes.h"
#include "../../../../SuperGameEngine/Structural/Spatial/Area/Rectangle.h"

using namespace SuperGameEngine;
namespace SuperGameEngine_Structural_Spatial_Area
{
    class RectangleTests : public ::testing::Test
    {
    public:
        RectangleTests()
        {
            m_testRectangle = nullptr;
        }

    protected:

        Rectangle* m_testRectangle;

        void SetUp() override
        {

        }

        void TearDown() override
        {
            if (m_testRectangle != nullptr)
            {
                delete m_testRectangle;
            }
        }
    };

    /// <summary>
    /// Creates a basic rectangle for testing.
    /// </summary>
    /// <returns>A Unit 1 by 1 rectangle at (1, 1). </returns>
    Rectangle* CreateBasicRectangle();

#pragma region Construction
    TEST_F(RectangleTests, OnContruction_ReturnsGivenLocation_WhenGivenAsXY)
    {
        float givenX = 6;
        float givenY = 10;
        float validWidthHeight = 1;

        Rectangle* m_testRectangle = new Rectangle(givenX, givenY, validWidthHeight, validWidthHeight);

        ASSERT_EQ(givenX, m_testRectangle->GetLeft());
        ASSERT_EQ(givenY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsWidthHeight)
    {
        float givenWidth = 21;
        float givenHeight = 42;
        float validXY = 1;

        Rectangle* m_testRectangle = new Rectangle(validXY, validXY, givenWidth, givenHeight);

        ASSERT_EQ(givenWidth, m_testRectangle->GetWidth());
        ASSERT_EQ(givenHeight, m_testRectangle->GetHeight());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenLocation_WhenGivenAsSingleLocation)
    {
        float givenXY = 6;
        float validWidthHeight = 1;

        Rectangle* m_testRectangle = new Rectangle(givenXY, validWidthHeight);

        ASSERT_EQ(givenXY, m_testRectangle->GetLeft());
        ASSERT_EQ(givenXY, m_testRectangle->GetTop());
    }

    TEST_F(RectangleTests, OnContruction_ReturnsGivenWidthHeight_WhenGivenAsSingleSize)
    {
        float givenWidthHeight = 21;
        float validXY = 1;

        Rectangle* m_testRectangle = new Rectangle(validXY, givenWidthHeight);

        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetWidth());
        ASSERT_EQ(givenWidthHeight, m_testRectangle->GetHeight());
    }

#pragma endregion

#pragma region SetAndGet
    TEST_F(RectangleTests, GetSetX_ChangesLeftValue_WhenGivenNewValue)
    {
        Rectangle* m_testRectangle = CreateBasicRectangle();
        float givenX = 42;
        ASSERT_NE(m_testRectangle->GetLeft(), givenX) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetX(givenX);
        float actual = m_testRectangle->GetLeft();

        ASSERT_EQ(givenX, actual);
    }

    TEST_F(RectangleTests, GetSetY_ChangesTopValue_WhenGivenNewValue)
    {
        Rectangle* m_testRectangle = CreateBasicRectangle();
        float givenY = 98;
        ASSERT_NE(m_testRectangle->GetTop(), givenY) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetY(givenY);
        float actual = m_testRectangle->GetTop();

        ASSERT_EQ(givenY, actual);
    }

    TEST_F(RectangleTests, GetSetWidth_ChangesWidthValue_WhenGivenNewValue)
    {
        Rectangle* m_testRectangle = CreateBasicRectangle();
        float givenWidth = 100;
        ASSERT_NE(m_testRectangle->GetWidth(), givenWidth) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetWidth(givenWidth);
        float actual = m_testRectangle->GetWidth();

        ASSERT_EQ(givenWidth, actual);
    }

    TEST_F(RectangleTests, GetSetHeight_ChangesHeightValue_WhenGivenNewValue)
    {
        Rectangle* m_testRectangle = CreateBasicRectangle();
        float givenHeight = 21;
        ASSERT_NE(m_testRectangle->GetHeight(), givenHeight) << "Ensure the given is not the original, otherwise test means nothing";

        m_testRectangle->SetHeight(givenHeight);
        float actual = m_testRectangle->GetHeight();

        ASSERT_EQ(givenHeight, actual);
    }

    TEST_F(RectangleTests, SetLocation_ChangesLeftAndTopValue_WhenGivenNewValue)
    {
        Rectangle* m_testRectangle = CreateBasicRectangle();
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
        Rectangle* m_testRectangle = CreateBasicRectangle();
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
        Rectangle* m_testRectangle = CreateBasicRectangle();
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
        Rectangle* m_testRectangle = CreateBasicRectangle();
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
        Rectangle* m_testRectangle = CreateBasicRectangle();
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
        Rectangle* m_testRectangle = CreateBasicRectangle();

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

#pragma region Helper Methods
    Rectangle* CreateBasicRectangle()
    {
        float originalXY = 1;
        float originalWidthHeight = 1;
        return new Rectangle(originalXY, originalWidthHeight);
    }
#pragma endregion
}