#include "ToolsSelectionManager.h"

#include <ranges>

#include "Selectable.h"
#include "../../../FatedQuestLibraries.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SelectionChangedEventArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsSelectionManager::ToolsSelectionManager()
{
    m_onSelectionForAllGroups = std::make_shared<FEvent>();
    for (const SelectionGroup& group : ESelectionGroup::ToVector())
    {
        m_onSelectionByGroup.insert_or_assign(group, std::make_shared<FEvent>());
    }
}

std::shared_ptr<FEventSubscriptions> ToolsSelectionManager::OnSelectionChanged() const
{
    return m_onSelectionForAllGroups;
}

std::shared_ptr<FEventSubscriptions> ToolsSelectionManager::OnSelectionChanged(SelectionGroup selectionGroup) const
{
    if (m_onSelectionByGroup.contains(selectionGroup))
    {
        return m_onSelectionByGroup.at(selectionGroup);
    }

    Log::Error("Event not created for selection group. "
        "Regenerate the enum or ensure it is created in the constructor. "
        "Group: " + ESelectionGroup::ToString(selectionGroup),
        "ToolsSelectionManager::OnSelectionChanged(SelectionGroup)");

    return m_onSelectionForAllGroups;
}

void ToolsSelectionManager::AddToSelection(const std::weak_ptr<Selectable>& selectable)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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
            changedSelectables.emplace_back(selectable);
        }
    }

    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Add, changedSelectables);
    }
}

void ToolsSelectionManager::SetSelection(const std::weak_ptr<Selectable>& selectable)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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
            changedSelectables.emplace_back(selectable);
        }
    }

    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Set, changedSelectables);
    }
}

void ToolsSelectionManager::RemoveFromSelection(const std::weak_ptr<Selectable>& selectable)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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

            // Grab anything removed before so we can fire the event.
            bool foundOne = m_selectables.at(group).contains(guidKey);
            std::weak_ptr<Selectable> foundSelectable;
            if (foundOne)
            {
                foundSelectable = m_selectables.at(group).at(guidKey);
            }

            std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
            erase_if(selectables, [guidKey](const std::pair<std::string, std::weak_ptr<Selectable>>& pair)
                {
                    return pair.first == guidKey;
                });

            // Ensure the event will fire
            if (foundOne)
            {
                changedSelectables.emplace_back(foundSelectable);
            }

        }
    }

    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Remove, changedSelectables);
    }
}

void ToolsSelectionManager::AddToSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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
                    "ToolsSelectionManager::AddToSelection(std::vector<std::weak_ptr<Selectable>>)");
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
                selectables.insert_or_assign(guidKey, selectable);
                changedSelectables.emplace_back(selectable);
            }
        }
    }

    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Add, changedSelectables);
    }
}

void ToolsSelectionManager::SetSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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
                changedSelectables.emplace_back(selectable);
            }
        }
    }

    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Set, changedSelectables);
    }
}

void ToolsSelectionManager::RemoveFromSelection(const std::vector<std::weak_ptr<Selectable>>& selectables)
{
    std::vector<std::weak_ptr<Selectable>> changedSelectables;
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
                Log::Error("No Guid found on selectable. Could not remove from selection.",
                    "ToolsSelectionManager::RemoveFromSelection(std::vector<std::weak_ptr<Selectable>>)");
                continue;
            }

            std::unordered_set<SelectionGroup> selectableGroup = shared->GetSelectionGroup();
            for (const SelectionGroup& group : selectableGroup)
            {
                if (!m_selectables.contains(group))
                {
                    m_selectables.insert_or_assign(group, std::unordered_map<std::string, std::weak_ptr<Selectable>>());
                }

                // Grab anything removed before so we can fire the event.
                bool foundOne = m_selectables.at(group).contains(guidKey);
                std::weak_ptr<Selectable> foundSelectable;
                if (foundOne)
                {
                    foundSelectable = m_selectables.at(group).at(guidKey);
                }

                std::unordered_map<std::string, std::weak_ptr<Selectable>>& selectables = m_selectables.at(group);
                erase_if(selectables, [guidKey](const std::pair<std::string, std::weak_ptr<Selectable>>& pair)
                    {
                        return pair.first == guidKey;
                    });

                // Ensure the event will fire
                if (foundOne)
                {
                    changedSelectables.emplace_back(foundSelectable);
                }

            }
        }
    }
    if (!changedSelectables.empty())
    {
        CallOnSelection(SelectionChangeType::Remove, changedSelectables);
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

void ToolsSelectionManager::CallOnSelection(
    SelectionChangeType change, 
    const std::weak_ptr<Selectable>& selectable) const
{
    std::unordered_set<SelectionGroup> groups;
    if (auto selectableShared = selectable.lock())
    {
        for (const SelectionGroup& group : selectableShared->GetSelectionGroup())
        {
            groups.insert(group);
        }
    }

    auto arguments = std::make_shared<SelectionChangedEventArguments>(change, selectable);
    m_onSelectionForAllGroups->Invoke(arguments);
    for (const SelectionGroup& updatedGroup : groups)
    {
        if (m_onSelectionByGroup.contains(updatedGroup))
        {
            m_onSelectionByGroup.at(updatedGroup)->Invoke(arguments);
        }
    }
}

void ToolsSelectionManager::CallOnSelection(
    SelectionChangeType change,
    const std::vector<std::weak_ptr<Selectable>>& selectables) const
{
    std::unordered_set<SelectionGroup> groups;
    for (const std::weak_ptr<Selectable>& selectableWeak : selectables)
    {
        if (auto selectableShared = selectableWeak.lock())
        {
            for (const SelectionGroup& group : selectableShared->GetSelectionGroup())
            {
                groups.insert(group);
            }
        }
    }

    auto arguments = std::make_shared<SelectionChangedEventArguments>(change, selectables);
    m_onSelectionForAllGroups->Invoke(arguments);
    for (const SelectionGroup& updatedGroup : groups)
    {
        if (m_onSelectionByGroup.contains(updatedGroup))
        {
            m_onSelectionByGroup.at(updatedGroup)->Invoke(arguments);
        }
    }
}