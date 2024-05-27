#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/TestComponent.h"
#include "../Components/Visual/SpriteComponent.h"
#include "../Components/Spatial/TransformComponent.h"
#include "../Components/Example/UserInputTestComponent.h"
#include "../Components/Gameplay/PlayerControllerComponent.h"
#include "../Components/Colliders/BoxColliderComponent.h"
#include "SceneToGameObjectPackage.h"
#include "../Components/Colliders/CircleColliderComponent.h"
#include "../Components/Physics/SimpleRigidbodyComponent.h"
#include "../Components/Visual/TextComponent.h"
#include "../Scene/GrandScene.h"

using namespace SuperGameEngine;

Scene::Scene()
{
    m_sceneLoadPackage = nullptr;
    m_sceneToGameObjectPackage = nullptr;
    m_loaded = false;

    m_gameObjects = std::vector<std::shared_ptr<GameObject>>();
    m_guid = GUIDHelpers::CreateGUID();
}

Scene::~Scene()
{

}

std::shared_ptr<Guid> Scene::GetGuid()
{
    return m_guid;
}

void Scene::Setup(SceneLoadPackage* sceneLoadPackage, SceneToGameObjectPackage* sceneToGameObjectPackage)
{
    if (!sceneLoadPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), 
            FString("Setup"), FString("sceneLoadPackage is null"));
        return;
    }
    m_sceneLoadPackage = sceneLoadPackage;

    if (!sceneToGameObjectPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), 
            FString("Setup"), FString("sceneToGameObjectPackage is null"));
        return;
    }
    m_sceneToGameObjectPackage = sceneToGameObjectPackage;
    

    std::shared_ptr<GameObject> go = CreateNewGameObject();
    go->GetTransformComponent()->SetLocation(200, 100);

    std::shared_ptr<PlayerControllerComponent> pc = go->AddComponent<PlayerControllerComponent>("PlayerControllerComponent");

    pc->SetSpeed(300);
    pc->UseKeyboard(false);
    go->AddComponent<SimpleRigidbodyComponent>("SimpleRigidbodyComponent");

    std::shared_ptr<BoxColliderComponent> box = go->AddComponent<BoxColliderComponent>("BoxColliderComponent");
    FVector2D l = FVector2D(0, 0);
    FVector2D s = FVector2D(100, 200);
    box->SetColliderLocation(l);
    box->SetColliderSize(s);


    std::shared_ptr<GameObject> go2 = CreateNewGameObject();
    go2->GetTransformComponent()->SetLocation(500, 500);

    std::shared_ptr<CircleColliderComponent> box2 = go2->AddComponent<CircleColliderComponent>("CircleColliderComponent");
    FVector2D l2 = FVector2D(0, 0);
    FVector2D s2 = FVector2D(100, 200);
    box2->SetColliderLocation(l2);
    box2->SetColliderSize(50);

    go2->AddComponent<SimpleRigidbodyComponent>("SimpleRigidbodyComponent");

    std::shared_ptr<PlayerControllerComponent> player = go2->AddComponent<PlayerControllerComponent>("PlayerControllerComponent");

    player->UseKeyboard(true);

    go2->AddComponent<SpriteComponent>("SpriteComponent");
    go2->AddComponent<TextComponent>("TextComponent");
    go2->AddComponent("TestToolsComponent");

    m_gameObjects.push_back(go2);

    m_loaded = true;
}

bool Scene::Update(const GameTime gameTime)
{
    if (!m_loaded)
    {
        return true;
    }

    std::vector<std::shared_ptr<GameObject>> allObjects = m_gameObjects;
    for (size_t i = 0; i < allObjects.size(); ++i)
    {
        std::shared_ptr<GameObject> gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            if (gameObject->IsDestroyed())
            {
                VectorHelpers::RemoveValue(m_gameObjects, gameObject);
                m_sceneToGameObjectPackage->GetScene()->
                    OnGameObjectDestroyed(*gameObject->GetGuid());
            }
            else
            {
                gameObject->Update(gameTime);
            }
        }
    }

    return true;
}

void Scene::FixedUpdate(const GameTime gameTime)
{
    if (!m_loaded)
    {
        return;
    }

    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        std::shared_ptr<GameObject> gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            gameObject->FixedUpdate(gameTime);
        }
    }
}

void Scene::Draw()
{
    if (!m_loaded)
    {
        return;
    }

    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        std::shared_ptr<GameObject> gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            gameObject->Draw();
        }
    }
}

std::shared_ptr<GameObject> Scene::CreateNewGameObject()
{
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
    go->SetScene(GetGuid());
    go->Setup(m_sceneLoadPackage, m_sceneToGameObjectPackage);
    m_gameObjects.push_back(go);
    return go;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetAllGameObjects()
{
    return m_gameObjects;
}

void Scene::OnGameObjectDestroyed(const Guid& guid)
{
    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        std::shared_ptr<GameObject> gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            gameObject->OnGameObjectDestroyed(guid);
        }
    }
}
