#pragma once
#include <string>
#include <unordered_map>

#include "PanelManager.h"

namespace SuperGameTools
{
    class MenuItemView;
}

namespace SuperGameTools
{
    /// <summary>
    /// Manages panels, the visibility and layouts.
    /// </summary>
    class SuperPanelManager : public virtual PanelManager
    {
    public:

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) override;

        /// <summary>
        /// Registers the given panel with the manager.
        /// Ensure a unique name is provided, this will fail the registration.
        /// </summary>
        /// <param name="panel">Panel to register. </param>
        /// <returns>
        /// True means could register.
        /// False means it could not be registered.
        /// </returns>
        virtual bool RegisterPanel(const std::shared_ptr<ToolsPanel>& panel) override;

        /// <summary>
        /// Subscribed to the logger events.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

    private:

        /// <summary>
        /// 
        /// </summary>
        struct PanelMenuPacket
        {
            std::shared_ptr<ToolsPanel> Panel;
            std::shared_ptr<MenuItemView> MenuItem;
        };

        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// All registered panels.
        /// </summary>
        std::unordered_map<std::string, PanelMenuPacket> m_panels;
    };
}
