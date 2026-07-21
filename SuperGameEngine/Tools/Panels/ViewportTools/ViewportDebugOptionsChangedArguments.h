#pragma once
#include "ViewportDebugOption.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    /// <summary>
    /// Invoked when selected tool is changed.
    /// </summary>
    class ViewportDebugOptionsChanged : public FatedQuestLibraries::FEventArguments
    {
    public:

        ViewportDebugOptionsChanged(ViewportDebugOption option)
        {
            m_debugOption = option;
        }

        /// <summary>
        /// The changed debug option.
        /// </summary>
        /// <returns>The changed debug option. </returns>
        ViewportDebugOption GetDebugOption() const
        {
            return m_debugOption;
        }

    private:

        /// <summary>
        /// The options updated.
        /// </summary>
        ViewportDebugOption m_debugOption;
    };
}
