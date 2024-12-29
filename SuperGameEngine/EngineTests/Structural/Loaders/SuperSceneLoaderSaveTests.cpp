#include "../../../Engine/Structural/Loaders/SuperSceneLoader.h"
#include <memory>
#include <gtest/gtest.h>

#include "../../../../FatedQuest.Libraries/StandardObjects/Object/GUID/GUIDHelpers.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/AllReferences.h"
#include "../../../Engine/DebugEngine/DebugLogger.h"
#include "../../../Engine/Structural/Packages/SuperSceneLoadPackage.h"
#include "../../../Engine/Structural/Scene/Scene.h"
#include "../../../Engine/Structural/Scene/SuperScene.h"
#include "../../../Engine/Engine/Basic/SuperGameTime.h"
#include "../../../Engine/Structural/GameObject/GameObject.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;
namespace SuperGameEngineTests_Structural_Loaders
{
    class SuperSceneLoaderSaveTests : public ::testing::Test
    {
    public:
        SuperSceneLoaderSaveTests()
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

    TEST_F(SuperSceneLoaderSaveTests, Save_ReturnsADocument_WhenGivenASceneReference)
    {
        // Arrange
        auto givenScene = std::make_shared<SuperScene>();

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        ASSERT_TRUE(actual);
    }

    TEST_F(SuperSceneLoaderSaveTests, Save_ReturnsEmpty_WhenGivenEmpty)
    {
        // Arrange
        std::shared_ptr<Scene> givenScene = {};

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        ASSERT_FALSE(actual);
    }

    TEST_F(SuperSceneLoaderSaveTests, Save_ReturnsARootNodeWithSceneName_WhenGivenAScene)
    {
        // Arrange
        auto givenScene = std::make_shared<SuperScene>();

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        std::shared_ptr<StoredDocumentNode> actualNode = actual->GetRoot();
        ASSERT_TRUE(actualNode);
        ASSERT_EQ("Scene", actualNode->Name());
    }

    TEST_F(SuperSceneLoaderSaveTests, Save_ReturnsAttributeSavingGuid_WhenSceneHasOne)
    {
        // Arrange
        auto givenScene = std::make_shared<SuperScene>();
        std::shared_ptr<Guid> guid = givenScene->GetGuid();

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        std::shared_ptr<StoredDocumentNode> actualNode = actual->GetRoot();
        std::shared_ptr<StoredDocumentAttribute> actualGuid = actualNode->Attribute("Guid");
        ASSERT_TRUE(actualGuid);
        ASSERT_EQ(GUIDHelpers::ToString(*guid), actualGuid->Value())
            << GUIDHelpers::ToString(*guid) << " != " << actualGuid->Value();
    }

    TEST_F(SuperSceneLoaderSaveTests, Save_ReturnsChildNodeAsGameObject_WhenSceneHasGameObject)
    {
        // Arrange
        auto givenScene = std::make_shared<SuperScene>();
        givenScene->Setup(m_sceneLoadPackage);
        givenScene->CreateAndAddNewGameObject();

        // Ensures all objects are 'alive'
        givenScene->Update(std::make_shared<SuperGameTime>());

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        std::shared_ptr<StoredDocumentNode> actualNode = actual->GetRoot();
        std::shared_ptr<StoredDocumentNode> firstChild = actualNode->GetFirstChild();
        ASSERT_TRUE(firstChild);
        ASSERT_EQ("GameObject", firstChild->Name());
    }

    TEST_F(SuperSceneLoaderSaveTests, Save_SaveGuidInGameObject_WhenGiven)
    {
        // Arrange
        auto givenScene = std::make_shared<SuperScene>();
        givenScene->Setup(m_sceneLoadPackage);
        std::shared_ptr<GameObject> go = givenScene->CreateAndAddNewGameObject();

        // Ensures all objects are 'alive'
        givenScene->Update(std::make_shared<SuperGameTime>());

        // Act
        std::shared_ptr<StoredDocument> actual = m_testClass->Save(givenScene);

        // Assert
        std::shared_ptr<StoredDocumentNode> actualNode = actual->GetRoot();
        std::shared_ptr<StoredDocumentNode> firstChild = actualNode->GetFirstChild();
        std::shared_ptr<StoredDocumentAttribute> actualGuid = firstChild->Attribute("Guid", false);
        ASSERT_TRUE(actualGuid);
        ASSERT_TRUE(GUIDHelpers::ToString(*go->GetGuid()) == actualGuid->Value())
            << GUIDHelpers::ToString(*go->GetGuid()) << " != "
            << actualGuid->Value();
    }
}