#pragma once
#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    class MenuItemView;
}

namespace SuperGameTools
{
    /// <summary>
    /// Event arguments on events for menu items.
    /// </summary>
    class ToolsWindowShownArguments : public FatedQuestLibraries::FEventArguments
    {
    public:
        ToolsWindowShownArguments(bool newShown, const std::string& uniqueName)
        {
            m_newShownValue = newShown;
            m_uniqueName = uniqueName;
        }

        /// <summary>
        /// The value the window is now being set to when being hidden or shown.
        /// </summary>
        /// <returns>True means the window is now shown. </returns>
        bool GetNewShownValue() const
        {
            return m_newShownValue;
        }

        /// <summary>
        /// The unique name for the window used to identify any given window in the system.
        /// </summary>
        /// <returns>The unique name for the window used to identify any given window in the system. </returns>
        std::string GetUniqueName() const
        {
            return m_uniqueName;
        }

    private:
        /// <summary>
        /// A single item on a menu.
        /// </summary>
        bool m_newShownValue;

        /// <summary>
        /// The unique name for the window used to identify any given window in the system.
        /// </summary>
        std::string m_uniqueName;
    };
}

