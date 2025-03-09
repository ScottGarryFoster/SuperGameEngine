#include "../../../Engine/Structural/Assets/SuperGameAsset.h"
#include "../../../Engine/DebugEngine/DebugLogger.h"
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
        std::shared_ptr<DebugLogger> m_logger;

        void SetUp() override
        {
            m_logger = std::make_shared<DebugLogger>();
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


    };

    TEST_F(SuperGameAssetsTests, GetName_ReturnsName_WhenOneIsProvidedInStoredDocument)
    {
        // Arrange
        std::string givenName = "expectedName";

        // Make a document with a single element, name.
        auto givenDocument = std::make_shared<ModifiableDocument>();
        auto root = std::make_shared<ModifiableNode>();
        givenDocument->SetRootElement(root);
        auto firstElement = std::make_shared<ModifiableNode>();
        auto children = std::vector<std::shared_ptr<ModifiableNode>>();
        children.emplace_back(firstElement);
        root->SetAllChildrenNodes(children);

        // Give the top level metadata
        firstElement->SetName("GameAssetMeta");

        auto attribute = std::make_shared<ModifiableAttribute>();
        attribute->SetName("Name");
        attribute->SetValue(givenName);
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        attributes.emplace_back(attribute);
        firstElement->SetAttributes(attributes);

        // Give document to Asset
        std::shared_ptr<GameAsset> testClass = std::make_shared<SuperGameAsset>(givenDocument);

        // Act
        std::string actual = testClass->GetName();
        
        // Assert
        ASSERT_EQ(givenName, actual) << givenName << " != " << actual;
    }
}