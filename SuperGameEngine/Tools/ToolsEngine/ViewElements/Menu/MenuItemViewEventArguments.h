#pragma once
#include <memory>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    class MenuItemView;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Event arguments on events for menu items.
    /// </summary>
    class MenuItemViewEventArguments : public FEventArguments
    {
    public:
        MenuItemViewEventArguments(const std::weak_ptr<MenuItemView>& item)
        {
            m_menuItem = item;
        }

        /// <summary>
        /// Item the event occured for.
        /// </summary>
        /// <returns>Item the event occured for. </returns>
        inline std::weak_ptr<MenuItemView> GetMenuItem() const
        {
            return m_menuItem;
        }

    private:
        /// <summary>
        /// A single item on a menu.
        /// </summary>
        std::weak_ptr<MenuItemView> m_menuItem;
    };
}

