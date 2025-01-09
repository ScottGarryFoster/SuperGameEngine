#include "ToolsSelectionManager.h"

#include <ranges>

#include "Selectable.h"
#include "../../../FatedQuestLibraries.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void ToolsSelectionManager::AddToSelection(const std::weak_ptr<Selectable>& selectable)
{
    if (auto shared = selectable.lock())
    {
        std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
        for (const SelectionGroup& group : selectableGroup)
        {
            if (!m_selectables.contains(group))
            {
                m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
            {
                std::string guid = guidPointer->ToString();
                selectables.insert_or_assign(guid, selectable);
            }
            else
            {
                Log::Error("No Guid found on selectable. Could not add to selection.",
                    "ToolsSelectionManager::AddToSelection(std::weak_ptr<Selectable>)");
                return;
            }
        }
    }
}

void ToolsSelectionManager::SetSelection(const std::weak_ptr<Selectable>& selectable)
{
    if (auto shared = selectable.lock())
    {
        std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
        for (const SelectionGroup& group : selectableGroup)
        {
            if (!m_selectables.contains(group))
            {
                m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
            {
                std::string guid = guidPointer->ToString();
                selectables.clear();
                selectables.insert_or_assign(guid, selectable);
            }
            else
            {
                Log::Error("No Guid found on selectable. Could not add to selection.",
                    "ToolsSelectionManager::SetSelection(std::weak_ptr<Selectable>)");
                return;
            }
        }
    }
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
    std::vector<std::weak_ptr<Selectable>> returnVector;
    if (m_selectables.contains(selectionGroup))
    {
        std::unordered_map<std::string, std::weak_ptr<Selectable>> selectionsInGroup = m_selectables.at(selectionGroup);
        for (const std::weak_ptr<Selectable>& selectable : selectionsInGroup | std::views::values)
        {
            returnVector.emplace_back(selectable);
        }
    }

    return returnVector;
}

std::vector<std::weak_ptr<Selectable>>
    ToolsSelectionManager::GetSelection(
    std::vector<SelectionGroup> selectionGroup) const
{
    std::unordered_map<std::string, std::weak_ptr<Selectable>> selectables;
    for (const SelectionGroup& group : selectionGroup)
    {
        if (m_selectables.contains(group))
        {
            std::unordered_map<std::string, std::weak_ptr<Selectable>> selectionsInGroup = m_selectables.at(group);
            for (const std::pair<const std::string, std::weak_ptr<Selectable>>& selectionPair : selectionsInGroup)
            {
                selectables.insert(selectionPair);
            }
        }
    }

    std::vector<std::weak_ptr<Selectable>> returnVector;
    for (const std::pair<const std::string, std::weak_ptr<Selectable>>& selectable : selectables)
    {
        returnVector.emplace_back(selectable.second);
    }

    return returnVector;
}
