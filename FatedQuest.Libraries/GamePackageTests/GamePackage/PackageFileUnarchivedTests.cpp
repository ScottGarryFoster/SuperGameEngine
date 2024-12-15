#include "../../GamePackage/GamePackage/PackageFileUnarchived.h"
#include "../../StandardOperations/AllReferences.h"
#include "Stub/StubPackagePaths.h"
#include <memory>

#include <gtest/gtest.h>


using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    class PackageFileUnarchivedTests : public ::testing::Test
    {
    public:

        std::shared_ptr<StubPackagePaths> m_mockPackagePaths;

        std::string m_tempPath;
        std::string m_productsPath;

        std::vector<std::string> m_tempFiles;

        PackageFileUnarchivedTests()
        {
        }

    public:

    protected:

        void SetUp() override
        {
            m_tempPath = GetTemp();
            m_tempPath += "SuperGameEngine\\Tests\\GamePackage\\PackageFileUnarchived\\Products";

            if (!Directory::CreateDirectories(m_tempPath))
            {
                std::string exception = "Could not create directory " + m_tempPath;
                throw std::exception(exception.c_str());
            }

            m_mockPackagePaths = std::make_shared<StubPackagePaths>();
            m_mockPackagePaths->m_productsDirectory = m_tempPath;
        }

        void TearDown() override
        {
            for (const std::string path : m_tempFiles)
            {
                File::Delete(path);
            }
        }

        static std::string GetTemp()
        {
            std::filesystem::path temp_path = std::filesystem::temp_directory_path();

            return temp_path.string();
        }

        std::string AddTempFile(std::string path, std::string fileContents)
        {
            std::string tempFilepath = GetTemp();
            tempFilepath += "SuperGameEngine\\Tests\\GamePackage\\PackageFileUnarchived\\Products\\";
            tempFilepath += path;

            File::WriteLine(tempFilepath, fileContents);

            m_tempFiles.push_back(tempFilepath);

            return tempFilepath;
        }
    };

    TEST_F(PackageFileUnarchivedTests, Path_ReturnsPath_WhenGivenInConstruction)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);

        std::shared_ptr<PackageFileUnarchived> testClass = 
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::string actual = testClass->Path();

        // Assert
        ASSERT_EQ(givenPath, actual);
    }

    TEST_F(PackageFileUnarchivedTests, ReadFileContents_ReturnsFileContents_WhenGivenFile)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::string actual = testClass->ReadFileContents();

        // Assert
        ASSERT_EQ(contents, actual);
    }

    TEST_F(PackageFileUnarchivedTests, ReadFileContents_ReturnsEmptyString_WhenFileHasNoContents)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);
        AddTempFile(givenPath, "");

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::string actual = testClass->ReadFileContents();

        // Assert
        ASSERT_EQ("", actual);
    }

    TEST_F(PackageFileUnarchivedTests, ReadFileContentsByLine_ReturnsAllLinesOfAFile_WhenMultipleLinesAreGiven)
    {
        // Arrange
        std::string givenPath = "test.txt";
        std::string contents = "Somecontents\nAnotherLine\nAThirdLine";
        auto expected = std::vector<std::string>{ "Somecontents", "AnotherLine", "AThirdLine" };
        std::string fullPath = AddTempFile(givenPath, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::vector<std::string> actual = testClass->ReadFileContentsByLine();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, PathByDirectory_ReturnsEmptyVector_WhenThereAreNoDirectories)
    {
        // Arrange
        std::vector<std::string> expected = {};
        std::string givenPath = "test.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::vector<std::string> actual = testClass->PathByDirectory();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, PathByDirectory_ReturnsAllDirectories_WhenManyDirectoriesAreFound)
    {
        // Arrange
        std::string givenFolder = "folder1\\folder2\\folder3";
        std::vector<std::string> expected = { "folder1", "folder2", "folder3" };
        std::string givenPath = givenFolder + "\\test.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);

        std::string fullDirectory = m_tempPath + "\\" + givenFolder;
        ASSERT_TRUE(Directory::CreateDirectories(fullDirectory));

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::vector<std::string> actual = testClass->PathByDirectory();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, FileName_ReturnsOnlyTheEndFilename_WhenGivenFile)
    {
        // Arrange
        std::string expected = "test1.txt";
        std::string givenFolder = "folder1\\folder2\\folder3";
        std::string givenPath = givenFolder + "\\" + expected;
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(givenPath, contents);

        std::string fullDirectory = m_tempPath + "\\" + givenFolder;
        ASSERT_TRUE(Directory::CreateDirectories(fullDirectory));

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, givenPath);

        // Act
        std::string actual = testClass->FileName();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, FileName_ReturnsTheFileName_WhenFileIsNotInAFolder)
    {
        // Arrange
        std::string expected = "test1.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(expected, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, expected);

        // Act
        std::string actual = testClass->FileName();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, FileName_ReturnsExtention_WhenGivenAFileWithAnExtention)
    {
        // Arrange
        std::string expected = "txt";
        std::string path = "test1.txt";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(expected, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, path);

        // Act
        std::string actual = testClass->Extension();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, FileName_ReturnsTheWholeExtention_WhenGivenAFileWithALongerExtention)
    {
        // Arrange
        std::string expected = "txt.xml";
        std::string path = "test1.txt.xml";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(expected, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, path);

        // Act
        std::string actual = testClass->Extension();

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(PackageFileUnarchivedTests, FileName_ReturnEmptyString_WhenNoExtentionWasGiven)
    {
        // Arrange
        std::string expected = "";
        std::string path = "test1";
        std::string contents = "Somecontents";
        std::string fullPath = AddTempFile(expected, contents);

        std::shared_ptr<PackageFileUnarchived> testClass =
            std::make_shared<PackageFileUnarchived>(m_mockPackagePaths, path);

        // Act
        std::string actual = testClass->Extension();

        // Assert
        ASSERT_EQ(expected, actual);
    }
}