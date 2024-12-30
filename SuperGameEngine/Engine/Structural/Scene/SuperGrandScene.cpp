#include "SuperGrandScene.h"

#include "SuperScene.h"
#include "../../Engine/Content/ContentManager.h"
#include "../../Engine/Content/SceneStorageCache.h"
#include "../Packages/GrandScenePackage.h"
#include "../Packages/SuperSceneLoadPackage.h"

using namespace SuperGameEngine;

void SuperGrandScene::Setup(std::shared_ptr<GrandScenePackage> grandScenePackage)
{
    m_grandScenePackage = grandScenePackage;
    m_sceneLoadPackage = grandScenePackage->GetSceneLoadPackage();

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

    bool atLeastOneSceneIsDestroyed = false;
    for (const std::shared_ptr<Scene>& scenes : m_scenes)
    {
        if (scenes->IsDestroyed())
        {
            atLeastOneSceneIsDestroyed = true;
        }
        else
        {
            scenes->Update(gameTime);
        }
    }

    // TODO: Consider making this occur once every 5 seconds to avoid lag. As Destroyed objects functionally do not exist it should not matter.
    if (atLeastOneSceneIsDestroyed)
    {
        DestroyAllDestroyedScenes();
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

std::shared_ptr<Scene> SuperGrandScene::CreateAndAddNewScene(const std::string& filepath)
{
    if (!m_sceneLoadPackage->GetContentManager()->Scene())
    {
        Log::Error("No scene cache was found.", "SuperGrandScene::CreateAndAddNewScene(std::string)");
        return {};
    }

    std::shared_ptr<Scene> newScene = m_sceneLoadPackage->GetContentManager()->Scene()->GetScene(filepath);
    m_pendingScenes.push_back(newScene);
    m_isPendingScenes = true;

    return newScene;
}

void SuperGrandScene::Destroy()
{
    m_isDestroyed = true;
}

bool SuperGrandScene::IsDestroyed() const
{
    return m_isDestroyed;
}

void SuperGrandScene::MovePendingToMain()
{
    for (const std::shared_ptr<Scene>& go : m_pendingScenes)
    {
        m_scenes.push_back(go);
    }

    m_pendingScenes.clear();
}

void SuperGrandScene::DestroyAllDestroyedScenes()
{
    std::vector<std::shared_ptr<Scene>> destroyed;
    for (const std::shared_ptr<Scene>& scene : m_scenes)
    {
        if (scene->IsDestroyed())
        {
            scene->DestroyImmediately();
            destroyed.push_back(scene);
        }
    }

    std::erase_if(
        m_scenes,
        [](const std::shared_ptr<Scene>& s)
        { return s->IsDestroyed(); });

    for (const std::shared_ptr<Scene>& scene : destroyed)
    {
        scene->OnDestroyed();
    }
}
