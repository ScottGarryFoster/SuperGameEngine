#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/TestComponent.h"
#include "../Components/Visual/SpriteComponent.h"
#include "../Components/Spatial/TransformComponent.h"
#include "../Components/Example/UserInputTestComponent.h"
#include "../Components/Gameplay/PlayerControllerComponent.h"
using namespace SuperGameEngine;

Scene::Scene()
{
    m_sceneLoadPackage = nullptr;
    m_loaded = false;
    m_texture = nullptr;

    m_gameObjects = std::vector<GameObject*>();
}

Scene::~Scene()
{

}

void Scene::Setup(SceneLoadPackage* sceneLoadPackage)
{
    if (!sceneLoadPackage)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Setup"), FString("sceneLoadPackage is null"));
        return;
    }
    m_sceneLoadPackage = sceneLoadPackage;

    GameObject* go = new GameObject();
    go->Setup(m_sceneLoadPackage);
    go->GetTransform()->SetLocation(100, 0);
    go->AddComponent<PlayerControllerComponent>();
    go->AddComponent<SpriteComponent>();
    m_gameObjects.push_back(go);
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