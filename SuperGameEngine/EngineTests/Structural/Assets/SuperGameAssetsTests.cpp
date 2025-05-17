#include "../../../Engine/Structural/Assets/SuperGameAsset.h"
#include "../../../../FatedQuest.Libraries/Logger/Console/ConsoleLog.h"
#include <memory>
#include <gtest/gtest.h>

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
namespace SuperGameEngineTests_Structural_Assets
{
    class SuperGameAssetsTests : public ::testing::Test
    {
    public:
        SuperGameAssetsTests()
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

    TEST_F(SuperGameAssetsTests, GetName_ReturnsName_WhenOneIsProvidedInStoredDocument)
    {
        // Arrange
        std::string givenKey = "GameAssetName";
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
        std::shared_ptr<SuperGameAsset> testClass = std::make_shared<SuperGameAsset>(givenDocument, std::string());

        // Act
        std::string actual = testClass->GetName();

        // Assert
        ASSERT_EQ(givenValue, actual) << givenValue << " != " << actual;
    }

    TEST_F(SuperGameAssetsTests, GetPath_ReturnsGivenPath_WhenProvidedOnConstruction)
    {
        // Arrange
        std::string givenPath = "Example\\Path\\texture.png";

        // Document is not required.
        // This may change and there amy be an exception in the future here.
        auto givenDocument = std::make_shared<ModifiableDocument>();

        // Give document to Asset. Using ExplicitTextGameAsset as this exposes the data.
        std::shared_ptr<SuperGameAsset> testClass = std::make_shared<SuperGameAsset>(givenDocument, givenPath);

        // Act
        std::string actual = testClass->GetPath();

        // Assert
        ASSERT_EQ(givenPath, actual) << givenPath << " != " << actual;
    }
}