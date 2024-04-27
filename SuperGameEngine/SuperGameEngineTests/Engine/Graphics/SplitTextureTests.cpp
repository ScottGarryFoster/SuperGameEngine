#pragma once
#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Graphics/SplitTexture.h"
#include "../../../SuperGameEngine/Engine/Graphics/SuperTexture.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
using ::testing::AtLeast;

namespace SuperGameEngine_Engine_Graphics
{
    class MockSuperTexture : public SuperTexture {
    public:
        MOCK_METHOD(void, Draw, (), (override));
        MOCK_METHOD(void, Draw, (const FPoint&), (override));
        MOCK_METHOD(void, Draw, (const FPoint&, const FPoint&), (override));
        MOCK_METHOD(bool, RepresentSameImage, (SuperTexture*), (override));
        MOCK_METHOD(bool, RepresentSameImage, (FString), (override));
        MOCK_METHOD(FPoint, Size, (), (const, override));
    };

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

        std::vector<Rectangle> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(expected, actual.size());
    }

    TEST_F(SplitTextureTests, GetSplits_IsOne_WhenGivenSplit)
    {
        int expected = 1;
        Rectangle given = Rectangle(0, 0, 0, 0);
        m_splitTexture->AddSplit(given);

        std::vector<Rectangle> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(expected, actual.size());
    }

    TEST_F(SplitTextureTests, GetSplits_ReturnsSameAsGiven_WhenAddIsGivenASplit)
    {
        int expected = 1;
        Rectangle given = Rectangle(1, 2, 3, 4);
        m_splitTexture->AddSplit(given);

        std::vector<Rectangle> actual = m_splitTexture->GetSplits();

        ASSERT_EQ(given, actual[0]);
    }
#pragma endregion

#pragma region Draw
    TEST_F(SplitTextureTests, Draw_UsesTheLocationOfTheSplit_WhenGivenASplitNumber)
    {
        int expected = 0;
        int givenSplit = 0;
        FPoint validLocation = FPoint(0, 0);

        EXPECT_CALL(*mockSuperTexture, Draw(validLocation, validLocation))
            .Times(AtLeast(1));

        m_splitTexture->Draw(givenSplit, validLocation);
    }
#pragma endregion Draw
}