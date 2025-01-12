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
        // Get the guid as this is the key for the dictionaries.
        std::string guidKey = {};
        if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
        {
            guidKey = guidPointer->ToString();
        }
        else
        {
            Log::Error("No Guid found on selectable. Could not add to selection.",
                "ToolsSelectionManager::AddToSelection(std::weak_ptr<Selectable>)");
            return;
        }

        std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
        for (const SelectionGroup& group : selectableGroup)
        {
            if (!m_selectables.contains(group))
            {
                m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            selectables.insert_or_assign(guidKey, selectable);
        }
    }
}

void ToolsSelectionManager::SetSelection(const std::weak_ptr<Selectable>& selectable)
{
    if (auto shared = selectable.lock())
    {
        // Get the guid as this is the key for the dictionaries.
        std::string guidKey = {};
        if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
        {
            guidKey = guidPointer->ToString();
        }
        else
        {
            Log::Error("No Guid found on selectable. Could not add to selection.",
                "ToolsSelectionManager::SetSelection(std::weak_ptr<Selectable>)");
            return;
        }

        std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
        for (const SelectionGroup& group : selectableGroup)
        {
            if (!m_selectables.contains(group))
            {
                m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            selectables.clear();
            selectables.insert_or_assign(guidKey, selectable);
        }
    }
}

void ToolsSelectionManager::RemoveFromSelection(const std::weak_ptr<Selectable>& selectable)
{
    if (auto shared = selectable.lock())
    {
        // Get the guid as this is the key for the dictionaries.
        std::string guidKey = {};
        if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
        {
            guidKey = guidPointer->ToString();
        }
        else
        {
            Log::Error("No Guid found on selectable. Could not remove from selection.",
                "ToolsSelectionManager::RemoveFromSelection(std::weak_ptr<Selectable>)");
            return;
        }

        std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
        for (const SelectionGroup& group : selectableGroup)
        {
            if (!m_selectables.contains(group))
            {
                m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            erase_if(selectables, [guidKey](const std::pair<std::string, std::weak_ptr<Selectable>>& pair)
                {
                    return pair.first == guidKey;
                });
        }
    }
}

void ToolsSelectionManager::AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    for (const std::weak_ptr<Selectable>& selectable : selectables)
    {
        AddToSelection(selectable);
    }
}

void ToolsSelectionManager::SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    std::unordered_set<SelectionGroup> clearedGroups;
    for (const std::weak_ptr<Selectable>& selectable : selectables)
    {
        if (auto shared = selectable.lock())
        {
            // Get the guid as this is the key for the dictionaries.
            std::string guidKey = {};
            if (std::shared_ptr<Guid> guidPointer = shared->GetGuid())
            {
                guidKey = guidPointer->ToString();
            }
            else
            {
                Log::Error("No Guid found on selectable. Could not add to selection.",
                    "ToolsSelectionManager::SetSelection(std::weak_ptr<Selectable>)");
                continue;
            }

            std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
            for (const SelectionGroup& group : selectableGroup)
            {
                if (!m_selectables.contains(group))
                {
                    m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
                }

                std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
                if (!clearedGroups.contains(group))
                {
                    // Only clear this once for the entire group of selectables.
                    selectables.clear();
                    clearedGroups.insert(group);
                }
                
                selectables.insert_or_assign(guidKey, selectable);
            }
        }
    }
}

void ToolsSelectionManager::RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    for (const std::weak_ptr<Selectable>& selectable : selectables)
    {
        RemoveFromSelection(selectable);
    }
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
