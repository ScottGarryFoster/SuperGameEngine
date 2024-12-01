#include "../../StandardOperations/AllReferences.h"
#include "../../StandardObjects/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardObjects_Position
{
    class FPointTests : public ::testing::Test
    {
    public:
        std::shared_ptr<SuperXMLDocument> m_testClass;

        FPointTests()
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

    TEST_F(FPointTests, OnConstruction_GetXandGetYReturn0)
    {
        // Arrange
        FPoint testClass;
        int expectedX = 0;
        int expectedY = 0;

        // Act
        int actualX = testClass.GetX();
        int actualY = testClass.GetY();

        // Assert
        ASSERT_EQ(expectedX, actualX);
        ASSERT_EQ(expectedY, actualY);
    }

    TEST_F(FPointTests, SetX_ReturnsGiven_WhenGivenValue)
    {
        // Arrange
        FPoint testClass;
        int given = 3;

        // Act
        testClass.SetX(given);

        // Assert
        int actualX = testClass.GetX();
        ASSERT_EQ(given, actualX);
    }

    TEST_F(FPointTests, SetY_ReturnsGiven_WhenGivenValue)
    {
        // Arrange
        FPoint testClass;
        int given = 3;

        // Act
        testClass.SetY(given);

        // Assert
        int actualY = testClass.GetY();
        ASSERT_EQ(given, actualY);
    }

    TEST_F(FPointTests, SetXY_ReturnsGiven_WhenGivenValue)
    {
        // Arrange
        FPoint testClass;
        int givenX = 6;
        int givenY = 11;

        // Act
        testClass.SetXYValue(givenX, givenY);

        // Assert
        int actualX = testClass.GetX();
        int actualY = testClass.GetY();
        ASSERT_EQ(givenX, actualX);
        ASSERT_EQ(givenY, actualY);
    }

    TEST_F(FPointTests, OnConstruction_GivenXYAreReturned_WhenGetXYAreChecked)
    {
        // Arrange
        int givenX = 65;
        int givenY = 23;

        // Act
        FPoint testClass(givenX, givenY);

        // Assert
        int actualX = testClass.GetX();
        int actualY = testClass.GetY();
        ASSERT_EQ(givenX, actualX);
        ASSERT_EQ(givenY, actualY);
    }

    TEST_F(FPointTests, PlusReturn_AddsTwoPoints)
    {
        // Arrange
        FPoint firstPoint(4, 10);
        FPoint secondPoint(11, 23);
        FPoint expectedPoint(15, 33);

        // Act
        FPoint actual = firstPoint + secondPoint;

        // Assert
        ASSERT_EQ(expectedPoint.GetX(), actual.GetX());
        ASSERT_EQ(expectedPoint.GetY(), actual.GetY());
    }

    TEST_F(FPointTests, PlusEquals_AddsTwoPoints)
    {
        // Arrange
        FPoint firstPoint(4, 10);
        FPoint secondPoint(11, 23);
        FPoint expectedPoint(15, 33);

        // Act
        firstPoint += secondPoint;

        // Assert
        ASSERT_EQ(expectedPoint.GetX(), firstPoint.GetX());
        ASSERT_EQ(expectedPoint.GetY(), firstPoint.GetY());
    }

    TEST_F(FPointTests, Equals_ReturnsTrue_WhenTwoPointsHaveTheSameXandY)
    {
        // Arrange
        FPoint firstPoint(4, 10);
        FPoint secondPoint(4, 10);

        // Act
        bool actual = firstPoint == secondPoint;

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(FPointTests, Equals_ReturnsFalse_WhenTwoPointsHaveTheDifferentXandTheSameY)
    {
        // Arrange
        FPoint firstPoint(4, 10);
        FPoint secondPoint(11, 10);

        // Act
        bool actual = firstPoint == secondPoint;

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(FPointTests, Equals_ReturnsFalse_WhenTwoPointsHaveTheSameXandDifferentY)
    {
        // Arrange
        FPoint firstPoint(4, 10);
        FPoint secondPoint(4, -5);

        // Act
        bool actual = firstPoint == secondPoint;

        // Assert
        ASSERT_FALSE(actual);
    }
}