#include "GameViewport.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Graphics/Texture/SDLRendererReader.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameEngine;
using namespace SuperGameTools;

void GameViewport::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_viewport = { 50, 50, 500, 250 };;
    m_renderer = windowPackage->GetRenderer();
    m_windowPackage = windowPackage;
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

    if (m_windowPackage->GetSDLRenderTexture())
    {
        if (m_windowPackage->GetSDLRenderTexture()->GetState() == PointerState::Active)
        {
            ImVec2 imageSize = ImVec2((float)1280, (float)720);
            SDL_Texture* texture = m_windowPackage->GetSDLRenderTexture()->Get();
            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<void*>(texture)), imageSize);
        }
    }



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
