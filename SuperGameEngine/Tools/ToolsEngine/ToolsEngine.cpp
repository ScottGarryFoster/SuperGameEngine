#include "ToolsEngine.h"
#include "../../Engine/Imgui/External/imgui.h"

using namespace SuperGameTools;

void ToolsEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
}

ApplicationOperationState ToolsEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ToolsEngine::Update(Uint64 ticks)
{
    return ApplicationOperationState::Running;
}

void ToolsEngine::Draw()
{
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
