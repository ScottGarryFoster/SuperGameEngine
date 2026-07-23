#include "SuperToolsPanel.h"

using namespace SuperGameTools;

void SuperToolsPanel::GivePanelSelectionManager(const std::shared_ptr<PanelSelectionManager>& panelSelectionManager)
{
    m_panelSelectionManager = panelSelectionManager;
}

bool SuperToolsPanel::AreSelected() const
{
    return m_thisPanelsName == m_currentSelectedPanel;
}
