#include "SuperGrandScene.h"

#include "SuperScene.h"
#include "../Packages/GrandScenePackage.h"
#include "../Packages/SuperSceneLoadPackage.h"

using namespace SuperGameEngine;

void SuperGrandScene::Setup(std::shared_ptr<GrandScenePackage> grandScenePackage)
{
    m_grandScenePackage = grandScenePackage;

    // Setup Scene load package
    auto superSceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();
    superSceneLoadPackage->SetContentManager(m_grandScenePackage->GetContentManager());
    m_sceneLoadPackage = superSceneLoadPackage;

    m_isSetup = true;
}

bool SuperGrandScene::IsSetup() const
{
    return m_isSetup;
}

void SuperGrandScene::Update(const std::shared_ptr<GameTime> gameTime)
{
    if (!m_isSetup) return;

    if (m_isPendingScenes)
    {
        MovePendingToMain();
        m_isPendingScenes = false;
    }

    for (const std::shared_ptr<Scene>& scenes : m_scenes)
    {
        scenes->Update(gameTime);
    }
}

void SuperGrandScene::Draw() const
{
    if (!m_isSetup) return;

    for (const std::shared_ptr<Scene>& scenes : m_scenes)
    {
        scenes->Draw();
    }
}

std::shared_ptr<Scene> SuperGrandScene::CreateAndAddNewScene()
{
    std::shared_ptr<Scene> scene =
        std::make_shared<SuperScene>();
    scene->Setup(m_sceneLoadPackage);

    m_pendingScenes.push_back(scene);
    m_isPendingScenes = true;

    return scene;
}

void SuperGrandScene::MovePendingToMain()
{
    for (const std::shared_ptr<Scene>& go : m_pendingScenes)
    {
        m_scenes.push_back(go);
    }

    m_pendingScenes.clear();
}
