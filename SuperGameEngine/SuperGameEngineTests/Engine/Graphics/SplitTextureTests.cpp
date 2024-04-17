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
            //Texture* t = nullptr;
            std::shared_ptr<SuperTexture> super = std::make_shared<MockSuperTexture>();
            m_splitTexture = new SplitTexture();
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

    TEST_F(SplitTextureTests, GetSplits_IsEmpty_OnConstruction)
    {
        int expected = 0;

        //std::vector<Rectangle> actual = m_splitTexture->GetSplits();

        //ASSERT_EQ(expected, actual.size());
    }
}