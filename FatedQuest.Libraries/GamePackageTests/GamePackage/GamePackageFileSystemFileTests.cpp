#include "../../GamePackage/GamePackage/GamePackageFileSystemFile.h"
#include "../../GamePackage/GamePackage/PackageFiles.h"
#include "../../StandardOperations/AllReferences.h"
#include "Stub/StubPackageFile.h"
#include <memory>

#include <gtest/gtest.h>


using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    class GamePackageFileSystemFileTests : public ::testing::Test
    {
    public:
        std::shared_ptr<PackageFiles> m_packageFiles;
        std::shared_ptr<GamePackageFileSystemFile> m_testClass;
        GamePackageFileSystemFileTests()
        {

        }

    protected:

        void SetUp() override
        {
            m_packageFiles = std::make_shared<PackageFiles>();
            m_testClass = std::make_shared<GamePackageFileSystemFile>(m_packageFiles);
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

#pragma region Exists

    TEST_F(GamePackageFileSystemFileTests, Exists_ReturnsTrue_WhenGiven)
    {
        // Arrange
        std::string givenPath = "test.txt";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenPath);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(GamePackageFileSystemFileTests, Exists_ReturnsFalse_WhenPathNotGiven)
    {
        // Arrange
        std::string givenPath = "test2.txt";
        std::string pathInPackageFile = "test.txt";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(pathInPackageFile);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenPath);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(GamePackageFileSystemFileTests, Exists_ReturnsTrue_WhenCapitialisationDoesNotMatchGivenPackageAndGivenToMethod)
    {
        // Arrange
        std::string givenPath = "tEsT.txt";
        std::string pathInPackageFile = "TeSt.txt";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(pathInPackageFile);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenPath);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(GamePackageFileSystemFileTests, Exists_ReturnsTrue_WhenGivenHasDifferentSlashesThanPackage)
    {
        // Arrange
        std::string givenPath = "Folder\\Folder2///Folder3\\tEsT.txt";
        std::string pathInPackageFile = "Folder//Folder2\\Folder3/TeSt.txt";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(pathInPackageFile);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenPath);

        // Assert
        ASSERT_TRUE(actual);
    }

#pragma endregion

#pragma region ReadFileContents

    TEST_F(GamePackageFileSystemFileTests, ReadFileContents_ReturnsGiven_WhenFileExists)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string givenContents = "Contents";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(givenPath, givenContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::string actual = m_testClass->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(givenContents, actual);
    }

    TEST_F(GamePackageFileSystemFileTests, ReadFileContents_DoesNotReturnGiven_WhenFileIsNotGiven)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string packagePath = "package.txt";
        std::string packageContents = "Contents";
        std::string expected = {};

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(packagePath, packageContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::string actual = m_testClass->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region ReadFileContentsByLine

    TEST_F(GamePackageFileSystemFileTests, ReadFileContentsByLine_ReturnsGiven_WhenFileExists)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string givenContents = "Contents\nNextLine";
        std::vector<std::string> expected{"Contents", "NextLine"};

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(givenPath, givenContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::vector<std::string> actual = m_testClass->ReadFileContentsByLine(givenPath);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(GamePackageFileSystemFileTests, ReadFileContentsByLine_DoesNotReturnGiven_WhenFileIsNotGiven2)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string packagePath = "package.txt";
        std::string packageContents = "Contents\nNextLine";
        std::vector<std::string> expected;

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(packagePath, packageContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::vector<std::string> actual = m_testClass->ReadFileContentsByLine(givenPath);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region Refresh

    TEST_F(GamePackageFileSystemFileTests, ReadFileContents_DoesNotReturnFile_WhenRefreshNotCalledAfterUpdatingFile)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string givenContents = "Contents";
        std::string expected = {};

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(givenPath, givenContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);

        // Act
        std::string actual = m_testClass->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(GamePackageFileSystemFileTests, Refresh_CausesReadContentsToFindNewFile_WhenFileAdded)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string givenContents = "Contents";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFile(givenPath, givenContents);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);

        // Act
        m_testClass->Refresh();
        std::string actual = m_testClass->ReadFileContents(givenPath);

        // Assert
        ASSERT_EQ(givenContents, actual);
    }

#pragma endregion

}