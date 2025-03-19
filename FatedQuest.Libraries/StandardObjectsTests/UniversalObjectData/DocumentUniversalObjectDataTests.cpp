#include "DocumentUniversalObjectDataTests.h"
#include "../StandardObjects/UniversalObjectData/ExplicitUniversalObjectData.h"
#include "../Logger/AllReferences.h"

#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;
namespace StandardObjectsTests
{
    class DocumentUniversalObjectDataTests : public ::testing::Test
    {
    public:
        DocumentUniversalObjectDataTests()
        {
        }

    protected:
        std::shared_ptr<ConsoleLog> m_logger;

        void SetUp() override
        {
            m_logger = std::make_shared<ConsoleLog>();
            if (auto event = Log::GetEvent().lock())
            {
                event->Subscribe(m_logger);
            }


        }

        void TearDown() override
        {
            if (auto event = Log::GetEvent().lock())
            {
                event->Unsubscribe(m_logger);
            }
        }

        void AddAttribute(std::vector<std::shared_ptr<StoredDocumentAttribute>>& list, const std::string& name, const std::string& value)
        {
            list.emplace_back(std::make_shared<ModifiableAttribute>(name, value));
        }
    };

    TEST_F(DocumentUniversalObjectDataTests, GetString_ReturnsStringValue_WhenProvidedInStringList)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "myValue";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Strings");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("String");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", givenValue);
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::string actual = testClass->GetString(givenKey);

        // Assert
        ASSERT_EQ(givenValue, actual) << givenValue << " != " << actual;
    }

    TEST_F(DocumentUniversalObjectDataTests, IsStringLoaded_ReturnsTrue_WhenProvidedInStringList)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "myValue";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Strings");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("String");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", givenValue);
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        bool actual = testClass->IsStringLoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(DocumentUniversalObjectDataTests, GetString_ReturnsAllStrings_WhenProvidedMultipleInStringList)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "myValue";
        std::string givenKey2 = "mySecondKey";
        std::string givenValue2 = "mySecondValue";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Strings");
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();

        auto stringElement = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(stringElement);
        stringElement->SetName("String");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", givenValue);
        stringElement->SetAttributes(attributes);

        auto string2Element = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(string2Element);
        string2Element->SetName("String");
        auto attributes2 = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes2, "Key", givenKey2);
        AddAttribute(attributes2, "Value", givenValue2);
        string2Element->SetAttributes(attributes2);

        firstElement->SetAllChildrenNodes(firstElementChildren);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::string actual = testClass->GetString(givenKey);
        std::string actual2 = testClass->GetString(givenKey2);

        // Assert
        ASSERT_EQ(givenValue, actual) << givenValue << " != " << actual;
        ASSERT_EQ(givenValue2, actual2) << givenValue2 << " != " << actual2;
    }

    TEST_F(DocumentUniversalObjectDataTests, GetInt_ReturnsStringValue_WhenProvidedInIntList)
    {
        // Arrange
        std::string givenKey = "myKey";
        int givenValue = 44;

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Ints");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("Int");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", std::to_string(givenValue));
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        int actual = testClass->GetInt(givenKey);

        // Assert
        ASSERT_EQ(givenValue, actual) << givenValue << " != " << actual;
    }

    TEST_F(DocumentUniversalObjectDataTests, IsIntLoaded_ReturnsTrue_WhenProvidedInIntList)
    {
        // Arrange
        std::string givenKey = "myKey";
        int givenValue = 12;

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Ints");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("Int");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", std::to_string(givenValue));
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        bool actual = testClass->IsIntLoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(DocumentUniversalObjectDataTests, GetInt_ReturnsAllStrings_WhenProvidedMultipleInIntList)
    {
        // Arrange
        std::string givenKey = "myKey";
        int givenValue = 5;
        std::string givenKey2 = "mySecondKey";
        int givenValue2 = 12;

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Ints");
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();

        auto stringElement = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(stringElement);
        stringElement->SetName("Int");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "Value", std::to_string(givenValue));
        stringElement->SetAttributes(attributes);

        auto string2Element = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(string2Element);
        string2Element->SetName("Int");
        auto attributes2 = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes2, "Key", givenKey2);
        AddAttribute(attributes2, "Value", std::to_string(givenValue2));
        string2Element->SetAttributes(attributes2);

        firstElement->SetAllChildrenNodes(firstElementChildren);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        int actual = testClass->GetInt(givenKey);
        int actual2 = testClass->GetInt(givenKey2);

        // Assert
        ASSERT_EQ(givenValue, actual) << givenValue << " != " << actual;
        ASSERT_EQ(givenValue2, actual2) << givenValue2 << " != " << actual2;
    }
}