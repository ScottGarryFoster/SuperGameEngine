#include "../../GamePackage/GamePackage/GamePackageFileSystemDirectory.h"
#include "../../GamePackage/GamePackage/PackageFiles.h"
#include "../../StandardOperations/AllReferences.h"
#include "Stub/StubPackageFile.h"
#include <memory>

#include <gtest/gtest.h>


using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    class GamePackageFileSystemDirectoryTests : public ::testing::Test
    {
    public:
        std::shared_ptr<PackageFiles> m_packageFiles;
        std::shared_ptr<GamePackageFileSystemDirectory> m_testClass;
        GamePackageFileSystemDirectoryTests()
        {

        }

    protected:

        void SetUp() override
        {
            m_packageFiles = std::make_shared<PackageFiles>();
            m_testClass = std::make_shared<GamePackageFileSystemDirectory>(m_packageFiles);
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

    TEST_F(GamePackageFileSystemDirectoryTests, Exists_ReturnsTrue_WhenGiven)
    {
        // Arrange
        std::string givenPath = "Folder1/filename.txt";
        std::string givenDirectory = "Folder1";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenDirectory);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(GamePackageFileSystemDirectoryTests, Exists_ReturnsFalse_WhenGivenNotGiven)
    {
        // Arrange
        std::string givenPath = "Folder2/filename.txt";
        std::string givenDirectory = "Folder1";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenDirectory);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(GamePackageFileSystemDirectoryTests, Exists_ReturnsTrue_WhenGivenButEachPathIsNotSanitised)
    {
        // Arrange
        std::string givenPath = "Folder1\\FOLDER2\\\\Folder3/filename.txt";
        std::string givenDirectory = "FOLDER1/Folder2\\Folder3";

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        bool actual = m_testClass->Exists(givenDirectory);

        // Assert
        ASSERT_TRUE(actual);
    }

#pragma endregion

#pragma region GetFiles

    TEST_F(GamePackageFileSystemDirectoryTests, GetFiles_ReturnsFilenames_WhenGivenManyFilesInADirectory)
    {
        // Arrange
        std::string givenPath = "Folder1/filename.txt";
        std::string givenPath2 = "Folder1/filename2.txt";
        std::string givenPath3 = "Folder1/filename3.txt";
        std::string givenDirectory = "Folder1";
        std::vector<std::string> expected{ "filename.txt", "filename2.txt", "filename3.txt" };

        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::shared_ptr<StubPackageFile> packageFile2 = MockPackageFilepath(givenPath2);
        std::shared_ptr<StubPackageFile> packageFile3 = MockPackageFilepath(givenPath3);
        std::vector<std::shared_ptr<PackageFile>> files = { packageFile, packageFile2, packageFile3 };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::vector<std::string> actual = m_testClass->GetFiles(givenDirectory);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(GamePackageFileSystemDirectoryTests, GetFiles_DoesReturnFile_WhenItIsInAnotherDirectory)
    {
        // Arrange
        std::string unexpectedPath = "Folder2/unexpected.txt";
        std::string givenPath = "Folder1/filename.txt";
        std::string givenPath2 = "Folder1/filename2.txt";
        std::string givenPath3 = "Folder1/filename3.txt";
        std::string givenDirectory = "Folder1";
        std::vector<std::string> expected{ "filename.txt", "filename2.txt", "filename3.txt" };

        std::shared_ptr<StubPackageFile> unexpectedFile = MockPackageFilepath(unexpectedPath);
        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::shared_ptr<StubPackageFile> packageFile2 = MockPackageFilepath(givenPath2);
        std::shared_ptr<StubPackageFile> packageFile3 = MockPackageFilepath(givenPath3);
        std::vector<std::shared_ptr<PackageFile>> files = 
            { unexpectedFile, packageFile, packageFile2, packageFile3 };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::vector<std::string> actual = m_testClass->GetFiles(givenDirectory);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(GamePackageFileSystemDirectoryTests, GetFiles_DoesReturnFile_WhenItIsInASubDirectory)
    {
        // Arrange
        std::string unexpectedPath = "Folder1/SubFolder/unexpected.txt";
        std::string givenPath = "Folder1/filename.txt";
        std::string givenPath2 = "Folder1/filename2.txt";
        std::string givenPath3 = "Folder1/filename3.txt";
        std::string givenDirectory = "Folder1";
        std::vector<std::string> expected{ "filename.txt", "filename2.txt", "filename3.txt" };

        std::shared_ptr<StubPackageFile> unexpectedFile = MockPackageFilepath(unexpectedPath);
        std::shared_ptr<StubPackageFile> packageFile = MockPackageFilepath(givenPath);
        std::shared_ptr<StubPackageFile> packageFile2 = MockPackageFilepath(givenPath2);
        std::shared_ptr<StubPackageFile> packageFile3 = MockPackageFilepath(givenPath3);
        std::vector<std::shared_ptr<PackageFile>> files =
        { unexpectedFile, packageFile, packageFile2, packageFile3 };
        m_packageFiles->SetFiles(files);
        m_testClass->Refresh();

        // Act
        std::vector<std::string> actual = m_testClass->GetFiles(givenDirectory);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

}