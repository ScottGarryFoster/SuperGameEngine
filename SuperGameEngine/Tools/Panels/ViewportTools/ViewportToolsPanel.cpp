#include "ViewportToolsPanel.h"
#include "SuperViewportTools.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;

ViewportToolsPanel::ViewportToolsPanel()
{
}

ViewportToolsPanel::~ViewportToolsPanel()
{
}

void ViewportToolsPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    m_viewportTools = std::make_shared<SuperViewportTools>(m_windowPackage);

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
        m_viewportTools->Draw();
    }
    EndWindowRender(GetPanelName());
}

void ViewportToolsPanel::TearDown()
{
}

void ViewportToolsPanel::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
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
