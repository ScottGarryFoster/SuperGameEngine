#include "ViewportPanel.h"

#include "ToolsEngine/Packages/WindowPackage.h"
#include "../../FatedQuestLibraries.h"
#include "Engine/Graphics/Texture/SDLRendererReader.h"
#include "Engine/Graphics/Texture/SDLRendererState.h"
#include "Imgui/External/imgui.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ViewportPanel::ViewportPanel()
{
}

ViewportPanel::~ViewportPanel()
{
}

void ViewportPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    SetupWindow(m_windowPackage->GetColourPalette(), GetPanelUniqueName(),
        {
            .ResetLayoutUsingLayouts = true,
            .StartPosition = {.X = 50, .Y = 50}
        });

    m_viewport = { 50, 50, 500, 250 };;
    m_renderer = windowPackage->GetRenderer();
}

void ViewportPanel::Update()
{
}

void ViewportPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowTopLeftBelowTitleBar = ImVec2(windowPos.x, windowPos.y + ImGui::GetFrameHeight());
        ImVec2 windowSize = ImGui::GetContentRegionAvail();

        m_viewport.x = static_cast<int>(windowTopLeftBelowTitleBar.x);
        m_viewport.y = static_cast<int>(windowTopLeftBelowTitleBar.y);
        m_viewport.w = static_cast<int>(windowSize.x);
        m_viewport.h = static_cast<int>(windowSize.y);

        if (m_windowPackage->GetSDLToolsViewportRenderTexture())
        {
            if (m_windowPackage->GetSDLToolsViewportRenderTexture()->GetState() == PointerState::Active)
            {
                ImVec2 imageSize = ImVec2((float)1280, (float)720);
                SDL_Texture* texture = m_windowPackage->GetSDLToolsViewportRenderTexture()->Get();
                ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<void*>(texture)), imageSize);
            }
        }

        UpdateTheSDLViewport();
    }
    EndWindowRender(GetPanelName());
}

void ViewportPanel::TearDown()
{
}

void ViewportPanel::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
}

const char* ViewportPanel::GetPanelName() const
{
    return "Viewport";
}

const char* ViewportPanel::GetPanelUniqueName() const
{
    return "Viewport";
}

bool ViewportPanel::OnLoadOpenState() const
{
    return true;
}

void ViewportPanel::ResetPanel()
{
    SuperToolsPanel::ResetPanel();
}

void ViewportPanel::UpdateTheSDLViewport() const
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        SDL_RenderSetViewport(m_renderer->GetRenderer(), &m_viewport);
    }
}