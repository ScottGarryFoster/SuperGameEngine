#pragma once
#include "../../LibraryIncludes.h"
#include "../../../SuperGameEngine/Engine/Graphics/SuperTexture.h"

using namespace SuperGameEngine;

namespace SuperGameEngineTests
{
    /// <summary>
    /// A GMock version of SuperTexture.
    /// </summary>
    class MockSuperTexture : public SuperTexture
    {
    public:
        MOCK_METHOD(void, Draw, (), (override));
        MOCK_METHOD(void, Draw, (const FPoint&), (override));
        MOCK_METHOD(void, Draw, (const FPoint&, const FPoint&), (override));
        MOCK_METHOD(void, Draw, (const RectangleInt&, const RectangleInt&), (override));
        MOCK_METHOD(bool, RepresentSameImage, (SuperTexture*), (override));
        MOCK_METHOD(bool, RepresentSameImage, (FString), (override));
        MOCK_METHOD(FPoint, Size, (), (const, override));
    };
}