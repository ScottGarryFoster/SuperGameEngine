#pragma once
#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Graphics/SplitTexture.h"
#include "../../../SuperGameEngine/Engine/Graphics/SuperTexture.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;

namespace SuperGameEngine_Engine_Graphics
{
    class MockSuperTexture : public SuperTexture {
    public:
        MOCK_METHOD(void, Draw, (), (override));
        MOCK_METHOD(void, Draw, (const FPoint& location), (override));
        MOCK_METHOD(void, Draw, (FPoint location, FPoint size), (override));
        MOCK_METHOD(bool, RepresentSameImage, (SuperTexture* texture), (override));
        MOCK_METHOD(bool, RepresentSameImage, (FString filePath), (override));
        MOCK_METHOD(FPoint, Size, (), (const, override));
    };

    class SplitTextureTests : public ::testing::Test
    {
    public:
        SplitTextureTests()
        {
            std::shared_ptr<SuperTexture> super = std::make_shared<MockSuperTexture>();
            m_splitTexture = new SplitTexture(super);
        }

    protected:

        SplitTexture* m_splitTexture;

        void SetUp() override
        {
        }

        void TearDown() override
        {
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
}