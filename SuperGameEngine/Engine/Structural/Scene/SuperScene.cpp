#include "SuperScene.h"
#include "../../FatedQuestReferences.h"
#include "../GameObject/SuperGameObject.h"
#include "../../Structural/Packages/SuperGameObjectLoadPackage.h"
#include "../../Structural/Packages/SceneLoadPackage.h"
#include "../Component/GameComponent.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperScene::SuperScene()
{
    m_guid = GUIDHelpers::CreateGUID();
    m_isSetup = false;
    m_isPendingGameObjects = false;
}

SuperScene::~SuperScene()
{

}

std::shared_ptr<Guid> SuperScene::GetGuid() const
{
    return m_guid;
}

void SuperScene::Setup(std::shared_ptr<SceneLoadPackage> grandScenePackage)
{
    m_scenePackage = grandScenePackage;

    m_gameObjectPackage = std::make_shared<SuperGameObjectLoadPackage>();
    m_gameObjectPackage->SetContentManager(m_scenePackage->GetContentManager());

    m_isSetup = true;
}

bool SuperScene::IsSetup() const
{
    return m_isSetup;
}

void SuperScene::Update(const std::shared_ptr<GameTime> gameTime)
{
    if (!m_isSetup) return;

    if (m_isPendingGameObjects)
    {
        MovePendingToMain();
        m_isPendingGameObjects = false;
    }

    bool atLeastOneGameObjectDestroyed = false;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->IsDestroyed())
        {
            atLeastOneGameObjectDestroyed = true;
        }
        else
        {
            go->Update(gameTime);
        }
    }

    if (atLeastOneGameObjectDestroyed)
    {
        DestroyAllDestroyedGameObjects();
    }
}

void SuperScene::Draw() const
{
    if (!m_isSetup) return;

    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (!go->IsDestroyed())
        {
            go->Draw();
        }
    }
}

std::shared_ptr<GameObject> SuperScene::CreateAndAddNewGameObject()
{
    std::shared_ptr<GameObject> gameObject =
        std::make_shared<SuperGameObject>();
    gameObject->SetScene(m_guid);
    gameObject->Setup(m_gameObjectPackage);

    m_pendingGameObjects.push_back(gameObject);
    m_isPendingGameObjects = true;

    return gameObject;
}

void SuperScene::Destroy()
{
    m_isDestroyed = true;
}

bool SuperScene::IsDestroyed() const
{
    return m_isDestroyed;
}

void SuperScene::MovePendingToMain()
{
    for (const std::shared_ptr<GameObject>& go : m_pendingGameObjects)
    {
        m_gameObjects.push_back(go);
    }

    m_pendingGameObjects.clear();
}

void SuperScene::DestroyAllDestroyedGameObjects()
{
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->IsDestroyed())
        {
            DestroyGameObject(go);
        }
    }

    std::erase_if(
        m_gameObjects,
        [](const std::shared_ptr<GameObject>& o)
        { return o->IsDestroyed(); });
}

void SuperScene::DestroyGameObject(std::shared_ptr<GameObject> gameObject)
{
    std::vector<std::pair<std::string, std::shared_ptr<GameComponent>>> allComponents =
        gameObject->GetAllComponents();
    for (const auto typeComponent : allComponents)
    {
        typeComponent.second->Destroy();
    }

    gameObject->Destroy();
}
