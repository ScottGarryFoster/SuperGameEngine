#include "../LibraryIncludes.h"
#include "../../BinaryOperations/BinaryFile/StandardBinaryFile.h"

using namespace BinaryOperations;

namespace BinaryFileTests
{
    class StandardBinaryFileTests : public ::testing::Test
    {
    public:
        StandardBinaryFileTests()
        {
        }

    protected:

        std::shared_ptr<BinaryFile> m_binaryFile;

        void SetUp() override
        {
            m_binaryFile = std::make_shared<StandardBinaryFile>();
        }

        void TearDown() override
        {

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
}