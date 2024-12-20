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
}