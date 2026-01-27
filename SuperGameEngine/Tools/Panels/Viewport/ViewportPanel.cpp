#include "ViewportPanel.h"

#include "ToolsEngine/Packages/WindowPackage.h"
#include "../../FatedQuestLibraries.h"
#include "Engine/Basic/EngineControls.h"
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

    m_viewport = { 50, 50, 500, 250 };
    m_renderer = windowPackage->GetRenderer();
}

void ViewportPanel::Update()
{
    if (m_sizeHasChanged)
    {
        int newWidth = m_viewport.w;
        int newHeight = m_viewport.h;
        m_engineControls->SetNewViewportSize(newWidth, newHeight);
        m_sizeHasChanged = false;
    }
}

void ViewportPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowTopLeftBelowTitleBar = ImVec2(windowPos.x, windowPos.y + ImGui::GetFrameHeight());
        ImVec2 windowSize = ImGui::GetContentRegionAvail();

        SDL_Rect originalRect = m_viewport;
        int width = m_viewport.w;
        int height = m_viewport.h;

        m_viewport.x = static_cast<int>(windowTopLeftBelowTitleBar.x);
        m_viewport.y = static_cast<int>(windowTopLeftBelowTitleBar.y);
        m_viewport.w = static_cast<int>(windowSize.x);
        m_viewport.h = static_cast<int>(windowSize.y);

        int newWidth = m_viewport.w;
        int newHeight = m_viewport.h;
        if (width != newWidth || height != newHeight)
        {
            m_sizeHasChanged = true;
        }

        if (m_windowPackage->GetSDLToolsViewportRenderTexture())
        {
            if (m_windowPackage->GetSDLToolsViewportRenderTexture()->GetState() == PointerState::Active)
            {
                ImVec2 imageSize = ImVec2(width, height);
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
    return "ToolsMainViewport";
}

bool ViewportPanel::OnLoadOpenState() const
{
    return true;
}

void ViewportPanel::ResetPanel()
{
    SuperToolsPanel::ResetPanel();
}

void ViewportPanel::GiveEngineControls(const std::shared_ptr<SuperGameEngine::EngineControls>& engine)
{
    m_engineControls = engine;
}

void ViewportPanel::UpdateTheSDLViewport() const
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        SDL_RenderSetViewport(m_renderer->GetRenderer(), &m_viewport);
    }
}
