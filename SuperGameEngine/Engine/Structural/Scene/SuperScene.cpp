#include "SuperScene.h"
#include "../../FatedQuestReferences.h"
#include "../GameObject/SuperGameObject.h"
#include "../../Structural/Packages/GameObjectLoadPackage.h"
#include "../../Structural/Packages/SceneLoadPackage.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperScene::SuperScene()
{
    m_guid = GUIDHelpers::CreateGUID();
    m_isSetup = false;
    m_isPendingGameObjects = false;
    m_isDestroyed = false;
}

SuperScene::~SuperScene()
{

}

std::shared_ptr<Guid> SuperScene::GetGuid() const
{
    return m_guid;
}

void SuperScene::SetGuid(const std::shared_ptr<Guid>& guid)
{
    if (!guid)
    {
        Log::Error("Given empty guid.", "SuperScene::SetGuid(std::shared_ptr<Guid>)");
        return;
    }

    m_guid = guid;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (auto sgo = std::dynamic_pointer_cast<SuperGameObject>(go))
        {
            sgo->SetScene(m_guid);
        }
    }
}

void SuperScene::Setup(std::shared_ptr<SceneLoadPackage> grandScenePackage)
{
    m_scenePackage = grandScenePackage;

    m_gameObjectPackage = m_scenePackage->GetGameObjectLoadPackage();
    if (!m_gameObjectPackage->GetContentManager())
    {
        Log::Error("No content manager found when setting up GameObject.",
            "SuperGameObject::Setup(std::shared_ptr<GameObjectLoadPackage>)");
    }

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

    // TODO: Consider making this occur once every 5 seconds to avoid lag. As Destroyed objects functionally do not exist it should not matter.
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

void SuperScene::DestroyImmediately()
{
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        go->DestroyImmediately();
    }

    m_gameObjects = std::vector<std::shared_ptr<GameObject>>();

    // Let the game object do any last minute destruction.
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        go->OnDestroyed();
    }
}

void SuperScene::OnDestroyed()
{
    // No reaction.
}

std::vector<std::shared_ptr<GameObject>> SuperScene::GetChildren() const
{
    std::vector<std::shared_ptr<GameObject>> returnVector;
    returnVector.insert(returnVector.end(), m_gameObjects.begin(), m_gameObjects.end());

    // Ensure destroyed ones are not counted.
    erase_if(returnVector, [](const std::shared_ptr<GameObject>& go) { return go->IsDestroyed(); });
    return returnVector;
}

std::vector<std::shared_ptr<GameObject>> SuperScene::GetChildrenIncludingPending() const
{
    std::vector<std::shared_ptr<GameObject>> returnVector;
    returnVector.insert(returnVector.end(), m_gameObjects.begin(), m_gameObjects.end());
    returnVector.insert(returnVector.end(), m_pendingGameObjects.begin(), m_pendingGameObjects.end());

    // Ensure destroyed ones are not counted.
    erase_if(returnVector, [](const std::shared_ptr<GameObject>& go) { return go->IsDestroyed(); });

    return returnVector;
}

void SuperScene::Load(const std::shared_ptr<StoredDocumentNode>& documentNode)
{
}

std::shared_ptr<StoredDocumentNode> SuperScene::Save()
{
    return std::shared_ptr<StoredDocumentNode>();
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
    std::vector<std::shared_ptr<GameObject>> destroyed;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->IsDestroyed())
        {
            go->DestroyImmediately();
            destroyed.push_back(go);
        }
    }

    std::erase_if(
        m_gameObjects,
        [](const std::shared_ptr<GameObject>& o)
        { return o->IsDestroyed(); });

    for (const std::shared_ptr<GameObject>& go : destroyed)
    {
        go->OnDestroyed();
    }
}