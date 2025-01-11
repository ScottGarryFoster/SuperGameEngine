#pragma once
#include "ActionType.h"
#include "MenuItem.h"

namespace QuestLauncher
{
    /// <summary>
    /// A selectable item in the tray.
    /// </summary>
    class DebugMenuItem : public MenuItem
    {
    public:
        DebugMenuItem(const std::string& label, ActionType actionType, MenuType menuType);

        /// <summary>
        /// The label to display to the user.
        /// </summary>
        /// <returns>The label to display. </returns>
        virtual std::string GetLabel() const override;

        /// <summary>
        /// The way to handle the activation of this menu item.
        /// </summary>
        /// <returns>The way to handle the activation of this menu item. </returns>
        virtual ActionType GetActionType() const override;

        /// <summary>
        /// The method to display the menu item.
        /// </summary>
        /// <returns>The method to display the menu item. </returns>
        virtual MenuType GetMenuType() const override;

    private:
        /// <summary>
        /// The label to display to the user.
        /// </summary>
        std::string m_label;

        /// <summary>
        /// The way to handle the activation of this menu item.
        /// </summary>
        ActionType m_actionType;

        /// <summary>
        /// The method to display the menu item.
        /// </summary>
        MenuType m_menuType;
    };
}
