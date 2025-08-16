#pragma once
#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"
#include "SelectionChangeType.h"
#include "Selectable.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class Selectable;

    /// <summary>
    /// Arguments used when a selection changed.
    /// </summary>
    class SelectionChangedEventArguments : public FEventArguments
    {
    public:
        SelectionChangedEventArguments(
            SelectionChangeType changeType)
        {
            m_changeType = changeType;
        }

        SelectionChangedEventArguments(
            SelectionChangeType changeType,
            const std::weak_ptr<Selectable>& selectable)
        {
            m_changeType = changeType;
            m_selectables.emplace_back(selectable);
            if (auto selectablePtr = selectable.lock())
            {
                m_guids.insert(selectablePtr->GetGuid());
            }
        }

        SelectionChangedEventArguments(
            SelectionChangeType changeType,
            const std::vector<std::weak_ptr<Selectable>>& selectables)
        {
            m_changeType = changeType;
            m_selectables = selectables;
            for (const std::weak_ptr<Selectable>& selectable : selectables)
            {
                if (auto selectablePtr = selectable.lock())
                {
                    m_guids.insert(selectablePtr->GetGuid());
                }
            }
        }

        /// <summary>
        /// How the selection changed.
        /// </summary>
        /// <returns>How the selection changed. </returns>
        inline SelectionChangeType GetSelectionChangeType() const
        {
            return m_changeType;
        }

        /// <summary>
        /// The selectables added, removed or set.
        /// </summary>
        /// <returns>The selectables added, removed or set.</returns>
        inline std::vector<std::weak_ptr<Selectable>> GetSelectablesChanged() const
        {
            return m_selectables;
        }

        /// <summary>
        /// Gets just the guids for all selectables.
        /// This is faster if you want to purge selectables on mass as it uses a hash map.
        /// </summary>
        /// <returns>Gets just the guids for all selectables. </returns>
        std::unordered_set<std::shared_ptr<const Guid>> GetAllSelectableGuids() const
        {
            return m_guids;
        }

    private:
        /// <summary>
        /// How the selection changed.
        /// </summary>
        SelectionChangeType m_changeType;

        /// <summary>
        /// The selectables added, removed or set.
        /// </summary>
        std::vector<std::weak_ptr<Selectable>> m_selectables;

        /// <summary>
        /// All guids of the selectables added, removed or set.
        /// </summary>
        std::unordered_set<std::shared_ptr<const Guid>> m_guids;
    };
}
