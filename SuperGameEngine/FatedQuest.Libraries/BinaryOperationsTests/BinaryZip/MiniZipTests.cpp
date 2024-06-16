#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryZip/MiniZip.h"

#include <cstdlib>
#include <random>

using namespace BinaryOperations;

namespace BinaryOperations_BinaryIntTests
{
    class MiniZipTests : public ::testing::Test
    {
    public:
        MiniZipTests()
        {
        }

    protected:

        std::shared_ptr<MiniZip> m_miniZip;

        void SetUp() override
        {
            m_miniZip = std::make_shared<MiniZip>();
        }

        void TearDown() override
        {
            m_miniZip.reset();
        }

        std::string GetTemp()
        {
            const char* tempPath = std::getenv("TEMP");
            if (!tempPath)
            {
                tempPath = std::getenv("TMP");
            }

            if (tempPath)
            {
                return std::string(tempPath);
            }
            else 
            {
                return std::string();
            }
        }

        int RandomNumber(int min, int max)
        {
            std::random_device randomDevice;
            std::mt19937 generator(randomDevice());
            std::uniform_int_distribution<> distribution(min, max);

            return distribution(generator);
        }

        std::string RandomTempPath()
        {
            std::string temp = GetTemp();
            if (temp != "")
            {
                std::string newDirectory = temp + "\\SGETEST\\" + std::to_string(RandomNumber(0, 999999));
                int i = 0;
                int cutOff = 1000;
                while (Directory::Exists(newDirectory) && i < cutOff)
                {
                    newDirectory = temp + "\\" + std::to_string(RandomNumber(0, 999999));
                    ++i;
                }
                
                if (i < cutOff)
                {
                    return newDirectory;
                }
            }

            return temp;
        }
    };

    TEST_F(MiniZipTests, CreateZip_ReturnsFalse_WhenFilenameIsBlank)
    {
        // Arrange
        std::string givenPath = "";
        std::vector<std::string> filenames = {};

        // Act
        bool actual = m_miniZip->CreateZip(givenPath, filenames, ZipCreateOpenOption::CloseAfterOperation);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(MiniZipTests, CreateZip_ReturnsFalse_WhenFilenamesAreEmpty)
    {
        // Arrange
        std::string givenPath = RandomTempPath() + "\\tempzip.zip";
        std::vector<std::string> filenames = {};

        // Act
        bool actual = m_miniZip->CreateZip(givenPath, filenames, ZipCreateOpenOption::CloseAfterOperation);

        // Assert
        ASSERT_FALSE(actual);
    }
}