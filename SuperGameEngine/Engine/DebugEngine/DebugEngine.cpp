#include "DebugEngine.h"

#include "../Engine/Content/SuperContentManager.h"
#include "../Structural/GameObject/SuperGameObject.h"
#include "../Structural/Packages/SuperSceneLoadPackage.h"
#include "../Engine/Basic/SuperGameTime.h"

#include "../Structural/InternalComponents/TestComponent/TestComponent.h"

using namespace SuperEngineDebug;
using namespace SuperGameEngine;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    if (!m_textureManager)
    {
        m_sceneLoadPackage = std::make_shared<SuperSceneLoadPackage>();

        auto m_contentManager = std::make_shared<SuperContentManager>();
        m_textureManager = std::make_shared<SuperTextureManager>(renderer);
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
        //m_superTexture = m_textureManager->GetTexture(R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\A_pressed.png)");
        m_haveLoaded = true;

        curr = ticks;
    }

    m_gameTime->SetTicksSinceLastFrame(ticks);
    if (m_go)
    {
        
        m_go = std::shared_ptr<SuperGameObject>();
    }
    else
    {
        m_go = std::make_shared<SuperGameObject>();
        m_go->Setup(m_sceneLoadPackage);
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
    }

    return ApplicationOperationState::Running;
}

void DebugEngine::Draw()
{
    //m_superTexture->Draw();
    if (m_go)
    {
        m_go->Draw();
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
