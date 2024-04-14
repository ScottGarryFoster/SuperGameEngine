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
using namespace SuperGameEngine;

Scene::Scene()
{
    m_sceneLoadPackage = nullptr;
    m_sceneToGameObjectPackage = nullptr;
    m_loaded = false;
    m_texture = nullptr;

    m_gameObjects = std::vector<GameObject*>();
}

Scene::~Scene()
{

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
    

    GameObject* go = new GameObject(true);
    go->Setup(m_sceneLoadPackage, m_sceneToGameObjectPackage);
    go->GetTransform()->SetLocation(500, 100);

    std::shared_ptr<PlayerControllerComponent> pc = go->AddComponent<PlayerControllerComponent>();
    pc->SetSpeed(1500);
        
    go->AddComponent<SimpleRigidbodyComponent>();
    std::shared_ptr<CircleColliderComponent> box = go->AddComponent<CircleColliderComponent>();
    //std::shared_ptr<BoxColliderComponent> box = go->AddComponent<BoxColliderComponent>();
    FVector2D l = FVector2D(50, 50);
    FVector2D s = FVector2D(100, 200);
    box->SetColliderLocation(l);
    //box->SetColliderSize(s);
    box->SetColliderSize(35);

    go->AddComponent<SpriteComponent>();


    m_gameObjects.push_back(go);



    GameObject* go2 = new GameObject(true);
    go2->Setup(m_sceneLoadPackage, m_sceneToGameObjectPackage);
    go2->GetTransform()->SetLocation(100, 100);

    std::shared_ptr<CircleColliderComponent> box2 = go2->AddComponent<CircleColliderComponent>();
    //std::shared_ptr<BoxColliderComponent> box2 = go2->AddComponent<BoxColliderComponent>();
    FVector2D l2 = FVector2D(0, 0);
    FVector2D s2 = FVector2D(100, 200);
    box2->SetColliderLocation(l2);
    //box2->SetColliderSize(s2);
    box2->SetColliderSize(50);

    go2->AddComponent<SimpleRigidbodyComponent>();
    std::shared_ptr<PlayerControllerComponent> player = go2->AddComponent<PlayerControllerComponent>();
    player->UseKeyboard(false);

    go2->AddComponent<SpriteComponent>();
    m_gameObjects.push_back(go2);

    m_loaded = true;
}

bool Scene::Update(GameTime gameTime)
{
    if (!m_loaded)
    {
        return true;
    }

    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        GameObject* gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            gameObject->Update(gameTime);
        }
    }

    return true;
}

void Scene::FixedUpdate(GameTime gameTime)
{
    if (!m_loaded)
    {
        return;
    }

    for (size_t i = 0; i < m_gameObjects.size(); ++i)
    {
        GameObject* gameObject = m_gameObjects[i];
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
        GameObject* gameObject = m_gameObjects[i];
        if (m_gameObjects[i] != nullptr)
        {
            gameObject->Draw();
        }
    }
}