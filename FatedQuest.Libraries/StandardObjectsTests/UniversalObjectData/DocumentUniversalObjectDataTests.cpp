#include "../StandardObjects/UniversalObjectData/ExplicitUniversalObjectData.h"
#include "../Logger/AllReferences.h"

#include <memory>
#include <gtest/gtest.h>

#include "Collection/Vector/VectorHelpers.h"
#include "Position/FVector4I.h"
#include "Text/StringHelpers.h"

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

#pragma region String
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

    TEST_F(DocumentUniversalObjectDataTests, GetString_ReturnsEmpty_WhenStringIsNotInList)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "myValue";
        std::string createdKey = "notMyKey";
        std::string expected = {};

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

        AddAttribute(attributes, "Key", createdKey);
        AddAttribute(attributes, "Value", givenValue);
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::string actual = testClass->GetString(givenKey);

        // Assert
        ASSERT_EQ(expected, actual) << expected << " != " << actual;
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

    TEST_F(DocumentUniversalObjectDataTests, IsStringLoaded_ReturnsFalse_WhenStringIsNotInList)
    {
        // Arrange
        std::string givenKey = "myKey";
        std::string givenValue = "myValue";
        std::string createdKey = "notMyKey";

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

        AddAttribute(attributes, "Key", createdKey);
        AddAttribute(attributes, "Value", givenValue);
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        bool actual = testClass->IsStringLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
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

    TEST_F(DocumentUniversalObjectDataTests, ListStrings_ReturnsStringValue_WhenProvidedInStringList)
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
        std::vector<std::string> actual = testClass->ListStrings();

        // Assert
        ASSERT_EQ(1, actual.size());
        ASSERT_EQ(givenKey, actual.front()) << givenValue << " != " << actual.front();
    }

    TEST_F(DocumentUniversalObjectDataTests, ListStrings_ReturnsEmpty_WhenNoStringsGiven)
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

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::vector<std::string> actual = testClass->ListStrings();

        // Assert
        ASSERT_EQ(0, actual.size());
    }

    TEST_F(DocumentUniversalObjectDataTests, ListStrings_ReturnsAllStrings_WhenProvidedMultipleInStringList)
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
        std::vector<std::string> actual = testClass->ListStrings();

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }
#pragma endregion

#pragma region Int
    TEST_F(DocumentUniversalObjectDataTests, GetInt_ReturnsIntValue_WhenProvidedInIntList)
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

    TEST_F(DocumentUniversalObjectDataTests, GetInt_ReturnsMinusOne_WhenNoIntIsGiven)
    {
        // Arrange
        std::string givenKey = "myKey";
        int expectedValue = -1;

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        int actual = testClass->GetInt(givenKey);

        // Assert
        ASSERT_EQ(expectedValue, actual) << expectedValue << " != " << actual;
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

    TEST_F(DocumentUniversalObjectDataTests, IsIntLoaded_ReturnsFalse_WhenIntIsNotGiven)
    {
        // Arrange
        std::string givenKey = "myKey";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        bool actual = testClass->IsIntLoaded(givenKey);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(DocumentUniversalObjectDataTests, GetInt_ReturnsAllInts_WhenProvidedMultipleInIntList)
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

    TEST_F(DocumentUniversalObjectDataTests, ListInts_ReturnsIntKeys_WhenGivenInts)
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
        std::vector<std::string> actual = testClass->ListInts();

        // Assert
        ASSERT_EQ(1, actual.size());
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
    }

    TEST_F(DocumentUniversalObjectDataTests, ListInts_ReturnsAllInts_WhenProvidedMultipleInIntList)
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
        std::vector<std::string> actual = testClass->ListInts();

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }

    TEST_F(DocumentUniversalObjectDataTests, ListInts_ReturnsNothing_WhenNothingGiven)
    {
        // Arrange

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::vector<std::string> actual = testClass->ListInts();

        // Assert
        ASSERT_EQ(0, actual.size());
    }
#pragma endregion

#pragma region Vector4I
    TEST_F(DocumentUniversalObjectDataTests, GetVector4I_ReturnsVector4IValue_WhenProvidedInVector4IList)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Vector4Is");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("Vector4I");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "X", std::to_string(givenValue->GetX()));
        AddAttribute(attributes, "Y", std::to_string(givenValue->GetY()));
        AddAttribute(attributes, "Z", std::to_string(givenValue->GetZ()));
        AddAttribute(attributes, "W", std::to_string(givenValue->GetW()));
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::shared_ptr<FVector4I> actual = testClass->GetVector4I(givenKey);

        // Assert
        ASSERT_EQ(givenValue->GetX(), actual->GetX()) << "X: " << givenValue->GetX() << " != " << actual->GetX();
        ASSERT_EQ(givenValue->GetY(), actual->GetY()) << "Y: " << givenValue->GetY() << " != " << actual->GetY();
        ASSERT_EQ(givenValue->GetZ(), actual->GetZ()) << "Z: " << givenValue->GetZ() << " != " << actual->GetZ();
        ASSERT_EQ(givenValue->GetW(), actual->GetW()) << "W: " << givenValue->GetW() << " != " << actual->GetW();
    }

    TEST_F(DocumentUniversalObjectDataTests, IsVector4ILoaded_ReturnsTrue_WhenProvidedInVector4IList)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Vector4Is");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("Vector4I");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "X", std::to_string(givenValue->GetX()));
        AddAttribute(attributes, "Y", std::to_string(givenValue->GetY()));
        AddAttribute(attributes, "Z", std::to_string(givenValue->GetZ()));
        AddAttribute(attributes, "W", std::to_string(givenValue->GetW()));
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        bool actual = testClass->IsVector4ILoaded(givenKey);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(DocumentUniversalObjectDataTests, GetVector4I_ReturnsAllVector4Is_WhenProvidedMultipleInVector4IList)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey2 = "mySecondKey";
        auto givenValue2 = std::make_shared<FVector4I>(5, 6, 7, 8);

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Vector4Is");
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();

        auto stringElement = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(stringElement);
        stringElement->SetName("Vector4I");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "X", std::to_string(givenValue->GetX()));
        AddAttribute(attributes, "Y", std::to_string(givenValue->GetY()));
        AddAttribute(attributes, "Z", std::to_string(givenValue->GetZ()));
        AddAttribute(attributes, "W", std::to_string(givenValue->GetW()));
        stringElement->SetAttributes(attributes);

        auto string2Element = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(string2Element);
        string2Element->SetName("Vector4I");
        auto attributes2 = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes2, "Key", givenKey2);
        AddAttribute(attributes2, "X", std::to_string(givenValue2->GetX()));
        AddAttribute(attributes2, "Y", std::to_string(givenValue2->GetY()));
        AddAttribute(attributes2, "Z", std::to_string(givenValue2->GetZ()));
        AddAttribute(attributes2, "W", std::to_string(givenValue2->GetW()));
        string2Element->SetAttributes(attributes2);

        firstElement->SetAllChildrenNodes(firstElementChildren);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::shared_ptr<FVector4I> actual = testClass->GetVector4I(givenKey);
        std::shared_ptr<FVector4I> actual2 = testClass->GetVector4I(givenKey2);

        // Assert
        ASSERT_EQ(givenValue->GetX(), actual->GetX()) << "X: " << givenValue->GetX() << " != " << actual->GetX();
        ASSERT_EQ(givenValue->GetY(), actual->GetY()) << "Y: " << givenValue->GetY() << " != " << actual->GetY();
        ASSERT_EQ(givenValue->GetZ(), actual->GetZ()) << "Z: " << givenValue->GetZ() << " != " << actual->GetZ();
        ASSERT_EQ(givenValue->GetW(), actual->GetW()) << "W: " << givenValue->GetW() << " != " << actual->GetW();

        ASSERT_EQ(givenValue2->GetX(), actual2->GetX()) << "X: " << givenValue2->GetX() << " != " << actual2->GetX();
        ASSERT_EQ(givenValue2->GetY(), actual2->GetY()) << "Y: " << givenValue2->GetY() << " != " << actual2->GetY();
        ASSERT_EQ(givenValue2->GetZ(), actual2->GetZ()) << "Z: " << givenValue2->GetZ() << " != " << actual2->GetZ();
        ASSERT_EQ(givenValue2->GetW(), actual2->GetW()) << "W: " << givenValue2->GetW() << " != " << actual2->GetW();
    }

    TEST_F(DocumentUniversalObjectDataTests, ListVector4Is_ReturnsVector4IValue_WhenProvidedInVector4IList)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Vector4Is");
        auto stringElement = std::make_shared<ModifiableNode>();
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();
        firstElementChildren.emplace_back(stringElement);
        firstElement->SetAllChildrenNodes(firstElementChildren);

        stringElement->SetName("Vector4I");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();

        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "X", std::to_string(givenValue->GetX()));
        AddAttribute(attributes, "Y", std::to_string(givenValue->GetY()));
        AddAttribute(attributes, "Z", std::to_string(givenValue->GetZ()));
        AddAttribute(attributes, "W", std::to_string(givenValue->GetW()));
        stringElement->SetAttributes(attributes);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::vector<std::string> actual = testClass->ListVector4Is();

        // Assert
        ASSERT_EQ(1, actual.size());
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
    }

    TEST_F(DocumentUniversalObjectDataTests, ListVector4Is_ReturnsAllVector4Is_WhenProvidedMultipleInVector4IList)
    {
        // Arrange
        std::string givenKey = "myKey";
        auto givenValue = std::make_shared<FVector4I>(1, 2, 3, 4);
        std::string givenKey2 = "mySecondKey";
        auto givenValue2 = std::make_shared<FVector4I>(5, 6, 7, 8);

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("Vector4Is");
        auto firstElementChildren = std::vector<std::shared_ptr<ModifiableNode>>();

        auto stringElement = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(stringElement);
        stringElement->SetName("Vector4I");
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes, "Key", givenKey);
        AddAttribute(attributes, "X", std::to_string(givenValue->GetX()));
        AddAttribute(attributes, "Y", std::to_string(givenValue->GetY()));
        AddAttribute(attributes, "Z", std::to_string(givenValue->GetZ()));
        AddAttribute(attributes, "W", std::to_string(givenValue->GetW()));
        stringElement->SetAttributes(attributes);

        auto string2Element = std::make_shared<ModifiableNode>();
        firstElementChildren.emplace_back(string2Element);
        string2Element->SetName("Vector4I");
        auto attributes2 = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        AddAttribute(attributes2, "Key", givenKey2);
        AddAttribute(attributes2, "X", std::to_string(givenValue2->GetX()));
        AddAttribute(attributes2, "Y", std::to_string(givenValue2->GetY()));
        AddAttribute(attributes2, "Z", std::to_string(givenValue2->GetZ()));
        AddAttribute(attributes2, "W", std::to_string(givenValue2->GetW()));
        string2Element->SetAttributes(attributes2);

        firstElement->SetAllChildrenNodes(firstElementChildren);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::vector<std::string> actual = testClass->ListVector4Is();

        // Assert
        ASSERT_EQ(2, actual.size());
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey)) << "Could not find: " << givenKey;
        ASSERT_TRUE(VectorHelpers::ContainsString(actual, givenKey2)) << "Could not find: " << givenKey2;
    }

    TEST_F(DocumentUniversalObjectDataTests, ListVector4Is_ReturnsEmpty_WhenNoVectorsGiven)
    {
        // Arrange
        std::string givenKey = "myKey";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<ExplicitUniversalObjectData> testClass = std::make_shared<ExplicitUniversalObjectData>(givenDocument);

        // Act
        std::vector<std::string> actual = testClass->ListVector4Is();

        // Assert
        ASSERT_EQ(0, actual.size());
    }
#pragma endregion
}