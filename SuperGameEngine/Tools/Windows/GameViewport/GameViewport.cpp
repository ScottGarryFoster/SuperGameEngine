#include "GameViewport.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Graphics/Texture/SDLRendererReader.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;

void GameViewport::Setup(std::shared_ptr<SuperGameEngine::SDLRendererReader> renderer)
{
    m_viewport = { 50, 50, 500, 250 };;
    m_renderer = renderer;
}

void GameViewport::Update()
{
    
}

void GameViewport::Draw()
{
    ImGui::Begin("My Window");
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowTopLeftBelowTitleBar = ImVec2(windowPos.x, windowPos.y + ImGui::GetFrameHeight());
    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    m_viewport.x = static_cast<int>(windowTopLeftBelowTitleBar.x);
    m_viewport.y = static_cast<int>(windowTopLeftBelowTitleBar.y);
    m_viewport.w = static_cast<int>(windowSize.x);
    m_viewport.h = static_cast<int>(windowSize.y);

    UpdateTheSDLViewport();
    ImGui::End();
}

void GameViewport::TearDown()
{
}

void GameViewport::UpdateTheSDLViewport()
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        SDL_RenderSetViewport(m_renderer->GetRenderer(), &m_viewport);
    }
}
