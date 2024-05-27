#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryFile/BinaryString.h"

using namespace BinaryOperations;

namespace BinaryOperations_BinaryStringTests
{
    class BinaryStringTests : public ::testing::Test
    {
    public:
        BinaryStringTests()
        {
        }

    protected:

        std::shared_ptr<BinaryString> m_binaryString;
        std::shared_ptr<BinaryString> m_binaryStringSecond;

        void SetUp() override
        {
            m_binaryString = std::make_shared<BinaryString>();
            m_binaryStringSecond = std::make_shared<BinaryString>();
        }

        void TearDown() override
        {
            m_binaryString.reset();
            m_binaryStringSecond.reset();
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

        std::string ToBinary(const std::string& plain)
        {
            std::ostringstream oss(std::ios::binary);

            size_t stringLength = plain.size();
            oss.write(reinterpret_cast<const char*>(&stringLength), sizeof(stringLength));
            oss.write(plain.c_str(), stringLength);

            return oss.str();
        }
    };

    TEST_F(BinaryStringTests, ToBinary_ReturnsStringInBinaryForm)
    {
        // Arrange
        std::string expected = "givenKey";

        // Act
        std::string actual = m_binaryString->ToBinary(expected);

        // Assert
        std::string actualString = GetFirstString(actual);
        ASSERT_EQ(expected, actualString);
    }

    TEST_F(BinaryStringTests, ToPlainText_ParsesBinaryToPlainText)
    {
        // Arrange
        std::string expected = "givenKey";
        std::string given = ToBinary(expected);

        // Act
        std::string actual = m_binaryString->ToPlainText(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BinaryStringTests, ToBinary_ProvidesDataToPlainTextParses)
    {
        // Arrange
        std::string expected = "givenKey";

        // Act
        std::string data = m_binaryString->ToBinary(expected);
        std::string actual = m_binaryStringSecond->ToPlainText(data);

        // Assert
        ASSERT_EQ(expected, actual);
    }
}