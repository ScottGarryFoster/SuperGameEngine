#include "ViewportToolsPanel.h"
#include "SuperViewportTools.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/PanelSelectionChangedArguments.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;

ViewportToolsPanel::ViewportToolsPanel()
{
    m_thisPanelsName = PanelSelectionName::ViewportToolsUndocked;
    m_currentSelectedPanel = PanelSelectionName::None;
}

ViewportToolsPanel::~ViewportToolsPanel()
{
}

void ViewportToolsPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    auto superTools = std::make_shared<SuperViewportTools>(m_windowPackage);
    superTools->Setup();
    m_viewportTools = superTools;

    SetupWindow(m_windowPackage->GetColourPalette(), GetPanelUniqueName(),
        {
            .ResetLayoutUsingLayouts = false,
            .StartPosition = {.X = 50, .Y = 50}
        });
}

void ViewportToolsPanel::Update()
{
}

void ViewportToolsPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        HandlePanelSelection(m_panelSelectionManager, m_thisPanelsName);
        m_viewportTools->Draw();
    }
    EndWindowRender(GetPanelName());
}

void ViewportToolsPanel::TearDown()
{
}

void ViewportToolsPanel::Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments)
{
    if (auto args = std::dynamic_pointer_cast<PanelSelectionChangedArguments>(arguments))
    {
        m_currentSelectedPanel = args->GetSelectionName();
    }
}

const char* ViewportToolsPanel::GetPanelName() const
{
    return "ViewportTools";
}

const char* ViewportToolsPanel::GetPanelUniqueName() const
{
    return "ViewportTools";
}

bool ViewportToolsPanel::OnLoadOpenState() const
{
    return false;
}

void ViewportToolsPanel::ResetPanel()
{
    SuperToolsPanel::ResetPanel();
}

std::shared_ptr<ViewportTools> ViewportToolsPanel::GetViewportTools() const
{
    return m_viewportTools;
}
