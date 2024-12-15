#include "ToolsEngine.h"
#include <SDL.h>
#include "../../Engine/Imgui/External/imgui.h"
#include "../Windows/GameViewport/GameViewport.h"
#include "../ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;

ToolsEngine::ToolsEngine()
{
    m_windowPackage = std::make_shared<WindowPackage>();
    m_haveSetup = false;
}

ToolsEngine::~ToolsEngine()
{
}

void ToolsEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
    
    m_windowPackage->SetRenderer(m_renderer);
}

void ToolsEngine::GiveSDLTexture(std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> sdlRenderTexture)
{
    m_sdlRenderTexture = sdlRenderTexture;

    m_windowPackage->SetSDLRenderTexture(m_sdlRenderTexture);
}

ApplicationOperationState ToolsEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ToolsEngine::Update(Uint64 ticks)
{
    if (!m_haveSetup)
    {
        std::shared_ptr<UpdateableObject> gameViewport = std::make_shared<GameViewport>();
        gameViewport->Setup(m_windowPackage);
        m_updatables.push_back(gameViewport);
        m_haveSetup = true;
    }

    for (const std::shared_ptr<UpdateableObject>& obj : m_updatables)
    {
        obj->Update();
    }

    return ApplicationOperationState::Running;
}

void ToolsEngine::Draw()
{
    for (const std::shared_ptr<UpdateableObject>& obj : m_updatables)
    {
        obj->Draw();
    }

    ImGui::Begin("Hello, Dear ImGui with SDL2");
    ImGui::TextColored(ImVec4(150, 150, 150, 150), "This is just a basic Hello World!");
    ImGui::End();
}

void ToolsEngine::WindowStart()
{
}

void ToolsEngine::WindowTeardown()
{
}
