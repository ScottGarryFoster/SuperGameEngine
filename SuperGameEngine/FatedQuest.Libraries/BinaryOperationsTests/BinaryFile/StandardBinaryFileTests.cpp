#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryFile/StandardBinaryFile.h"

using namespace BinaryOperations;

namespace BinaryOperations_StandardBinaryFileTests
{
    class StandardBinaryFileTests : public ::testing::Test
    {
    public:
        StandardBinaryFileTests()
        {
        }

    protected:

        std::shared_ptr<BinaryFile> m_binaryFile;
        std::shared_ptr<BinaryFile> m_binaryFileSecond;

        void SetUp() override
        {
            m_binaryFile = std::make_shared<StandardBinaryFile>();
            m_binaryFileSecond = std::make_shared<StandardBinaryFile>();
        }

        void TearDown() override
        {
            m_binaryFile.reset();
            m_binaryFileSecond.reset();
        }

        std::string GetFirstString(const std::string& binary)
        {
            if (binary == "")
            {
                return "";
            }

            std::istringstream iss(binary, std::ios::binary);

            size_t textLength;
            iss.read(reinterpret_cast<char*>(&textLength), sizeof(textLength));

            std::string returnString = "";
            returnString.resize(textLength);
            iss.read(&returnString[0], textLength);
            
            return returnString;
        }
    };

    TEST_F(StandardBinaryFileTests, TryGetInt_ReturnsDefault_WhenAddIsNotCalled)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 3454;

        // Act
        int actual = m_binaryFile->TryGetInt(givenKey, expected);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryFileTests, TryGetInt_ReturnsGiven_WhenValueSetAndGiven)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 1234;
        int defaultValue = 5678;

        m_binaryFile->AddInt(givenKey);
        m_binaryFile->SetInt(givenKey, expected);

        // Act
        int actual = m_binaryFile->TryGetInt(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryFileTests, TryGetInt_ReturnsGiven_WhenMultipleValuesGiven)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 1234;
        int defaultValue = 5678;

        m_binaryFile->AddInt("dummyKey");
        m_binaryFile->SetInt("dummyKey", 9999);

        m_binaryFile->AddInt(givenKey);
        m_binaryFile->SetInt(givenKey, expected);

        m_binaryFile->AddInt("dummyKey2");
        m_binaryFile->SetInt("dummyKey2", 8888);

        // Act
        int actual = m_binaryFile->TryGetInt(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    /// <summary>
    /// The purpose of this test is to ensure we are actually using a binary
    /// format. Otherwise export and import could be just text which defeats the
    /// point a little bit.
    /// </summary>
    TEST_F(StandardBinaryFileTests, ExportBinaryData_ReturnsAStreamWithTheFirstWordContainingBinaryFile)
    {
        // Arrange
        std::string expected = "BinaryFile_V1.0.0";

        // Act
        const std::string actual = m_binaryFile->ExportBinaryData();

        // Assert
        std::string firstString = GetFirstString(actual);
        ASSERT_EQ(expected, firstString);
    }

    TEST_F(StandardBinaryFileTests, TryGetInt_ReturnsValue_WhenExportedWithDataAndImportedIntoFreshVersion)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 1234;
        int defaultValue = 5678;

        const std::string data = m_binaryFile->ExportBinaryData();
        m_binaryFileSecond->ImportBinaryData(data);

        // Act
        int actual = m_binaryFileSecond->TryGetInt(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }
}