#include "../../StandardOperations/AllReferences.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_StandardOperations_XMLDocument
{
    class RapidXMLDocumentTests : public ::testing::Test
    {
    public:
        std::shared_ptr<XMLDocument> m_testClass;

        RapidXMLDocumentTests()
        {
        }

    protected:

        std::vector<std::string> m_cleanupFiles;

        void SetUp() override
        {
            // Ensures if there's an issue it excepts here not after file creation.
            m_cleanupFiles.clear();

            m_testClass = std::make_shared<RapidXMLDocument>();
        }

        void TearDown() override
        {
            for (const std::string& path : m_cleanupFiles)
            {
                if (File::Exists(path))
                {
                    File::Delete(path);
                }
            }
        }

        std::string TestDirectory()
        {
            std::string tempDirectory = Directory::GetTempDirectory();
            std::string completePath = Directory::CombinePath(
                tempDirectory, "SuperGameEngine", "Tests", "StandardOperations", "RapidXMLDocument");

            return completePath;
        }
    };

    TEST_F(RapidXMLDocumentTests, LoadFromFile_ReturnsFalse_WhenFileDoesNotExist)
    {
        // Arrange
        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        ASSERT_FALSE(File::Exists(testFile)) << "Test file appears to exist, cleanup must not have worked.";

        // Act
        bool actual = m_testClass->LoadFromFile(testFile);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RapidXMLDocumentTests, LoadFromFile_ReturnsTrue_WhenFileExists)
    {
        // Arrange
        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, "<Node />")) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";

        // Act
        bool actual = m_testClass->LoadFromFile(testFile);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RapidXMLDocumentTests, GetRoot_ReturnsGiven_WhenFileContainsOneNode)
    {
        // Arrange
        std::string given = "<Node />";

        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, given)) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";
        m_testClass->LoadFromFile(testFile);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        XMLNode* properActual = actual.get();
        ASSERT_NE(nullptr, properActual);
        ASSERT_EQ("Node", actual->Name()) << "Node != " << actual->Name();
    }
}