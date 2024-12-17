#include "../XmlDocument/AllReferences.h"
#include "../XmlDocument/FatedQuestLibraries.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_XMLDocument
{
    class RapidXMLDocumentTests : public ::testing::Test
    {
    public:
        std::shared_ptr<SuperXMLDocument> m_testClass;

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

#pragma region FromFile
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

    TEST_F(RapidXMLDocumentTests, LoadFromFile_ReturnsFalse_WhenFileContentsIsNotXML)
    {
        // Arrange
        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, "Not xml")) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";

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

    TEST_F(RapidXMLDocumentTests, RootAttributes_ReturnsGivenAttributes_WhenRootNodeContainsSome)
    {
        // Arrange
        std::string given = R"(<Node AttributeName="ValueOne" AttributeName2="ValueTwo" />)";

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

        std::vector<std::shared_ptr<XMLAttribute>> attributes = actual->Attributes();
        ASSERT_EQ(2, attributes.size()) << "It did not parse both elements.";

        ASSERT_EQ("AttributeName", attributes[0]->Name()) << "AttributeName != " << attributes[0]->Name();
        ASSERT_EQ("ValueOne", attributes[0]->Value()) << "ValueOne != " << attributes[0]->Value();

        ASSERT_EQ("AttributeName2", attributes[1]->Name()) << "AttributeName2 != " << attributes[1]->Name();
        ASSERT_EQ("ValueTwo", attributes[1]->Value()) << "ValueTwo != " << attributes[1]->Value();
    }

    TEST_F(RapidXMLDocumentTests, GetRoot_CreatesMoreThanOneNode_WhenThereAreChildren)
    {
        // Arrange
        std::string given = "<Node><Inner /></Node>";

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

        std::shared_ptr<XMLNode> firstChild = actual->GetFirstChild();
        ASSERT_TRUE(firstChild);
        ASSERT_EQ("Inner", firstChild->Name()) << "Inner != " << firstChild->Name();
    }

    TEST_F(RapidXMLDocumentTests, InnerAttributes_AreParsed_WhenAttributesAreFoundWithinNodes)
    {
        // Arrange
        std::string given = R"(<Node><Inner AttributeName="ValueOne" AttributeName2="ValueTwo" /></Node>)";

        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, given)) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";
        m_testClass->LoadFromFile(testFile);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        std::shared_ptr<XMLNode> firstChild = actual->GetFirstChild();
        ASSERT_TRUE(firstChild);
        ASSERT_EQ("Inner", firstChild->Name()) << "Inner != " << firstChild->Name();

        std::vector<std::shared_ptr<XMLAttribute>> attributes = firstChild->Attributes();
        ASSERT_EQ(2, attributes.size()) << "It did not parse both elements.";

        ASSERT_EQ("AttributeName", attributes[0]->Name()) << "AttributeName != " << attributes[0]->Name();
        ASSERT_EQ("ValueOne", attributes[0]->Value()) << "ValueOne != " << attributes[0]->Value();

        ASSERT_EQ("AttributeName2", attributes[1]->Name()) << "AttributeName2 != " << attributes[1]->Name();
        ASSERT_EQ("ValueTwo", attributes[1]->Value()) << "ValueTwo != " << attributes[1]->Value();
    }

    TEST_F(RapidXMLDocumentTests, FirstAndAdjacent_ReturnsAnArrayOfNodeChildren_WhenGivenComplexInput)
    {
        // Arrange
        std::string given = R"(
                <Node>
                    <Inner1 />
                    <Inner2 />
                    <Inner3> <Unexcepted /> </Inner3>
                    <Inner4 />
                </Node>)";

        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, given)) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";
        m_testClass->LoadFromFile(testFile);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        int i = 0;
        for (std::shared_ptr<XMLNode> child = actual->GetFirstChild(); child; child = actual->GetAdjacentNode())
        {
            ASSERT_TRUE(child);
            switch (i)
            {
            case 0:
                ASSERT_EQ("Inner1", child->Name()) << "Inner1 != " << child->Name() << " index: " << i;
                break;
            case 1:
                ASSERT_EQ("Inner2", child->Name()) << "Inner2 != " << child->Name() << " index: " << i;
                break;
            case 2:
                ASSERT_EQ("Inner3", child->Name()) << "Inner3 != " << child->Name() << " index: " << i;
                break;
            case 3:
                ASSERT_EQ("Inner4", child->Name()) << "Inner4 != " << child->Name() << " index: " << i;
                break;
            }

            ++i;
        }
    }

    TEST_F(RapidXMLDocumentTests, GetLastChild_ReturnsLastInAList_WhenGivenAListOfNodes)
    {
        // Arrange
        std::string given = R"(
                <Node>
                    <Inner1 />
                    <Inner2 />
                    <Inner3> <Unexcepted /> </Inner3>
                    <Inner4 />
                </Node>)";

        std::string testFile = Directory::CombinePath(TestDirectory(), "test.txt");
        m_cleanupFiles.push_back(testFile);
        ASSERT_TRUE(File::WriteLine(testFile, given)) << "Could not write test file.";
        ASSERT_TRUE(File::Exists(testFile)) << "Could not write test file, it does not exist. ";
        m_testClass->LoadFromFile(testFile);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        std::shared_ptr<XMLNode> last = actual->GetLastChild();
        ASSERT_TRUE(last);
        ASSERT_EQ("Inner4", last->Name()) << "Inner4 != " << last->Name();
    }

#pragma endregion

#pragma region FromContents
    TEST_F(RapidXMLDocumentTests, Load_ReturnsFalse_WhenInputIsNotXml)
    {
        // Arrange
        std::string given = "Not xml";

        // Act
        bool actual = m_testClass->Load(given);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RapidXMLDocumentTests, Load_ReturnsTrue_WhenContentExists)
    {
        // Arrange
        std::string given = "<Node />";

        // Act
        bool actual = m_testClass->Load(given);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(RapidXMLDocumentTests, GetRoot_ReturnsGiven_WhenXmlContainsOneNode)
    {
        // Arrange
        std::string given = "<Node />";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        XMLNode* properActual = actual.get();
        ASSERT_NE(nullptr, properActual);
        ASSERT_EQ("Node", actual->Name()) << "Node != " << actual->Name();
    }

    TEST_F(RapidXMLDocumentTests, RootAttributes_ReturnsGivenAttributes_WhenRootNodeContainsSomeLoadingXML)
    {
        // Arrange
        std::string given = R"(<Node AttributeName="ValueOne" AttributeName2="ValueTwo" />)";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        XMLNode* properActual = actual.get();
        ASSERT_NE(nullptr, properActual);
        ASSERT_EQ("Node", actual->Name()) << "Node != " << actual->Name();

        std::vector<std::shared_ptr<XMLAttribute>> attributes = actual->Attributes();
        ASSERT_EQ(2, attributes.size()) << "It did not parse both elements.";

        ASSERT_EQ("AttributeName", attributes[0]->Name()) << "AttributeName != " << attributes[0]->Name();
        ASSERT_EQ("ValueOne", attributes[0]->Value()) << "ValueOne != " << attributes[0]->Value();

        ASSERT_EQ("AttributeName2", attributes[1]->Name()) << "AttributeName2 != " << attributes[1]->Name();
        ASSERT_EQ("ValueTwo", attributes[1]->Value()) << "ValueTwo != " << attributes[1]->Value();
    }

    TEST_F(RapidXMLDocumentTests, GetRoot_CreatesMoreThanOneNode_WhenThereAreChildrenLoadingXML)
    {
        // Arrange
        std::string given = "<Node><Inner /></Node>";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        XMLNode* properActual = actual.get();
        ASSERT_NE(nullptr, properActual);
        ASSERT_EQ("Node", actual->Name()) << "Node != " << actual->Name();

        std::shared_ptr<XMLNode> firstChild = actual->GetFirstChild();
        ASSERT_TRUE(firstChild);
        ASSERT_EQ("Inner", firstChild->Name()) << "Inner != " << firstChild->Name();
    }

    TEST_F(RapidXMLDocumentTests, InnerAttributes_AreParsed_WhenAttributesAreFoundWithinNodesLoadingXML)
    {
        // Arrange
        std::string given = R"(<Node><Inner AttributeName="ValueOne" AttributeName2="ValueTwo" /></Node>)";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        std::shared_ptr<XMLNode> firstChild = actual->GetFirstChild();
        ASSERT_TRUE(firstChild);
        ASSERT_EQ("Inner", firstChild->Name()) << "Inner != " << firstChild->Name();

        std::vector<std::shared_ptr<XMLAttribute>> attributes = firstChild->Attributes();
        ASSERT_EQ(2, attributes.size()) << "It did not parse both elements.";

        ASSERT_EQ("AttributeName", attributes[0]->Name()) << "AttributeName != " << attributes[0]->Name();
        ASSERT_EQ("ValueOne", attributes[0]->Value()) << "ValueOne != " << attributes[0]->Value();

        ASSERT_EQ("AttributeName2", attributes[1]->Name()) << "AttributeName2 != " << attributes[1]->Name();
        ASSERT_EQ("ValueTwo", attributes[1]->Value()) << "ValueTwo != " << attributes[1]->Value();
    }

    TEST_F(RapidXMLDocumentTests, FirstAndAdjacent_ReturnsAnArrayOfNodeChildren_WhenGivenComplexInputLoadingXML)
    {
        // Arrange
        std::string given = R"(
                <Node>
                    <Inner1 />
                    <Inner2 />
                    <Inner3> <Unexcepted /> </Inner3>
                    <Inner4 />
                </Node>)";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        int i = 0;
        for (std::shared_ptr<XMLNode> child = actual->GetFirstChild(); child; child = actual->GetAdjacentNode())
        {
            ASSERT_TRUE(child);
            switch (i)
            {
            case 0:
                ASSERT_EQ("Inner1", child->Name()) << "Inner1 != " << child->Name() << " index: " << i;
                break;
            case 1:
                ASSERT_EQ("Inner2", child->Name()) << "Inner2 != " << child->Name() << " index: " << i;
                break;
            case 2:
                ASSERT_EQ("Inner3", child->Name()) << "Inner3 != " << child->Name() << " index: " << i;
                break;
            case 3:
                ASSERT_EQ("Inner4", child->Name()) << "Inner4 != " << child->Name() << " index: " << i;
                break;
            }

            ++i;
        }
    }

    TEST_F(RapidXMLDocumentTests, GetLastChild_ReturnsLastInAList_WhenGivenAListOfNodesLoadingXML)
    {
        // Arrange
        std::string given = R"(
                <Node>
                    <Inner1 />
                    <Inner2 />
                    <Inner3> <Unexcepted /> </Inner3>
                    <Inner4 />
                </Node>)";
        m_testClass->Load(given);

        // Act
        std::shared_ptr<XMLNode> actual = m_testClass->GetRoot();

        // Assert
        std::shared_ptr<XMLNode> last = actual->GetLastChild();
        ASSERT_TRUE(last);
        ASSERT_EQ("Inner4", last->Name()) << "Inner4 != " << last->Name();
    }

#pragma endregion

#pragma region XMLNode

    TEST_F(RapidXMLDocumentTests, Inner_ReturnsInnerText_WhenGivenNodeWithInnerText)
    {
        // Arrange
        std::string given = R"(<Node>Text</Node>)";
        m_testClass->Load(given);

        // Act
        std::string actual = m_testClass->GetRoot()->Inner();

        // Assert
        ASSERT_EQ("Text", actual);
    }

    TEST_F(RapidXMLDocumentTests, Inner_ReturnsEmptyString_WhenNodeHasNoInnerText)
    {
        // Arrange
        std::string given = R"(<Node></Node>)";
        m_testClass->Load(given);

        // Act
        std::string actual = m_testClass->GetRoot()->Inner();

        // Assert
        ASSERT_EQ("", actual);
    }


    TEST_F(RapidXMLDocumentTests, Inner_ReturnsEmptyString_WhenNodeIsSelfClosing)
    {
        // Arrange
        std::string given = R"(<Node />)";
        m_testClass->Load(given);

        // Act
        std::string actual = m_testClass->GetRoot()->Inner();

        // Assert
        ASSERT_EQ("", actual);
    }

#pragma endregion
}