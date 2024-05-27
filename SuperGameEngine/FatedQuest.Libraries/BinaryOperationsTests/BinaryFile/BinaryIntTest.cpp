#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryFile/BinaryInt.h"

using namespace BinaryOperations;

namespace BinaryOperations_BinaryIntTests
{
    class BinaryIntTests : public ::testing::Test
    {
    public:
        BinaryIntTests()
        {
        }

    protected:

        std::shared_ptr<BinaryInt> m_binaryInt;
        std::shared_ptr<BinaryInt> m_binaryIntSecond;

        void SetUp() override
        {
            m_binaryInt = std::make_shared<BinaryInt>();
            m_binaryIntSecond = std::make_shared<BinaryInt>();
        }

        void TearDown() override
        {
            m_binaryInt.reset();
            m_binaryIntSecond.reset();
        }

        int GetFirstString(const std::string& binary)
        {
            if (binary == "")
            {
                return -1;
            }

            std::istringstream iss(binary, std::ios::binary);

            size_t intLength = sizeof(int);
            int returnNumber = 0;
            iss.read(reinterpret_cast<char*>(&returnNumber), sizeof(intLength));

            return returnNumber;
        }

        std::string ToBinary(const int& plain)
        {
            std::ostringstream oss(std::ios::binary);
            oss.write(reinterpret_cast<const char*>(&plain), sizeof(int));
            return oss.str();
        }
    };

    TEST_F(BinaryIntTests, ToBinary_ReturnsIntInBinaryForm)
    {
        // Arrange
        int expected = 1234;

        // Act
        std::string actual = m_binaryInt->ToBinary(1234);

        // Assert
        int actualNumber = GetFirstString(actual);
        ASSERT_EQ(expected, actualNumber);
    }

    TEST_F(BinaryIntTests, ToPlainText_ParsesBinaryToPlainText)
    {
        // Arrange
        int expected = 1234;
        std::string given = ToBinary(expected);

        // Act
        int actual = m_binaryInt->ToInt(given);

        // Assert
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BinaryIntTests, ToBinary_ProvidesDataToPlainTextParses)
    {
        // Arrange
        int expected = 1234;

        // Act
        std::string data = m_binaryInt->ToBinary(1234);
        int actual = m_binaryIntSecond->ToInt(data);

        // Assert
        ASSERT_EQ(expected, actual);
    }
}