#pragma once
#include <string>

#include "MenuType.h"
#include "ActionType.h"

namespace QuestLauncher
{
    /// <summary>
    /// A selectable item in the tray.
    /// </summary>
    class MenuItem
    {
    public:
        /// <summary>
        /// The label to display to the user.
        /// </summary>
        /// <returns>The label to display. </returns>
        virtual std::string GetLabel() const = 0;

        /// <summary>
        /// The way to handle the activation of this menu item.
        /// </summary>
        /// <returns>The way to handle the activation of this menu item. </returns>
        virtual ActionType GetActionType() const = 0;

        /// <summary>
        /// The method to display the menu item.
        /// </summary>
        /// <returns>The method to display the menu item. </returns>
        virtual MenuType GetMenuType() const = 0;
    };
}
