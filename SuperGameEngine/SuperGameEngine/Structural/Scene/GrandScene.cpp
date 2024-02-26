#include "GrandScene.h"
#include "../../Engine/Basic/GameTime.h"
#include "../../Structural/Spatial/Collision/CollisionDectection.h"

using namespace SuperGameEngine;

GrandScene::GrandScene(SDL_Renderer* renderer)
{
    m_directInput = new DirectInput();
    m_techniqueRenderer = new TechniqueRenderer(renderer);
    m_sceneLoadPackage = new SceneLoadPackage(
        new ContentManager(renderer),
        m_directInput, 
        m_techniqueRenderer);
    m_scenes = std::vector<Scene*>();

    m_collisionDectection = new CollisionDectection();
    m_sceneToGameObjectPackage = new SceneToGameObjectPackage(m_collisionDectection);


    Scene* scene = new Scene();
    scene->Setup(m_sceneLoadPackage, m_sceneToGameObjectPackage);
    m_scenes.push_back(scene);
}

GrandScene::~GrandScene()
{
    delete m_sceneLoadPackage;
    delete m_directInput;
    delete m_techniqueRenderer;
    delete m_sceneToGameObjectPackage;
    delete m_collisionDectection;
}

bool GrandScene::Update(Uint64 tick)
{
    GameTime gameTime = GameTime();
    gameTime.TicksSinceLastFrame = (int)tick;

    m_collisionDectection->RunCollisionUpdate();

    for (Scene* scene : m_scenes)
    {
        if (scene != nullptr)
        {
            scene->Update(gameTime);
        }
    }

    // TODO: This should run maybe once a minute or every 5 minutes.
    // Make Clean Techniques occur on a slower update loop #41
    m_techniqueRenderer->Clean();

    return true;
}


void GrandScene::Draw()
{
    m_techniqueRenderer->Draw();
    for (Scene* scene : m_scenes)
    {
        if (scene != nullptr)
        {
            scene->Draw();
        }
    }
}

void GrandScene::EventUpdate(SDL_Event& e)
{
    m_directInput->EventUpdate(e);
}
