#include "DebugEngine.h"

using namespace SuperEngineDebug;
using namespace SuperGameEngine;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
}

ApplicationOperationState DebugEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState DebugEngine::Update(Uint64 ticks)
{
    if (!m_haveLoaded)
    {
        m_texture = std::make_shared<Texture>(m_renderer);
        std::vector<std::string> errors;
        m_texture->LoadImageFromFile(R"(E:\Development\SuperGameEngine-Myriad\Products\Engine\TestImages\A_pressed.png)", errors);
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
    m_texture->Draw();
}

void DebugEngine::WindowStart()
{
    if (m_haveLoaded)
    {
        std::vector<std::string> errors;
        m_texture->Remake(errors);
    }
    else
    {
        originalTime = std::time(nullptr);

    }
}

void DebugEngine::WindowTeardown()
{
}
