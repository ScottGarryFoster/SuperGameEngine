#include "SuperToolsPanel.h"

#include "ToolsEngine/FrameworkManager/SelectionManager/PanelSelectionManager.h"

using namespace SuperGameTools;

void SuperToolsPanel::GivePanelSelectionManager(const std::shared_ptr<PanelSelectionManager>& panelSelectionManager)
{
    m_panelSelectionManager = panelSelectionManager;
}

bool SuperToolsPanel::AreSelected() const
{
    return m_thisPanelsName == m_currentSelectedPanel;
}

bool SuperToolsPanel::HideWindow()
{
    m_panelSelectionManager->DeselectIfSelected(m_thisPanelsName);
    return ToolsWindowElement::HideWindow();
}
