#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/TestComponent.h"
using namespace SuperGameEngine;

Scene::Scene(SceneLoadPackage* sceneLoadPackage)
{
    m_sceneLoadPackage = sceneLoadPackage;
    m_intialised = false;
    m_texture = nullptr;
}

Scene::~Scene()
{

}

bool Scene::Update(GameTime gameTime)
{
    if (!m_intialised)
    {
        GameObject* go = new GameObject();
        //go->Update(gameTime);
        go->AddComponent<TestComponent>();
        //go->AddActualComponent(new TestComponent());
        m_intialised = true;

        //ContentManager* content = m_sceneLoadPackage->GetContentManager();
        //m_texture = content->GetTexture(FString("E:/Development/SuperGameEngine-SDL/collideCircle.png"));
    }

    return true;
}

void Scene::Draw()
{
    if (m_texture != nullptr)
    {
        m_texture->Draw();
    }
}