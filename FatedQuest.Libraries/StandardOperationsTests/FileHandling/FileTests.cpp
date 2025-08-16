#include "../../StandardOperations/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardOperations_FileHandling
{
    class FileTests : public ::testing::Test
    {
    public:

        FileTests()
        {
        }

    protected:

        void SetUp() override
        {

        }

        void TearDown() override
        {

        }

    };

#pragma region Sanitize

    TEST_F(FileTests, Sanitize_ReturnsCorrectly_WhenThreeBackslashesGiven)
    {
        // Arrange
        std::string given = "text\\\\\\more";
        std::string expected = "text\\more";

        // Act
        std::string actual = File::Sanitize(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, Sanitize_ReturnsCorrectly_WhenForwardSlashesAreGiven)
    {
        // Arrange
        std::string given = "text///more";
        std::string expected = "text\\more";

        // Act
        std::string actual = File::Sanitize(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, Sanitize_ReturnsCorrectly_WhenCapitialLettersGiven)
    {
        // Arrange
        std::string given = "TeXt.tXT";
        std::string expected = "text.txt";

        // Act
        std::string actual = File::Sanitize(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region RemoveAllExtensions

    TEST_F(FileTests, RemoveAllExtensions_ReturnsFilepathWithoutExtensions_WhenGivenFilepathWithASingleExtension)
    {
        // Arrange
        std::string given = "folder1\\filename.txt";
        std::string expected = "folder1\\filename";

        // Act
        std::string actual = File::RemoveAllExtensions(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, RemoveAllExtensions_ReturnsFilepathWithoutExtensions_WhenGivenFilepathWithMultipleExtensions)
    {
        // Arrange
        std::string given = "folder2\\filename.txt.gz";
        std::string expected = "folder2\\filename";

        // Act
        std::string actual = File::RemoveAllExtensions(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, RemoveAllExtensions_ReturnsGiven_WhenPathDoesNotHaveExtensions)
    {
        // Arrange
        std::string given = "folder3\\filename";
        std::string expected = "folder3\\filename";

        // Act
        std::string actual = File::RemoveAllExtensions(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region RemoveLastExtension

    TEST_F(FileTests, RemoveLastExtension_ReturnsWithoutExtension_WhenGivenSingleExtension)
    {
        // Arrange
        std::string given = "folder1\\filename.txt";
        std::string expected = "folder1\\filename";

        // Act
        std::string actual = File::RemoveLastExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, RemoveLastExtension_ReturnsWithFirstExtension_WhenGivenTwoExtensions)
    {
        // Arrange
        std::string given = "folder2\\filename.txt.gz";
        std::string expected = "folder2\\filename.txt";

        // Act
        std::string actual = File::RemoveLastExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, RemoveLastExtension_ReturnsGiven_WhenPathDoesNotHaveExtensions)
    {
        // Arrange
        std::string given = "folder3\\filename";
        std::string expected = "folder3\\filename";

        // Act
        std::string actual = File::RemoveLastExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region GetExtension

    TEST_F(FileTests, GetExtension_ReturnsTxt_WhenThatIsTheLastExtension)
    {
        // Arrange
        std::string given = "folder1\\filename.txt";
        std::string expected = ".txt";

        // Act
        std::string actual = File::GetExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, GetExtension_ReturnsGz_WhenTxtAndGzAreTheExtensions)
    {
        // Arrange
        std::string given = "folder2\\filename.txt.gz";
        std::string expected = ".gz";

        // Act
        std::string actual = File::GetExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(FileTests, GetExtension_ReturnsBlank_WhenThereAreNoExtensions)
    {
        // Arrange
        std::string given = "folder3\\filename";
        std::string expected = {};

        // Act
        std::string actual = File::GetExtension(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion
}