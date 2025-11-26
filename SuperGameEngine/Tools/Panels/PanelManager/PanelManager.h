#pragma once
#include <memory>
#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace SuperGameTools
{
    class WindowPackage;
    class ToolsPanel;

    /// <summary>
    /// Manages panels, the visibility and layouts.
    /// </summary>
    class PanelManager : public FatedQuestLibraries::FEventObserver
    {
    public:
        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) = 0;

        /// <summary>
        /// Registers the given panel with the manager.
        /// Ensure a unique name is provided, this will fail the registration.
        /// </summary>
        /// <param name="panel">Panel to register. </param>
        /// <returns>
        /// True means could register.
        /// False means it could not be registered.
        /// </returns>
        virtual bool RegisterPanel(const std::shared_ptr<ToolsPanel>& panel) = 0;

        /// <summary>
        /// Registers the given panel with the manager.
        /// Ensure a unique name is provided, this will fail the registration.
        /// </summary>
        /// <param name="panel">Panel to register. </param>
        /// <returns>
        /// True means could register.
        /// False means it could not be registered.
        /// </returns>
        //virtual bool RegisterPanel(const std::weak_ptr<ToolsPanel>& panel) = 0;
    };
}
