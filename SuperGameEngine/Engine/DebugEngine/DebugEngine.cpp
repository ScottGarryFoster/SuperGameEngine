#include "DebugEngine.h"

#include "../Engine/Content/SuperContentManager.h"
#include "../Structural/GameObject/SuperGameObject.h"
#include "../Structural/Packages/SuperGrandScenePackage.h"
#include "../Engine/Basic/SuperGameTime.h"

// TODO: Reference all Components
#include "../Structural/InternalComponents/TestComponent/TestComponent.h"
#include "../Structural/Scene/GrandScene.h"
#include "../Structural/Scene/Scene.h"
#include "../Structural/Scene/SuperGrandScene.h"

using namespace SuperEngineDebug;
using namespace SuperGameEngine;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    if (!m_textureManager)
    {
        m_sceneLoadPackage = std::make_shared<SuperGrandScenePackage>();

        m_textureManager = std::make_shared<SuperTextureManager>(renderer);
        auto m_contentManager = std::make_shared<SuperContentManager>();
        m_contentManager->GiveSuperTextureManager(m_textureManager);
        m_sceneLoadPackage->SetContentManager(m_contentManager);

        m_gameTime = std::make_shared<SuperGameTime>();
    }
    else
    {
        // TODO: Create a way to update the Renderer.
    }
}

ApplicationOperationState DebugEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState DebugEngine::Update(Uint64 ticks)
{
    if (!m_haveLoaded)
    {
        m_haveLoaded = true;

        curr = ticks;

        m_grandScene = std::make_shared<SuperGrandScene>();
        m_grandScene->Setup(m_sceneLoadPackage);

        std::shared_ptr<Scene> scene = m_grandScene->CreateAndAddNewScene();
        m_go = scene->CreateAndAddNewGameObject();
        m_go->AddComponent("TestComponent");
    }

    m_gameTime->SetTicksSinceLastFrame(ticks);
    m_grandScene->Update(m_gameTime);


    if (m_gameTime->AllTime() > 5000)
    {
        if (m_go)
        {
            m_go->Destroy();
            m_go = std::shared_ptr<GameObject>();
        }

    }

    /*m_gameTime->SetTicksSinceLastFrame(ticks);
    if (m_go)
    {
        
        m_go = std::shared_ptr<SuperGameObject>();
    }
    else
    {
        m_go = std::make_shared<SuperGameObject>();
        m_go->Setup(m_loadPackage);
        m_go->AddComponent("TestComponent");
        m_go->Update(m_gameTime);
    }

    curr += ticks;
    if (curr > 10000)
    {
        m_haveRestartedWindow = true;
        curr = 0;
        std::cout << "Restart" << std::endl;
        return ApplicationOperationState::Restart;
    }*/

    return ApplicationOperationState::Running;
}

void DebugEngine::Draw()
{
    if (m_grandScene)
    {
        m_grandScene->Draw();
    }

}

void DebugEngine::WindowStart()
{
    if (m_haveLoaded)
    {
        std::vector<std::string> errors;
        m_textureManager->RemakeAllTextures(errors);
    }
}

void DebugEngine::WindowTeardown()
{
}
