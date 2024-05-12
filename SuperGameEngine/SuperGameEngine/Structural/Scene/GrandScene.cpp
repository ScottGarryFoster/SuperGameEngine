#include "GrandScene.h"
#include "../../Engine/Basic/GameTime.h"
#include "../../Structural/Spatial/Collision/CollisionDectection.h"
#include "../../Structural/GameObject/GameObject.h"

using namespace SuperGameEngine;

GrandScene::GrandScene(SDL_Renderer* renderer)
{
    m_collisionDectection = new CollisionDectection();
    m_directInput = new DirectInput();
    m_techniqueRenderer = new TechniqueRenderer(renderer);
    m_frameTimings = new FrameTiming();
    m_sceneLoadPackage = new SceneLoadPackage(
        new ContentManager(renderer),
        m_directInput, 
        m_techniqueRenderer,
        m_frameTimings,
        m_collisionDectection);
    m_scenes = std::vector<Scene*>();
    m_sceneToGameObjectPackage = new SceneToGameObjectPackage(m_collisionDectection, this);


    Scene* scene = new Scene();
    scene->Setup(m_sceneLoadPackage, m_sceneToGameObjectPackage);
    m_scenes.push_back(scene);

    m_currentFixedUpdateTicks = 0;
}

GrandScene::~GrandScene()
{
    delete m_sceneLoadPackage;
    delete m_directInput;
    delete m_techniqueRenderer;
    delete m_sceneToGameObjectPackage;
    delete m_collisionDectection;
    delete m_frameTimings;
}

bool GrandScene::Update(Uint64 tick)
{
    m_currentFixedUpdateTicks += tick;
    m_singleSecondCountdown += tick;
    if (m_singleSecondCountdown >= 1000)
    {
        m_singleSecondCountdown -= 1000;
        //Logger::Info(FString("FPS: ") + (int)(1000.0f / tick));
    }


    bool runFixedUpdate = false;

    GameTime fixedUpdateGameTime = GameTime();
    fixedUpdateGameTime.TicksSinceLastFrame = m_frameTimings->GetFixedUpdateLoopTiming();

    int timesToRunFixedUpdate = 0;
    while (m_currentFixedUpdateTicks >= m_frameTimings->GetFixedUpdateLoopTiming())
    {
        runFixedUpdate = true;
        m_currentFixedUpdateTicks -= m_frameTimings->GetFixedUpdateLoopTiming();

        // If the refresh is really good you want the fixed update to run multiple times
        // in a frame. This is the number of times to run this frame.
        ++timesToRunFixedUpdate;
    }

    while (timesToRunFixedUpdate > 0)
    {
        --timesToRunFixedUpdate;

        m_collisionDectection->RunCollisionUpdate();
        for (Scene* scene : m_scenes)
        {
            if (scene != nullptr)
            {
                scene->FixedUpdate(fixedUpdateGameTime);
            }
        }
    }

    GameTime updateGameTime = GameTime();
    updateGameTime.TicksSinceLastFrame = (int)tick;
    for (Scene* scene : m_scenes)
    {
        if (scene != nullptr)
        {
            scene->Update(updateGameTime);
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

std::shared_ptr<GameObject> GrandScene::CreateNewGameObject(GameObject* caller)
{
    if (caller == nullptr)
    {
        return m_scenes[0]->CreateNewGameObject();
    }

    for (Scene* scene : m_scenes)
    {
        if (scene->GetGuid() == caller->GetSceneGuid())
        {
            return scene->CreateNewGameObject();
        }
    }

    return m_scenes[0]->CreateNewGameObject();
}
