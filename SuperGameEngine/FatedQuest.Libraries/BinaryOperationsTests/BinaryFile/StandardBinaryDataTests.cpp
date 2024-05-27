#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryFile/StandardBinaryData.h"

using namespace BinaryOperations;

namespace BinaryOperations_StandardBinaryDataTests
{
    class StandardBinaryDataTests : public ::testing::Test
    {
    public:
        StandardBinaryDataTests()
        {
        }

    protected:

        std::shared_ptr<BinaryData> m_binaryFile;
        std::shared_ptr<BinaryData> m_binaryFileSecond;

        void SetUp() override
        {
            m_binaryFile = std::make_shared<StandardBinaryData>();
            m_binaryFileSecond = std::make_shared<StandardBinaryData>();
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

    /// <summary>
    /// The purpose of this test is to ensure we are actually using a binary
    /// format. Otherwise export and import could be just text which defeats the
    /// point a little bit.
    /// </summary>
    TEST_F(StandardBinaryDataTests, ExportBinaryData_ReturnsAStreamWithTheFirstWordContainingBinaryFile)
    {
        // Arrange
        std::string expected = "BinaryFile_V1.0.0";

        // Act
        const std::string actual = m_binaryFile->ExportBinaryData();

        // Assert
        std::string firstString = GetFirstString(actual);
        ASSERT_EQ(expected, firstString);
    }

#pragma region Int

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsDefault_WhenAddIsNotCalled)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 3454;

        // Act
        int actual = m_binaryFile->TryGetInt(givenKey, expected);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsGiven_WhenValueSetAndGiven)
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

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsGiven_WhenMultipleValuesGiven)
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

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsValue_WhenExportedWithDataAndImportedIntoFreshVersion)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 1234;
        int defaultValue = 5678;

        m_binaryFile->AddInt(givenKey);
        m_binaryFileSecond->AddInt(givenKey);

        // Only second is ever given expected.
        m_binaryFile->SetInt(givenKey, expected);

        const std::string data = m_binaryFile->ExportBinaryData();
        m_binaryFileSecond->ImportBinaryData(data);

        // Act
        int actual = m_binaryFileSecond->TryGetInt(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsMultipleValues_WhenExportedWithDataAndImportedIntoFreshVersion)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int expected = 1234;
        int defaultValue = 7777777;

        std::string givenKeySecond = "otherKey";
        int expectedSecond = 543543;
        int defaultValueSecond = 99999;

        std::string givenKeyThird = "otherOtherKey";
        int expectedThird = 121242;
        int defaultValueThird = 888888;

        m_binaryFile->AddInt(givenKey);
        m_binaryFileSecond->AddInt(givenKey);

        m_binaryFile->AddInt(givenKeySecond);
        m_binaryFileSecond->AddInt(givenKeySecond);

        m_binaryFile->AddInt(givenKeyThird);
        m_binaryFileSecond->AddInt(givenKeyThird);

        // Only second is ever given expected.
        m_binaryFile->SetInt(givenKey, expected);
        m_binaryFile->SetInt(givenKeySecond, expectedSecond);
        m_binaryFile->SetInt(givenKeyThird, expectedThird);

        const std::string data = m_binaryFile->ExportBinaryData();
        m_binaryFileSecond->ImportBinaryData(data);

        // Act
        int actual = m_binaryFileSecond->TryGetInt(givenKey, defaultValue);
        int actualSecond = m_binaryFileSecond->TryGetInt(givenKeySecond, defaultValueSecond);
        int actualThird = m_binaryFileSecond->TryGetInt(givenKeyThird, defaultValueThird);

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(expectedSecond, actualSecond);
        ASSERT_EQ(expectedThird, actualThird);
    }

    TEST_F(StandardBinaryDataTests, TryGetInt_ReturnsDefaultValue_WhenSetIntThenImportValueWithoutData)
    {
        // Arrange
        std::string givenKey = "givenKey";
        int given = 1234;
        int defaultValue = 5678;
        int expected = defaultValue;

        m_binaryFile->AddInt(givenKey);
        m_binaryFileSecond->AddInt(givenKey);

        // Only second is ever given expected.
        m_binaryFile->SetInt(givenKey, expected);

        // Import blank data
        const std::string data = m_binaryFileSecond->ExportBinaryData();
        m_binaryFile->ImportBinaryData(data);

        // Act
        int actual = m_binaryFileSecond->TryGetInt(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion

#pragma region String

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsDefault_WhenAddIsNotCalled)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string expected = "testString";

        // Act
        std::string actual = m_binaryFile->TryGetString(givenKey, expected);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsGiven_WhenValueSetAndGiven)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string expected = "testString";
        std::string defaultValue = "defaultString";

        m_binaryFile->AddString(givenKey);
        m_binaryFile->SetString(givenKey, expected);

        // Act
        std::string actual = m_binaryFile->TryGetString(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsGiven_WhenMultipleValuesGiven)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string expected = "testString";
        std::string defaultValue = "defaultString";

        m_binaryFile->AddString("dummyKey");
        m_binaryFile->SetString("dummyKey", "dummyDefault");

        m_binaryFile->AddString(givenKey);
        m_binaryFile->SetString(givenKey, expected);

        m_binaryFile->AddString("dummyKey2");
        m_binaryFile->SetString("dummyKey2", "dummyDefault2");

        // Act
        std::string actual = m_binaryFile->TryGetString(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsValue_WhenExportedWithDataAndImportedIntoFreshVersion)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string expected = "testString";
        std::string defaultValue = "defaultString";

        m_binaryFile->AddString(givenKey);
        m_binaryFileSecond->AddString(givenKey);

        // Only second is ever given expected.
        m_binaryFile->SetString(givenKey, expected);

        const std::string data = m_binaryFile->ExportBinaryData();
        m_binaryFileSecond->ImportBinaryData(data);

        // Act
        std::string actual = m_binaryFileSecond->TryGetString(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsMultipleValues_WhenExportedWithDataAndImportedIntoFreshVersion)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string expected = "testString";
        std::string defaultValue = "defaultString";

        std::string givenKeySecond = "otherKey";
        std::string expectedSecond = "testString2";
        std::string defaultValueSecond = "defaultString2";

        std::string givenKeyThird = "otherOtherKey";
        std::string expectedThird = "testString3";
        std::string defaultValueThird = "defaultString3";

        m_binaryFile->AddString(givenKey);
        m_binaryFileSecond->AddString(givenKey);

        m_binaryFile->AddString(givenKeySecond);
        m_binaryFileSecond->AddString(givenKeySecond);

        m_binaryFile->AddString(givenKeyThird);
        m_binaryFileSecond->AddString(givenKeyThird);

        // Only second is ever given expected.
        m_binaryFile->SetString(givenKey, expected);
        m_binaryFile->SetString(givenKeySecond, expectedSecond);
        m_binaryFile->SetString(givenKeyThird, expectedThird);

        const std::string data = m_binaryFile->ExportBinaryData();
        m_binaryFileSecond->ImportBinaryData(data);

        // Act
        std::string actual = m_binaryFileSecond->TryGetString(givenKey, defaultValue);
        std::string actualSecond = m_binaryFileSecond->TryGetString(givenKeySecond, defaultValueSecond);
        std::string actualThird = m_binaryFileSecond->TryGetString(givenKeyThird, defaultValueThird);

        // Assert
        ASSERT_EQ(expected, actual);
        ASSERT_EQ(expectedSecond, actualSecond);
        ASSERT_EQ(expectedThird, actualThird);
    }

    TEST_F(StandardBinaryDataTests, TryGetString_ReturnsDefaultValue_WhenSetIntThenImportValueWithoutData)
    {
        // Arrange
        std::string givenKey = "givenKey";
        std::string given = "testString";
        std::string defaultValue = "defaultString";
        std::string expected = defaultValue;

        m_binaryFile->AddString(givenKey);
        m_binaryFileSecond->AddString(givenKey);

        // Only second is ever given expected.
        m_binaryFile->SetString(givenKey, expected);

        // Import blank data
        const std::string data = m_binaryFileSecond->ExportBinaryData();
        m_binaryFile->ImportBinaryData(data);

        // Act
        std::string actual = m_binaryFileSecond->TryGetString(givenKey, defaultValue);

        // Assert
        ASSERT_EQ(expected, actual);
    }

#pragma endregion
}