#pragma once
#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Graphics/SplitTexture.h"
#include "../../../SuperGameEngine/Engine/Graphics/SuperTexture.h"
#include "../../../SuperGameEngine/Structural/Spatial/Area/RectangleInt.h"
#include "MockSuperTexture.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
using namespace SuperGameEngineTests;

namespace SuperGameEngineTests_Engine_Graphics
{
    class SplitTextureTests : public ::testing::Test
    {
    public:
        SplitTextureTests()
        {
        }

    protected:

        std::shared_ptr<MockSuperTexture> m_mockSuperTexture;
        std::shared_ptr<SplitTexture> m_splitTexture;

        void SetUp() override
        {
            m_mockSuperTexture = std::make_shared<MockSuperTexture>();

            FPoint validSize = FPoint(100, 100);
            EXPECT_CALL(*m_mockSuperTexture, Size())
                .WillRepeatedly(Return(validSize));

            m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        }

        void TearDown() override
        {
            // Occasially tests fail due to these shared
            // not being found. This reset kicks the garbadge collector
            // into gear.
            m_mockSuperTexture.reset();
            m_splitTexture.reset();
        }
    };

#pragma region GetSplits
    TEST_F(SplitTextureTests, GetSplits_IsEmpty_OnConstruction)
    {
        int expected = 0;

        std::vector<RectangleInt> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(expected, actual.size());
    }

    TEST_F(SplitTextureTests, GetSplits_IsOne_WhenGivenSplit)
    {
        int expected = 1;
        RectangleInt given = RectangleInt(0, 0, 0, 0);
        m_splitTexture->AddSplit(given);

        std::vector<RectangleInt> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(expected, actual.size());
    }

    TEST_F(SplitTextureTests, GetSplits_ReturnsSameAsGiven_WhenAddIsGivenASplit)
    {
        int expected = 1;
        RectangleInt given = RectangleInt(1, 2, 3, 4);
        m_splitTexture->AddSplit(given);

        std::vector<RectangleInt> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(given, actual[0]);
    }
#pragma endregion

#pragma region AddSplit
    TEST_F(SplitTextureTests, AddSplit_ReturnsTrue_WhenSplitIsOnTheTexture)
    {
        // Arrange
        FPoint givenSize = FPoint(10, 10);
        RectangleInt givenSplit = RectangleInt(1, 1, 2, 2);
        m_splitTexture->AddSplit(givenSplit);

        EXPECT_CALL(*m_mockSuperTexture, Size())
            .WillRepeatedly(Return(givenSize));

        // Act
        m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        bool actual = m_splitTexture->AddSplit(givenSplit);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(SplitTextureTests, AddSplit_ReturnsFalse_WhenSplitIsOffTheTexture)
    {
        // Arrange
        FPoint givenSize = FPoint(10, 10);
        RectangleInt givenSplit = RectangleInt(1, 1, 20, 20);
        EXPECT_CALL(*m_mockSuperTexture, Size())
            .WillRepeatedly(Return(givenSize));

        // Act
        m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        bool actual = m_splitTexture->AddSplit(givenSplit);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(SplitTextureTests, AddSplit_ReturnsFalse_WhenSplitBeginsBeforeTextureDoes)
    {
        // Arrange
        FPoint givenSize = FPoint(10, 10);
        RectangleInt givenSplitX = RectangleInt(-1, 1, 1, 1);
        RectangleInt givenSplitY = RectangleInt(1, -1, 1, 1);
        EXPECT_CALL(*m_mockSuperTexture, Size())
            .WillRepeatedly(Return(givenSize));

        // Act
        m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        bool actual = m_splitTexture->AddSplit(givenSplitX);
        bool actual2 = m_splitTexture->AddSplit(givenSplitY);

        // Assert
        ASSERT_FALSE(actual);
        ASSERT_FALSE(actual2);
    }

    TEST_F(SplitTextureTests, AddSplit_ReturnsFalse_WhenSplitBeginsAfterTextureDoes)
    {
        // Arrange
        FPoint givenSize = FPoint(10, 10);
        RectangleInt givenSplitX = RectangleInt(10, 1, 1, 1);
        RectangleInt givenSplitY = RectangleInt(1, 10, 1, 1);
        EXPECT_CALL(*m_mockSuperTexture, Size())
            .WillRepeatedly(Return(givenSize));

        // Act
        m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        bool actual = m_splitTexture->AddSplit(givenSplitX);
        bool actual2 = m_splitTexture->AddSplit(givenSplitY);

        // Assert
        ASSERT_FALSE(actual);
        ASSERT_FALSE(actual2);
    }

    TEST_F(SplitTextureTests, AddSplit_DoesNotAddSplit_WhenFalse)
    {
        // Arrange
        FPoint givenSize = FPoint(10, 10);
        RectangleInt givenSplit = RectangleInt(10, 1, 2, 2);
        m_splitTexture->AddSplit(givenSplit);

        EXPECT_CALL(*m_mockSuperTexture, Size())
            .WillRepeatedly(Return(givenSize));

        // Act
        m_splitTexture = std::make_shared<SplitTexture>(m_mockSuperTexture);
        bool actual = m_splitTexture->AddSplit(givenSplit);

        // Assert
        std::vector<RectangleInt> splits = m_splitTexture->GetSplits();
        ASSERT_EQ(0, splits.size());
    }
#pragma endregion

#pragma region Draw
    TEST_F(SplitTextureTests, Draw_UsesTheLocationOfTheSplit_WhenGivenASplitNumber)
    {
        // Arrange
        int expectedSplit = 0;

        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);
        RectangleInt givenTextureLocation = RectangleInt(1, 2, 3, 4);
        m_splitTexture->AddSplit(givenTextureLocation);

        // Assert
        EXPECT_CALL(*m_mockSuperTexture, Draw(givenTextureLocation, validLocation))
            .Times(AtLeast(1));

        // Act
        m_splitTexture->Draw(expectedSplit, validLocation);
    }

    TEST_F(SplitTextureTests, Draw_UsesTheCorrectSplit_WhenManyAreAdded)
    {
        // Arrange
        int expectedSplit = 2;
        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);

        RectangleInt notValidSplit = RectangleInt(2, 2, 3, 4);
        m_splitTexture->AddSplit(notValidSplit);
        RectangleInt notValidSplit2 = RectangleInt(2, 4, 3, 4);
        m_splitTexture->AddSplit(notValidSplit2);

        // Index 2
        RectangleInt givenTextureLocation = RectangleInt(1, 2, 3, 4);
        m_splitTexture->AddSplit(givenTextureLocation);

        RectangleInt notValidSplit3 = RectangleInt(2, 3, 3, 4);
        m_splitTexture->AddSplit(notValidSplit3);


        // Assert
        EXPECT_CALL(*m_mockSuperTexture, Draw(givenTextureLocation, validLocation))
            .Times(AtLeast(1));

        // Act
        m_splitTexture->Draw(expectedSplit, validLocation);
    }

    TEST_F(SplitTextureTests, Draw_DoesNotDrawOrFail_WhenGivenValidNumberButNoSplit)
    {
        // Arrange
        int givenSplit = 0;
        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);

        // Assert
        EXPECT_CALL(*m_mockSuperTexture, Draw()).Times(0);

        // Act
        m_splitTexture->Draw(givenSplit, validLocation);
    }

    TEST_F(SplitTextureTests, Draw_DoesNotDrawOrFail_WhenThereAreSomeSplitsButNumberIsTooBig)
    {
        // Arrange
        int expectedSplit = 1;

        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);
        RectangleInt givenTextureLocation = RectangleInt(1, 2, 3, 4);
        m_splitTexture->AddSplit(givenTextureLocation);

        // Assert
        EXPECT_CALL(*m_mockSuperTexture, Draw()).Times(0);

        // Act
        m_splitTexture->Draw(expectedSplit, validLocation);
    }

    TEST_F(SplitTextureTests, Draw_DoesNotDrawOrFail_WhenSplitValueIsTooToBeValid)
    {
        // Arrange
        int givenSplit = -1;
        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);

        // Assert
        EXPECT_CALL(*m_mockSuperTexture, Draw()).Times(0);

        // Act
        m_splitTexture->Draw(givenSplit, validLocation);
    }
#pragma endregion Draw
}