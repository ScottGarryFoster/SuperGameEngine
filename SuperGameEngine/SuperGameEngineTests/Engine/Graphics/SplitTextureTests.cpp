#pragma once
#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Graphics/SplitTexture.h"
#include "../../../SuperGameEngine/Engine/Graphics/SuperTexture.h"
#include "../../../SuperGameEngine/Structural/Spatial/Area/RectangleInt.h"
#include "MockSuperTexture.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
using namespace SuperGameEngineTests;
using ::testing::AtLeast;
using ::testing::_;

namespace SuperGameEngineTests_Engine_Graphics
{
    class SplitTextureTests : public ::testing::Test
    {
    public:
        SplitTextureTests()
        {
            mockSuperTexture = nullptr;
            m_splitTexture = nullptr;
        }

    protected:

        std::shared_ptr<MockSuperTexture> m_mockSuperTexture;
        MockSuperTexture* mockSuperTexture;
        SplitTexture* m_splitTexture;

        void SetUp() override
        {
            m_mockSuperTexture = std::make_shared<MockSuperTexture>();
            mockSuperTexture = m_mockSuperTexture.get();
            m_splitTexture = new SplitTexture(m_mockSuperTexture);
        }

        void TearDown() override
        {
            if (m_splitTexture != nullptr)
            {
                delete m_splitTexture;
            }
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

#pragma region Draw
    TEST_F(SplitTextureTests, Draw_UsesTheLocationOfTheSplit_WhenGivenASplitNumber)
    {
        // Arrange
        int expectedSplit = 0;

        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);
        RectangleInt givenTextureLocation = RectangleInt(1, 2, 3, 4);
        m_splitTexture->AddSplit(givenTextureLocation);

        // Assert
        EXPECT_CALL(*mockSuperTexture, Draw(givenTextureLocation, validLocation))
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
        EXPECT_CALL(*mockSuperTexture, Draw(givenTextureLocation, validLocation))
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
        EXPECT_CALL(*mockSuperTexture, Draw()).Times(0);

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
        EXPECT_CALL(*mockSuperTexture, Draw()).Times(0);

        // Act
        m_splitTexture->Draw(expectedSplit, validLocation);
    }

    TEST_F(SplitTextureTests, Draw_DoesNotDrawOrFail_WhenSplitValueIsTooToBeValid)
    {
        // Arrange
        int givenSplit = -1;
        RectangleInt validLocation = RectangleInt(4, 3, 2, 1);

        // Assert
        EXPECT_CALL(*mockSuperTexture, Draw()).Times(0);

        // Act
        m_splitTexture->Draw(givenSplit, validLocation);
    }
#pragma endregion Draw
}