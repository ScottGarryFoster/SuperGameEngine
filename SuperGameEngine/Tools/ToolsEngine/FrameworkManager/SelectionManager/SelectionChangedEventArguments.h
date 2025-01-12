#pragma once
#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"
#include "SelectionChangeType.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Arguments used when a selection changed.
    /// </summary>
    class SelectionChangedEventArguments : public FEventArguments
    {
    public:
        SelectionChangedEventArguments(SelectionChangeType changeType)
        {
            m_changeType = changeType;
        }

        /// <summary>
        /// How the selection changed.
        /// </summary>
        /// <returns>How the selection changed. </returns>
        inline SelectionChangeType GetSelectionChangeType() const
        {
            return m_changeType;
        }

    private:
        /// <summary>
        /// How the selection changed.
        /// </summary>
        SelectionChangeType m_changeType;
    };
}
