#pragma once
#include "../GamePackage/GamePackage/FileSystem/PackageFileSystemFile.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace SuperGameEngineTests_Mocks
{
    class PackageFileSystemFileMock : public FatedQuestLibraries::PackageFileSystemFile
    {
    public:
        MOCK_METHOD(bool, Exists, (const std::string& path), (const, override));
        MOCK_METHOD(std::string, ReadFileContents, (const std::string& filepath), (const, override));
        MOCK_METHOD(std::vector<std::string>, ReadFileContentsByLine, (const std::string& filepath), (const, override));
        MOCK_METHOD(std::vector<unsigned char>, ReadFileContentsExplicitly, (const std::string& filepath), (const, override));
    };
}