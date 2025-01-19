#pragma once
#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// For OnDirtied events.
    /// </summary>
    class DirtiedDataEventArguments : public FEventArguments
    {
    public:
        DirtiedDataEventArguments(bool dirtyFlag)
        {
            m_currentDirtyFlag = dirtyFlag;
        }

        /// <summary>
        /// The current state of the dirty flag.
        /// </summary>
        /// <returns>
        /// The current state of the dirty flag.
        /// </returns>
        bool GetDirtyFlagState() const
        {
            return m_currentDirtyFlag;
        }

    private:

        /// <summary>
        /// The current state of the dirty flag.
        /// </summary>
        bool m_currentDirtyFlag;
    };
}
