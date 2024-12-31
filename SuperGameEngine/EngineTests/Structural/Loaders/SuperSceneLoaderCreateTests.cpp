#include "../../../Engine/Structural/Loaders/SuperSceneLoader.h"
#include <memory>
#include <gtest/gtest.h>

#include "../../../../FatedQuest.Libraries/StandardObjects/Object/GUID/GUIDHelpers.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../Engine/Structural/Scene/SuperScene.h"
#include "../../../Engine/Structural/Packages/SuperSceneLoadPackage.h"
#include "../../../Engine/DebugEngine/DebugLogger.h"
#include "../../../Engine/Structural/GameObject/GameObject.h"
#include "../../../Engine/Structural/InternalComponents/TestComponent/TestComponent.h"
#include "../../../Engine/Structural/Serializable/SuperSerializableParser.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
namespace SuperGameEngineTests_Structural_Loaders
{
    class SuperSceneLoaderCreateTests : public ::testing::Test
    {
    public:
        SuperSceneLoaderCreateTests()
        {
        }

    protected:

        std::shared_ptr<SuperSceneLoader> m_testClass;
        std::shared_ptr<SuperSceneLoadPackage> m_sceneLoadPackage;
        std::shared_ptr<DebugLogger> m_logger;

        void SetUp() override
        {
            m_logger = std::make_shared<DebugLogger>();
            if (auto event = Log::GetEvent().lock())
            {
                event->Subscribe(m_logger);
            }

            m_sceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
            m_sceneLoadPackage->SetSerializableParser(std::make_shared<SuperSerializableParser>());
            m_testClass = std::make_shared<SuperSceneLoader>(m_sceneLoadPackage);
        }

        void TearDown() override
        {
            if (auto event = Log::GetEvent().lock())
            {
                event->Unsubscribe(m_logger);
            }
        }

        
    };

    TEST_F(SuperSceneLoaderCreateTests, Create_ReturnsScene_WhenGivenADocumentWithJustAScene)
    {
        // Arrange
        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");

        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_ReturnsEmpty_WhenEmptyGiven)
    {
        // Arrange
        std::shared_ptr<StoredDocument> givenDocument = {};

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_ReturnsEmpty_WhenDocumentDoesNotStartWithScene)
    {
        // Arrange
        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("NotScene");

        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_SetsGuid_WhenGiven)
    {
        // Arrange
        std::shared_ptr<Guid> given = GUIDHelpers::CreateGUID();
        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Guid", GUIDHelpers::ToString(*given)));

        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");
        givenRootNode->SetAttributes(attributes);

        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        ASSERT_TRUE(*given == *actual->GetGuid())
            << given->ToString() << " != " << actual->GetGuid()->ToString();
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_AddsGameObject_WhenGiven)
    {
        // Arrange
        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");

        auto givenGameObject = std::make_shared<ModifiableNode>();
        givenGameObject->SetName("GameObject");

        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);

        givenRootNode->SetFirstChild(givenGameObject);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        auto superScene = std::static_pointer_cast<SuperScene>(actual);
        ASSERT_TRUE(superScene) << "Scene was not a super scene";

        std::vector<std::shared_ptr<GameObject>> actualGo = superScene->GetChildrenIncludingPending();
        ASSERT_EQ(1, actualGo.size());
        ASSERT_TRUE(actualGo.at(0));
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_SetsGameObjectGuid_WhenGiven)
    {
        // Arrange
        std::shared_ptr<Guid> givenGuid = GUIDHelpers::CreateGUID();

        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");

        auto givenGameObject = std::make_shared<ModifiableNode>();
        givenGameObject->SetName("GameObject");

        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Guid", GUIDHelpers::ToString(*givenGuid)));
        givenGameObject->SetAttributes(attributes);

        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);

        givenRootNode->SetFirstChild(givenGameObject);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        auto superScene = std::static_pointer_cast<SuperScene>(actual);
        ASSERT_TRUE(superScene) << "Scene was not a super scene";

        std::vector<std::shared_ptr<GameObject>> actualGo = superScene->GetChildrenIncludingPending();
        ASSERT_EQ(1, actualGo.size());
        ASSERT_EQ(GUIDHelpers::ToString(*givenGuid), GUIDHelpers::ToString(*actualGo.at(0)->GetGuid()))
            << GUIDHelpers::ToString(*givenGuid) << " != "
            << GUIDHelpers::ToString(*actualGo.at(0)->GetGuid());
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_AddsTestComponent_WhenGiven)
    {
        // Arrange
        const std::string componentTestType = "TestComponent";

        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");

        auto givenGameObject = std::make_shared<ModifiableNode>();
        givenGameObject->SetName("GameObject");

        auto givenComponent = std::make_shared<ModifiableNode>();
        givenComponent->SetName("Component");

        auto attributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
        attributes.emplace_back(std::make_shared<ModifiableAttribute>
            ("Type", componentTestType));
        givenComponent->SetAttributes(attributes);

        // Setup chain
        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);
        givenRootNode->SetFirstChild(givenGameObject);
        givenGameObject->SetFirstChild(givenComponent);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        auto superScene = std::static_pointer_cast<SuperScene>(actual);
        ASSERT_TRUE(superScene) << "Scene was not a super scene";

        std::vector<std::shared_ptr<GameObject>> actualGo = superScene->GetChildrenIncludingPending();
        std::shared_ptr<GameComponent> actualComponent = actualGo.at(0)->GetComponent(componentTestType);
        ASSERT_TRUE(actualComponent);

        std::shared_ptr<TestComponent> testComponent = std::static_pointer_cast<TestComponent>(actualComponent);
        ASSERT_TRUE(testComponent);
        ASSERT_EQ(componentTestType, testComponent->TypeName());
    }

    TEST_F(SuperSceneLoaderCreateTests, Create_DoesNotAddComponent_WhenTypeIsNotAdded)
    {
        // Arrange
        const std::string componentTestType = "TestComponent";

        auto givenRootNode = std::make_shared<ModifiableNode>();
        givenRootNode->SetName("Scene");

        auto givenGameObject = std::make_shared<ModifiableNode>();
        givenGameObject->SetName("GameObject");

        auto givenComponent = std::make_shared<ModifiableNode>();
        givenComponent->SetName("Component");

        // Setup chain
        auto givenDocument = std::make_shared<ModifiableDocument>();
        givenDocument->SetRootElement(givenRootNode);
        givenRootNode->SetFirstChild(givenGameObject);
        givenGameObject->SetFirstChild(givenComponent);

        // Act
        std::shared_ptr<Scene> actual = m_testClass->Create(givenDocument);

        // Assert
        auto superScene = std::static_pointer_cast<SuperScene>(actual);
        ASSERT_TRUE(superScene) << "Scene was not a super scene";

        std::vector<std::shared_ptr<GameObject>> actualGo = superScene->GetChildrenIncludingPending();
        std::shared_ptr<GameComponent> actualComponent = actualGo.at(0)->GetComponent(componentTestType);
        ASSERT_FALSE(actualComponent);
    }
}