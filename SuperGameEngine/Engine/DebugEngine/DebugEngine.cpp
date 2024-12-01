#include "DebugEngine.h"

using namespace SuperEngineDebug;
using namespace SuperGameEngine;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    if (!m_textureManager)
    {
        m_textureManager = std::make_unique<SuperTextureManager>(renderer);
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
        m_supertexture = m_textureManager->GetTexture(R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\A_pressed.png)");
        m_haveLoaded = true;

        curr = ticks;
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
    m_supertexture->Draw();
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
