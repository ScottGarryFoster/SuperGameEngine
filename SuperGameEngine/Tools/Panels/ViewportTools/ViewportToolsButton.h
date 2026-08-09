#pragma once
#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace FatedQuestLibraries
{
    class FEventSubscriptions;
}

namespace SuperGameTools
{
    /// <summary>
    /// A button rendered for the viewport.
    /// </summary>
    class ViewportToolsButton : public FatedQuestLibraries::FEventObserver
    {
    public:

        /// <summary>
        /// Draw the button.
        /// </summary>
        virtual void Draw() = 0;

        /// <summary>
        /// Called when this button is selected.
        /// </summary>
        /// <returns>Called when this button is selected. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSelected() const = 0;

        /// <summary>
        /// Select this button.
        /// </summary>
        virtual void Select() = 0;
    };
}
