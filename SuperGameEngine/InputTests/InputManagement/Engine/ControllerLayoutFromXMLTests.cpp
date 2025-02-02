#include <gtest/gtest.h>

#include "../../../Engine/DebugEngine/DebugLogger.h"
#include "../../../Input/InputManagement/Engine/ControllerLayoutFromXML.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../Engine/DebugEngine/DebugLogger.h"
#include "../../../Input/InputManagement/Engine/ControllerLayout.h"

using namespace SuperGameInput;
using namespace FatedQuestLibraries;

namespace SuperGameInput_InputManagement_Engine
{
    class ControllerLayoutFromXMLTests : public ::testing::Test
    {
    public:
        ControllerLayoutFromXMLTests()
        {
        }

    protected:

        std::shared_ptr<ControllerLayoutFromXML> m_testClass;
        std::shared_ptr<SuperGameEngine::DebugLogger> m_logger;

        void SetUp() override
        {
            m_testClass = std::make_shared<ControllerLayoutFromXML>();

            m_logger = std::make_shared<SuperGameEngine::DebugLogger>();
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Subscribe(m_logger);
            }
        }

        void TearDown() override
        {
            if (auto shared = Log::GetEvent().lock())
            {
                shared->Unsubscribe(m_logger);
            }
        }


    };

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ReturnsEmpty_WhenRootNodeIsNotFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout given. "; 
        ASSERT_FALSE(error.empty()) << "No error given. ";
    }

#pragma region MetaTag

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ReturnsDocument_WhenCompleteMetadataFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ParsesName_WhenNameIsGiven)
    {
        // Arrange
        std::string expected = "ControllerName";

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", expected));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";
        ASSERT_EQ(expected, actual->Name) << "Name does not match.";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ParsesController_WhenControllerIsGiven)
    {
        // Arrange
        Controller expected = Controller::Xbox360Controller;
        std::string givenString = EController::ToString(expected);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ValidName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", givenString));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";
        ASSERT_EQ(expected, actual->Controller) << "Controller does not match.";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ParsesAxis_WhenAxisIsGiven)
    {
        // Arrange
        int expected = 1;
        std::string givenString = std::to_string(expected);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ValidName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "XboxSeriesController"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", givenString));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";
        ASSERT_EQ(expected, actual->Axis) << "Axis does not match.";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ParsesButtons_WhenButtonsIsGiven)
    {
        // Arrange
        int expected = 4;
        std::string givenString = std::to_string(expected);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ValidName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "XboxSeriesController"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", givenString));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";
        ASSERT_EQ(expected, actual->Buttons) << "Buttons do not match.";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenNameIsNotFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenControllerIsNotFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenAxisIsNotFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenButtonsIsNotFound)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenNameIsEmpty)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", ""));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenControllerIsUnparsable)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", EController::ToString(Controller::Unknown)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenAxisIsUnparsable)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "F"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotReturnDocument_WhenButtonsIsUnparsable)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto metaData = std::make_shared<ModifiableNode>();
        metaData->SetName(ControllerLayoutFromXML::MetaTagName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "Q"));
        metaData->SetAttributes(attributes);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(metaData);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_FALSE(actual) << "Layout is given. ";
    }

#pragma endregion
}
