#include "GrandScene.h"
#include "../../Engine/Basic/GameTime.h"

using namespace SuperGameEngine;

GrandScene::GrandScene(SDL_Renderer* renderer)
{
    m_sceneLoadPackage = new SceneLoadPackage(new ContentManager(renderer));
    m_scenes = std::vector<Scene*>();

    Scene* scene = new Scene();
    scene->Setup(m_sceneLoadPackage);
    m_scenes.push_back(scene);
}

GrandScene::~GrandScene()
{
    delete m_sceneLoadPackage;
}

bool GrandScene::Update(Uint64 tick)
{
    GameTime gameTime = GameTime();
    gameTime.TicksSinceLastFrame = (int)tick;

    for (Scene* scene : m_scenes)
    {
        if (scene != nullptr)
        {
            scene->Update(gameTime);
        }
    }

    return true;
}


void GrandScene::Draw()
{
    for (Scene* scene : m_scenes)
    {
        if (scene != nullptr)
        {
            scene->Draw();
        }
    }
}