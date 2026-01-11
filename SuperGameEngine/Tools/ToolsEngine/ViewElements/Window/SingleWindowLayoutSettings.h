#pragma once
#include "../../../../../FatedQuest.Libraries/StandardObjects/Position/Simple/PVector2F.h"

namespace SuperGameTools
{
    /// <summary>
    /// Defines the layout for a single window.
    /// </summary>
    /// <remarks>
    /// Note the window being referred to as here is the ImGui window,
    /// referred to as the panel in the reset of the system
    /// </remarks>
    struct SingleWindowLayoutSettings
    {
    public:

        /// <summary>
        /// True means use layouts to reset the position.
        /// </summary>
        /// <remakrs>
        /// Until we setup layouts outside of ImGui this is the turn off for these.
        /// This allows us to reset windows to these settings without going full
        /// custom layouts
        /// </remarks>
        bool ResetLayoutUsingLayouts;

        /// <summary>
        /// The starting position of the window.
        /// </summary>
        FatedQuestLibraries::PVector2F StartPosition;

        /// <summary>
        /// The pivot to position the window from;
        /// 0 is top left, 0.5f would be the center and 1 is the bottom right.
        /// </summary>
        FatedQuestLibraries::PVector2F StartPivot;
    };
}
