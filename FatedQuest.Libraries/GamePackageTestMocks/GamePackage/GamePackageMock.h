#pragma once
#include "../GamePackage/GamePackage/GamePackage.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace SuperGameEngineTests_Mocks
{
    class GamePackageMock : public FatedQuestLibraries::GamePackage
    {
        public:
            MOCK_METHOD(const std::shared_ptr<FatedQuestLibraries::PackageFileSystemFile>, File, (), (const, override));
            MOCK_METHOD(const std::shared_ptr<FatedQuestLibraries::PackageFileSystemDirectory>, Directory, (), (const, override));
            MOCK_METHOD(bool, Reload, (), (const, override));
    };  
}