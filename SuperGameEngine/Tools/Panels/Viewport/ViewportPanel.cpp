#include "ViewportPanel.h"

#include "ViewportEngineAndPanelCommunication.h"
#include "ToolsEngine/Packages/WindowPackage.h"
#include "../../FatedQuestLibraries.h"
#include "Engine/Basic/EngineControls.h"
#include "Engine/Graphics/Texture/SDLRendererReader.h"
#include "Engine/Graphics/Texture/SDLRendererState.h"
#include "Engine/Graphics/Texture/SDLTextureChest.h"
#include "Imgui/External/imgui.h"
#include "Panels/ViewportTools/ViewportTools.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/PanelSelectionChangedArguments.h"
#include "ToolsEngine/ViewElements/Window/ToolsWindowShownArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ViewportPanel::ViewportPanel()
{
    m_sizeOrPositionHasChanged = true;
    m_viewportImage = RectangleInt(0, 0, 0, 0);

    m_thisPanelsName = PanelSelectionName::ToolsViewport;
    m_currentSelectedPanel = PanelSelectionName::None;
}

ViewportPanel::~ViewportPanel()
{
}

void ViewportPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    SetupWindow(m_windowPackage->GetColourPalette(), GetPanelUniqueName(),
        {
            .ResetLayoutUsingLayouts = false,
            .StartPosition = {.X = 50, .Y = 50}
        });

    m_viewport = { 50, 50, 500, 250 };
    m_renderer = windowPackage->GetRenderer();

    if (!m_viewportEngineAndPanelCommunication || !m_viewportTools)
    {
        Log::Error("No engine communication or viewport tools on setup."
                   "This means the viewport engine and tools will not be able to communicate.");
    }
    else
    {
        m_viewportEngineAndPanelCommunication->GiveViewportTools(m_viewportTools);
    }
}

void ViewportPanel::Update()
{
    m_viewportTools->Update();
    if (m_sizeHasChanged)
    {
        int newWidth = m_viewport.w;
        int newHeight = m_viewport.h;
        m_engineControls->SetNewViewportSize(newWidth, newHeight);
        m_sizeHasChanged = false;
    }

    if (m_sizeOrPositionHasChanged && m_viewportEngineAndPanelCommunication)
    {
        if (m_renderViewportTools)
        {
            // Ensure the position is adjusted for the frame when viewport tools are rendered.
            m_viewportEngineAndPanelCommunication->UpdateViewportLocation(
                m_viewportImage.GetLeft() - 26,
                m_viewportImage.GetTop() + 44,
                m_viewportImage.GetWidth(),
                m_viewportImage.GetHeight()
            );
        }
        else
        {
            // Ensure the position is adjusted when viewport tools are not rendered.
            m_viewportEngineAndPanelCommunication->UpdateViewportLocation(
                m_viewportImage.GetLeft() + 9,
                m_viewportImage.GetTop() + 9,
                m_viewportImage.GetWidth(),
                m_viewportImage.GetHeight()
            );
        }


        m_sizeOrPositionHasChanged = false;
    }
}

void ViewportPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        HandlePanelSelection(m_panelSelectionManager, m_thisPanelsName);

        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowTopLeftBelowTitleBar = ImVec2(windowPos.x, windowPos.y + ImGui::GetFrameHeight());
        ImVec2 windowSize = ImGui::GetContentRegionAvail();

        SDL_Rect originalRect = m_viewport;
        int width = m_viewport.w;
        int height = m_viewport.h;
        int originalX = m_viewport.x;
        int originalY = m_viewport.y;

        m_viewport.x = static_cast<int>(windowTopLeftBelowTitleBar.x);
        m_viewport.y = static_cast<int>(windowTopLeftBelowTitleBar.y);
        m_viewport.w = static_cast<int>(windowSize.x);
        m_viewport.h = static_cast<int>(windowSize.y);

        if (m_renderViewportTools)
        {
            m_viewport.x += 35;
            m_viewport.h -= 35;
            m_viewportTools->Draw();
        }

        int newWidth = m_viewport.w;
        int newHeight = m_viewport.h;
        int newX = m_viewport.x;
        int newY = m_viewport.y;
        if (width != newWidth || height != newHeight)
        {
            m_sizeHasChanged = true;
        }

        if (width != newWidth || height != newHeight || originalX != newX || originalY != newY)
        {
            m_viewportImage.SetLocation(newX, newY);
            m_viewportImage.SetSize(newWidth, newHeight);
            m_sizeOrPositionHasChanged = true;
        }

        if (m_windowPackage->GetSDLToolsViewportRenderTexture())
        {
            SDL_Texture* texture = m_windowPackage->GetSDLToolsViewportRenderTexture()->Get();
            if (texture)
            {
                ImVec2 imageSize = ImVec2(width, height);
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

void ViewportPanel::Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments)
{
    if (auto shownArgs = std::dynamic_pointer_cast<ToolsWindowShownArguments>(arguments))
    {
        if (shownArgs->GetUniqueName() != "ViewportTools")
        {
            return;
        }

        m_renderViewportTools = !shownArgs->GetNewShownValue();
    }
    else if (auto args = std::dynamic_pointer_cast<PanelSelectionChangedArguments>(arguments))
    {
        m_currentSelectedPanel = args->GetSelectionName();
    }
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

void ViewportPanel::GiveViewportTools(const std::shared_ptr<ViewportTools>& viewportTools)
{
    m_viewportTools = viewportTools;
}

void ViewportPanel::GiveViewportEngineAndPanelCommunication(
    const std::shared_ptr<ViewportEngineAndPanelCommunication>& engineAndPanelCommunication)
{
    m_viewportEngineAndPanelCommunication = engineAndPanelCommunication;
}

void ViewportPanel::UpdateTheSDLViewport() const
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        SDL_RenderSetViewport(m_renderer->GetRenderer(), &m_viewport);
    }
}
