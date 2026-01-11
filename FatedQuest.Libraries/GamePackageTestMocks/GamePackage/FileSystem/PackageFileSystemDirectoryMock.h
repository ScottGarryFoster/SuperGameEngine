#pragma once
#include "../GamePackage/GamePackage/FileSystem/PackageFileSystemDirectory.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace SuperGameEngineTests_Mocks
{
    class PackageFileSystemDirectoryMock : public FatedQuestLibraries::PackageFileSystemDirectory
    {
    public:
        MOCK_METHOD(bool, Exists, (const std::string& path), (const, override));
        MOCK_METHOD(std::vector<std::string>, GetFiles, (const std::string& path), (const, override));
        MOCK_METHOD(std::vector<std::string>, ListDirectories, (const std::string& path), (const, override));
        MOCK_METHOD(std::vector<std::string>, ListDirectoryNames, (const std::string& path), (const, override));
    };
}