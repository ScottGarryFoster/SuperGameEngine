#include "ToolsPanelSelectionManager.h"

#include "PanelSelectionChangedArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsPanelSelectionManager::ToolsPanelSelectionManager()
{
    m_panelSelectionName = PanelSelectionName::None;
    m_onSelectionChanged = std::make_shared<FEvent>();
}

void ToolsPanelSelectionManager::UpdateNewSelection(PanelSelectionName newSelection)
{
    m_panelSelectionName = newSelection;
    m_onSelectionChanged->Invoke(std::make_shared<PanelSelectionChangedArguments>(newSelection));
}

void ToolsPanelSelectionManager::DeselectIfSelected(PanelSelectionName deselection)
{
    if (m_panelSelectionName!= PanelSelectionName::None && m_panelSelectionName == deselection)
    {
        UpdateNewSelection(PanelSelectionName::None);
    }
}

PanelSelectionName ToolsPanelSelectionManager::CurrentSelection() const
{
    return m_panelSelectionName;
}

std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> ToolsPanelSelectionManager::OnSelectionChanged() const
{
    return m_onSelectionChanged;
}

