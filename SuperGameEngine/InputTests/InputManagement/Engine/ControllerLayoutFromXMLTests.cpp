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

        std::shared_ptr<ModifiableNode> GetValidMetaTag() const
        {
            auto metaData = std::make_shared<ModifiableNode>();
            metaData->SetName(ControllerLayoutFromXML::MetaTagName);
            std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
            attributes.emplace_back(std::make_shared<ModifiableAttribute>("Name", "ControllerName"));
            attributes.emplace_back(std::make_shared<ModifiableAttribute>("Controller", "Xbox360Controller"));
            attributes.emplace_back(std::make_shared<ModifiableAttribute>("Axis", "1"));
            attributes.emplace_back(std::make_shared<ModifiableAttribute>("Buttons", "1"));
            metaData->SetAttributes(attributes);

            return metaData;
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

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_ReturnsEmpty_WhenCompleteMetadataFoundButMainTagNameIsNotCorrect)
    {
        // Arrange
        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName + "invalid");
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
        ASSERT_FALSE(actual) << "Layout was given. ";
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

#pragma region SDLToUniversalButtons
    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalButtonAreParsed_WhenGiven)
    {
        // Arrange
        int expectedSDLButton = 7;
        std::string expectedSDLButtonInt = std::to_string(expectedSDLButton);

        UniversalControllerButton expectedButton = UniversalControllerButton::DPadRight;
        std::string buttonStringGiven = EUniversalControllerButton::ToString(expectedButton);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Button to parse
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven));

        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(1, sdlButtons.size()) << "No SDL Buttons found in layout";

        ASSERT_EQ(expectedSDLButton, sdlButtons.at(0).first);
        ASSERT_EQ(expectedButton, sdlButtons.at(0).second);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AllSDLToUniversalButtonsAreParsed_WhenGiven)
    {
        // Arrange

        // Node 1 stuff
        int expectedSDLButton = 1;
        std::string expectedSDLButtonInt = std::to_string(expectedSDLButton);
        UniversalControllerButton expectedButton = UniversalControllerButton::DPadRight;
        std::string buttonStringGiven = EUniversalControllerButton::ToString(expectedButton);

        // Node 2 stuff
        int expectedSDLButton2 = 13;
        std::string expectedSDLButtonInt2 = std::to_string(expectedSDLButton2);
        UniversalControllerButton expectedButton2 = UniversalControllerButton::LeftShoulder;
        std::string buttonStringGiven2 = EUniversalControllerButton::ToString(expectedButton2);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Node 1
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven));
        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);

        // Node 2
        auto sdlToUniversalButtonNode2 = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode2->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes2;
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt2));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven2));
        sdlToUniversalButtonNode2->SetAttributes(attributes2);
        childrenButtons.emplace_back(sdlToUniversalButtonNode2);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(2, sdlButtons.size()) << "Not enough SDL Buttons found. ";

        ASSERT_EQ(expectedSDLButton, sdlButtons.at(0).first);
        ASSERT_EQ(expectedButton, sdlButtons.at(0).second);

        ASSERT_EQ(expectedSDLButton2, sdlButtons.at(1).first);
        ASSERT_EQ(expectedButton2, sdlButtons.at(1).second);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotParseSDLToUniversalButton_WhenButtonCannotBeParsed)
    {
        // Arrange
        // Unparsable Int
        std::string expectedSDLButtonInt = "T";

        UniversalControllerButton expectedButton = UniversalControllerButton::DPadRight;
        std::string buttonStringGiven = EUniversalControllerButton::ToString(expectedButton);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Button to parse
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven));

        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(0, sdlButtons.size()) << "It still parsed SDL Buttons";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotParseSDLToUniversalButton_WhenControllerButtonIsNotParsed)
    {
        // Arrange
        int expectedSDLButton = 7;
        std::string expectedSDLButtonInt = std::to_string(expectedSDLButton);

        UniversalControllerButton expectedButton = UniversalControllerButton::Unknown;
        std::string buttonStringGiven = EUniversalControllerButton::ToString(expectedButton);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Button to parse
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven));

        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(0, sdlButtons.size()) << "It still parsed SDL Buttons";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotParseSDLToUniversalButton_WhenNoButtonsFound)
    {
        // Arrange
        UniversalControllerButton expectedButton = UniversalControllerButton::DPadRight;
        std::string buttonStringGiven = EUniversalControllerButton::ToString(expectedButton);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Button to parse
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        // No Button given
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", buttonStringGiven));
        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(0, sdlButtons.size()) << "It still parsed SDL Buttons";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_DoesNotParseSDLToUniversalButton_WhenControllerButtonIsNotFound)
    {
        // Arrange
        int expectedSDLButton = 7;
        std::string expectedSDLButtonInt = std::to_string(expectedSDLButton);

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalButtonsNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonsNode->SetName(ControllerLayoutFromXML::ButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Button to parse
        auto sdlToUniversalButtonNode = std::make_shared<ModifiableNode>();
        sdlToUniversalButtonNode->SetName(ControllerLayoutFromXML::ButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLButton", expectedSDLButtonInt));
        // No Controller Attribute
        sdlToUniversalButtonNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalButtonNode);
        sdlToUniversalButtonsNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalButtonsNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<std::pair<int, UniversalControllerButton>> sdlButtons = actual->SDLToUniversalButton;
        ASSERT_EQ(0, sdlButtons.size()) << "It still parsed SDL Buttons";
    }

#pragma endregion

#pragma region AxisToButtons

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreParsed_WhenGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(1, axisToButtons.size()) << "No SDL Buttons found in layout";

        ASSERT_EQ(expectedValues.Axis, axisToButtons.at(0).Axis);
        ASSERT_EQ(expectedValues.Button, axisToButtons.at(0).Button);
        ASSERT_EQ(expectedValues.Evaluation.Value, axisToButtons.at(0).Evaluation.Value);
        ASSERT_EQ(expectedValues.Evaluation.Comparison, axisToButtons.at(0).Evaluation.Comparison);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AllAxisToButtonsAreParsed_WhenGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        ControllerAxisMappedToButton expectedValues2;
        expectedValues2.Axis = 1;
        expectedValues2.Button = UniversalControllerButton::DPadLeft;
        expectedValues2.Evaluation.Value = 4;
        expectedValues2.Evaluation.Comparison = ControllerComparisonType::Greater;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));
        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);

        // Axis Button to parse 2
        auto axisToButtonTagSingularNode2 = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode2->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes2;
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues2.Axis)));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues2.Button)));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues2.Evaluation.Comparison)));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues2.Evaluation.Value)));
        axisToButtonTagSingularNode2->SetAttributes(attributes2);
        childrenButtons.emplace_back(axisToButtonTagSingularNode2);

        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(2, axisToButtons.size()) << "Not enough SDL Buttons found in layout";

        ASSERT_EQ(expectedValues.Axis, axisToButtons.at(0).Axis);
        ASSERT_EQ(expectedValues.Button, axisToButtons.at(0).Button);
        ASSERT_EQ(expectedValues.Evaluation.Value, axisToButtons.at(0).Evaluation.Value);
        ASSERT_EQ(expectedValues.Evaluation.Comparison, axisToButtons.at(0).Evaluation.Comparison);

        ASSERT_EQ(expectedValues2.Axis, axisToButtons.at(1).Axis);
        ASSERT_EQ(expectedValues2.Button, axisToButtons.at(1).Button);
        ASSERT_EQ(expectedValues2.Evaluation.Value, axisToButtons.at(1).Evaluation.Value);
        ASSERT_EQ(expectedValues2.Evaluation.Comparison, axisToButtons.at(1).Evaluation.Comparison);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenAxisIsNotGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        // No Axis
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenButtonIsNotGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        // No UniversalControllerButton
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenEvaluationValueIsNotGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        // No EvaluationValue

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenEvaluationComparisonIsNotGiven)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        // No EvaluationComparison
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenAxisIsNotParseable)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        std::string givenAxis = "T";
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", givenAxis));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenButtonIsNotParseable)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::Unknown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenEvaluationValueIsNotParseable)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Equals;
        std::string givenValue = "T";

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", givenValue));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AxisToButtonsAreNotFound_WhenEvaluationComparisonIsNotParseable)
    {
        // Arrange
        ControllerAxisMappedToButton expectedValues;
        expectedValues.Axis = 10;
        expectedValues.Button = UniversalControllerButton::FaceButtonDown;
        expectedValues.Evaluation.Value = 12;
        expectedValues.Evaluation.Comparison = ControllerComparisonType::Unknown;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto axisToButtonTagNode = std::make_shared<ModifiableNode>();
        axisToButtonTagNode->SetName(ControllerLayoutFromXML::AxisToButtonTagName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto axisToButtonTagSingularNode = std::make_shared<ModifiableNode>();
        axisToButtonTagSingularNode->SetName(ControllerLayoutFromXML::AxisToButtonTagSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Axis", std::to_string(expectedValues.Axis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerButton", EUniversalControllerButton::ToString(expectedValues.Button)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationComparison", EControllerComparisonType::ToString(expectedValues.Evaluation.Comparison)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("EvaluationValue", std::to_string(expectedValues.Evaluation.Value)));

        axisToButtonTagSingularNode->SetAttributes(attributes);
        childrenButtons.emplace_back(axisToButtonTagSingularNode);
        axisToButtonTagNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(axisToButtonTagNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<ControllerAxisMappedToButton> axisToButtons = actual->AxisToButton;
        ASSERT_EQ(0, axisToButtons.size()) << "SDL Buttons found in layout";
    }
#pragma endregion

#pragma region SDLToUniversalAxes

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesIsParsed_WhenGiven)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(1, sdlAxisToUniversal.size()) << "No SDLToUniversalAxis found in layout";

        ASSERT_EQ(expectedValues.SDLAxis, sdlAxisToUniversal.at(0).SDLAxis);
        ASSERT_EQ(expectedValues.UniversalAxis, sdlAxisToUniversal.at(0).UniversalAxis);
        ASSERT_EQ(expectedValues.Deadzone, sdlAxisToUniversal.at(0).Deadzone);
        ASSERT_EQ(expectedValues.HasDeadzone, sdlAxisToUniversal.at(0).HasDeadzone);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_AllSDLToUniversalAxesAreParsed_WhenGiven)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        AxisToUniversalAxis expectedValues2;
        expectedValues2.SDLAxis = 5;
        expectedValues2.Deadzone = 10;
        expectedValues2.HasDeadzone = true;
        expectedValues2.UniversalAxis = UniversalControllerAxis::RightStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));
        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);

        // Axis Button to parse 2
        auto sdlToUniversalAxesSingleNameNode2 = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode2->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes2;
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues2.SDLAxis)));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues2.UniversalAxis)));
        attributes2.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues2.Deadzone)));
        sdlToUniversalAxesSingleNameNode2->SetAttributes(attributes2);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode2);
        
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(2, sdlAxisToUniversal.size()) << "Incorrect number of SDLToUniversalAxis found in layout";

        ASSERT_EQ(expectedValues.SDLAxis, sdlAxisToUniversal.at(0).SDLAxis);
        ASSERT_EQ(expectedValues.UniversalAxis, sdlAxisToUniversal.at(0).UniversalAxis);
        ASSERT_EQ(expectedValues.Deadzone, sdlAxisToUniversal.at(0).Deadzone);
        ASSERT_EQ(expectedValues.HasDeadzone, sdlAxisToUniversal.at(0).HasDeadzone);

        ASSERT_EQ(expectedValues2.SDLAxis, sdlAxisToUniversal.at(1).SDLAxis);
        ASSERT_EQ(expectedValues2.UniversalAxis, sdlAxisToUniversal.at(1).UniversalAxis);
        ASSERT_EQ(expectedValues2.Deadzone, sdlAxisToUniversal.at(1).Deadzone);
        ASSERT_EQ(expectedValues2.HasDeadzone, sdlAxisToUniversal.at(1).HasDeadzone);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesParsedWithDeadZoneFalse_WhenDeadzoneNotGiven)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        expectedValues.HasDeadzone = false;
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        // No dead zone, this is optional.

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(1, sdlAxisToUniversal.size()) << "No SDLToUniversalAxis found in layout";

        ASSERT_EQ(expectedValues.SDLAxis, sdlAxisToUniversal.at(0).SDLAxis);
        ASSERT_EQ(expectedValues.UniversalAxis, sdlAxisToUniversal.at(0).UniversalAxis);
        ASSERT_EQ(expectedValues.HasDeadzone, sdlAxisToUniversal.at(0).HasDeadzone);
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesDoesNotParse_WhenAxisIsNotGiven)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        // No SDLAxis
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(0, sdlAxisToUniversal.size()) << "Found SDLToUniversalAxis in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesDoesNotParse_WhenUniversalAxisIsNotGiven)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        // No UniversalControllerAxis
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(0, sdlAxisToUniversal.size()) << "Found SDLToUniversalAxis in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesDoesNotParse_WhenSDLAxisIsNotValid)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        std::string givenAxis = "Q";
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", givenAxis));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(0, sdlAxisToUniversal.size()) << "Found SDLToUniversalAxis in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesDoesNotParse_WhenUniversalAxisIsNotValid)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        expectedValues.Deadzone = 30;
        expectedValues.HasDeadzone = true;
        expectedValues.UniversalAxis = UniversalControllerAxis::Unknown;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", std::to_string(expectedValues.Deadzone)));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(0, sdlAxisToUniversal.size()) << "Found SDLToUniversalAxis in layout";
    }

    TEST_F(ControllerLayoutFromXMLTests, CreateFromDocument_SDLToUniversalAxesDoesNotParse_WhenDeadzoneIsNotValid)
    {
        // Arrange
        AxisToUniversalAxis expectedValues;
        expectedValues.SDLAxis = 3;
        std::string givenDeadZone = "T";
        expectedValues.UniversalAxis = UniversalControllerAxis::LeftStickX;

        auto given = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        root->SetName(ControllerLayoutFromXML::MainTagName);
        given->SetRootElement(root);

        auto sdlToUniversalAxesNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesName);
        std::vector<std::shared_ptr<ModifiableNode>> childrenButtons;

        // Axis Button to parse
        auto sdlToUniversalAxesSingleNameNode = std::make_shared<ModifiableNode>();
        sdlToUniversalAxesSingleNameNode->SetName(ControllerLayoutFromXML::SDLToUniversalAxesSingularName);
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("SDLAxis", std::to_string(expectedValues.SDLAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("UniversalControllerAxis", EUniversalControllerAxis::ToString(expectedValues.UniversalAxis)));
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Deadzone", givenDeadZone));

        sdlToUniversalAxesSingleNameNode->SetAttributes(attributes);
        childrenButtons.emplace_back(sdlToUniversalAxesSingleNameNode);
        sdlToUniversalAxesNameNode->SetAllChildrenNodes(childrenButtons);

        std::vector<std::shared_ptr<ModifiableNode>> children;
        children.emplace_back(GetValidMetaTag());
        children.emplace_back(sdlToUniversalAxesNameNode);
        root->SetAllChildrenNodes(children);

        // Act
        std::string error = {};
        std::shared_ptr<ControllerLayout> actual = m_testClass->CreateFromDocument(given, error);

        // Assert
        ASSERT_TRUE(actual) << "Layout not given. ";

        std::vector<AxisToUniversalAxis> sdlAxisToUniversal = actual->SDLAxisToUniversalAxis;
        ASSERT_EQ(0, sdlAxisToUniversal.size()) << "Found SDLToUniversalAxis in layout";
    }
#pragma endregion
}
