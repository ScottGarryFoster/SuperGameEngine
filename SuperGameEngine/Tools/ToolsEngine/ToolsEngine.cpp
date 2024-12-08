#include "ToolsEngine.h"
#include "../../Engine/Imgui/External/imgui.h"
#include "../Windows/GameViewport/GameViewport.h"

using namespace SuperGameTools;

void ToolsEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
    m_renderer = renderer;
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
        gameViewport->Setup(m_renderer);
        m_updatables.push_back(gameViewport);
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
