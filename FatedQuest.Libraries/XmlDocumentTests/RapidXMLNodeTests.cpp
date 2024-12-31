#include "../XmlDocument/AllReferences.h"
#include "../XmlDocument/FatedQuestLibraries.h"
#include <memory>
#include <gtest/gtest.h>

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_XMLDocument
{
    class RapidXMLNodeTests : public ::testing::Test
    {
    public:
        std::shared_ptr<StoredDocument> m_testClass;

        RapidXMLNodeTests()
        {
        }

    protected:

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        std::shared_ptr<StoredDocumentAttribute> CreateAttribute(
            const std::string& name,
            const std::string& value)
        {
            std::shared_ptr<RapidXMLAttribute> attribute = std::make_shared<RapidXMLAttribute>();
            attribute->SetName(name);
            attribute->SetValue(value);

            return attribute;
        }
    };

#pragma region Attribute
    TEST_F(RapidXMLNodeTests, Attribute_ReturnsAttribute_WhenAttributeIsInList)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string expected = "Expected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(lookfor, expected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(lookfor);

        // Assert
        ASSERT_TRUE(actual);
        ASSERT_EQ(lookfor, actual->Name());
        ASSERT_EQ(expected, actual->Value());
    }

    TEST_F(RapidXMLNodeTests, Attribute_DoesNotReturnAttribute_WhenAttributeIsNotInList)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string inArray = "inArray";
        std::string unexpected = "unexpected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(inArray, unexpected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(lookfor);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RapidXMLNodeTests, Attribute_DoesNotReturnAttribute_WhenCaseDoesNotMatch)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string givenLookFor = "LOoKFOr";
        std::string unexpected = "unexpected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(lookfor, unexpected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(givenLookFor);

        // Assert
        ASSERT_FALSE(actual);
    }

#pragma endregion

#pragma region Attribute with bool

    TEST_F(RapidXMLNodeTests, AttributeWithFalse_ReturnsAttribute_WhenAttributeIsInList)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string expected = "Expected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(lookfor, expected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(lookfor, false);

        // Assert
        ASSERT_TRUE(actual);
        ASSERT_EQ(lookfor, actual->Name());
        ASSERT_EQ(expected, actual->Value());
    }

    TEST_F(RapidXMLNodeTests, AttributeWithFalse_DoesNotReturnAttribute_WhenAttributeIsNotInList)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string inArray = "inArray";
        std::string unexpected = "unexpected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(inArray, unexpected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(lookfor, false);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RapidXMLNodeTests, AttributeWithFalse_DoesNotReturnAttribute_WhenCaseDoesNotMatch)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string givenLookFor = "LOoKFOr";
        std::string unexpected = "unexpected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(lookfor, unexpected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(givenLookFor, false);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(RapidXMLNodeTests, AttributeWithTrue_ReturnsAttribute_WhenCaseDoesNotMatch)
    {
        // Arrange
        std::string lookfor = "LookFor";
        std::string givenLookFor = "LOoKFOr";
        std::string expected = "Expected";
        std::vector<std::shared_ptr<StoredDocumentAttribute>> given;
        given.push_back(CreateAttribute(lookfor, expected));

        std::shared_ptr<RapidXMLNode> rapidNode = std::make_shared<RapidXMLNode>();
        rapidNode->SetAttributes(given);

        // Act
        std::shared_ptr<StoredDocumentAttribute> actual = rapidNode->Attribute(lookfor, true);

        // Assert
        ASSERT_TRUE(actual);
        ASSERT_EQ(lookfor, actual->Name());
        ASSERT_EQ(expected, actual->Value());
    }

#pragma endregion
}