#include "../../GamePackage/GamePackage/FileSystem/GamePackageFileSystem.h"
#include "../../StandardOperations/AllReferences.h"
#include <memory>

#include <gtest/gtest.h>

#include "../../GamePackage/GamePackage/FileSystem/PackageFileSystemFile.h"
#include "Stub/StubPackageFile.h"


using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    class GamePackageFileSystemTests : public ::testing::Test
    {
    public:
        std::shared_ptr<GamePackageFileSystem> m_testClass;
        GamePackageFileSystemTests()
        {

        }

    protected:

        void SetUp() override
        {
            m_testClass = std::make_shared<GamePackageFileSystem>();
        }

        void TearDown() override
        {

        }

        std::shared_ptr<StubPackageFile> MockPackageFilepath(const std::string& path)
        {
            auto givenFile = std::make_shared<StubPackageFile>();
            givenFile->m_path = path;
            return givenFile;
        }

        std::shared_ptr<StubPackageFile> MockPackageFile(const std::string& path, const std::string contents)
        {
            auto givenFile = std::make_shared<StubPackageFile>();
            givenFile->m_path = path;
            givenFile->m_fileContents = contents;
            givenFile->m_fileContentsByLine = StringHelpers::Split(contents, "\n");
            return givenFile;
        }
    };

    TEST_F(GamePackageFileSystemTests, OnConstruction_FileExistsIsFalse)
    {
        // Arrange
        std::string testedPath = "test2.txt";

        // Act
        bool actual = m_testClass->File()->Exists(testedPath);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(GamePackageFileSystemTests, GiveFiles_CausesFileExistsToReturnTrue_WhenGivenTheSamePath)
    {
        // Arrange
        std::string givenPath = "test.txt";
        auto givenOrigin = PackageFileOrigin::Unarchived;

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);

        std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>> givenFiles
        { std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>(givenOrigin, packageFile) };

        // Act
        m_testClass->GiveFiles(givenFiles);
        bool actual = m_testClass->File()->Exists(givenPath);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(GamePackageFileSystemTests, GiveFiles_CausesFileExistsToReturnFalse_WhenNotGivenTheSamePage)
    {
        // Arrange
        std::string testedPath = "test2.txt";
        std::string givenPath = "test.txt";
        auto givenOrigin = PackageFileOrigin::Unarchived;

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);

        std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>> givenFiles
        { std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>(givenOrigin, packageFile) };

        // Act
        m_testClass->GiveFiles(givenFiles);
        bool actual = m_testClass->File()->Exists(testedPath);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(GamePackageFileSystemTests, GiveFiles_CausesFileContentsToReturnContents_WhenGivenTheFile)
    {
        // Arrange
        std::string givenPath = "test.txt";
        auto givenOrigin = PackageFileOrigin::Unarchived;
        auto givenContents = "Contents";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(givenPath, givenContents);

        std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>> givenFiles
        { std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>(givenOrigin, packageFile) };

        // Act
        m_testClass->GiveFiles(givenFiles);
        std::string actual = m_testClass->File()->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(givenContents, actual);
    }

    TEST_F(GamePackageFileSystemTests, GiveFiles_PrioritisesUnarchivedFiles_WhenTwoFilesAreGiven)
    {
        // Arrange
        std::string givenPath = "test.txt";
        auto expectedContents = "Contents";
        auto unexpectedContents = "Unexpected";

        std::shared_ptr<StubPackageFile> unarchivedFile = MockPackageFile(givenPath, expectedContents);
        std::shared_ptr<StubPackageFile> archivedFile = MockPackageFile(givenPath, unexpectedContents);

        std::vector<std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>> givenFiles
        { std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>(PackageFileOrigin::Unarchived, unarchivedFile),
          std::pair<PackageFileOrigin, std::shared_ptr<PackageFile>>(PackageFileOrigin::Archived, archivedFile), };

        // Act
        m_testClass->GiveFiles(givenFiles);
        std::string actual = m_testClass->File()->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(expectedContents, actual);
    }
}