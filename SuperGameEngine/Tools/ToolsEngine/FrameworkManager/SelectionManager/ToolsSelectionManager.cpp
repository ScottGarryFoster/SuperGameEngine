#include "ToolsSelectionManager.h"
#include "../../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void ToolsSelectionManager::AddToSelection(const std::weak_ptr<Selectable>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::AddToSelection(std::weak_ptr<Selectable>)");
}

void ToolsSelectionManager::SetSelection(const std::weak_ptr<Selectable>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::SetSelection(std::weak_ptr<Selectable>)");
}

void ToolsSelectionManager::RemoveFromSelection(const std::weak_ptr<Selectable>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::RemoveFromSelection(std::weak_ptr<Selectable>)");
}

void ToolsSelectionManager::AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::AddToSelection(std::vector<std::weak_ptr<Selectable>>)");
}

void ToolsSelectionManager::SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::SetSelection(std::vector<std::weak_ptr<Selectable>>)");
}

void ToolsSelectionManager::RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectable)
{
    Log::Error("Not implemented.", "ToolsSelectionManager::RemoveFromSelection(std::vector<std::weak_ptr<Selectable>>)");
}

std::vector<std::weak_ptr<Selectable>> ToolsSelectionManager::GetSelection(SelectionGroup selectionGroup) const
{
    Log::Error("Not implemented.", "ToolsSelectionManager::GetSelection(SelectionGroup)");
    return {};
}

std::vector<std::weak_ptr<Selectable>>
    ToolsSelectionManager::GetSelection(
    std::vector<SelectionGroup> selectionGroup) const
{
    Log::Error("Not implemented.", "ToolsSelectionManager::GetSelection(std::vector<SelectionGroup>)");
    return {};
}
