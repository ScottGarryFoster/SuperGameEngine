#pragma once
#include "ViewportToolsType.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    /// <summary>
    /// Defines the viewport tools selected in event calls.
    /// </summary>
    class ViewportToolsButtonSelectedArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        ViewportToolsButtonSelectedArguments(ViewportToolsType buttonType)
        {
            m_viewportButtonType = buttonType;
        }

        /// <summary>
        /// The button selected.
        /// </summary>
        /// <returns>The button selected. </returns>
        ViewportToolsType GetButtonSelected() const
        {
            return m_viewportButtonType;
        }

    private:

        /// <summary>
        /// The button these arguments describe.
        /// </summary>
        ViewportToolsType m_viewportButtonType;
    };
}
