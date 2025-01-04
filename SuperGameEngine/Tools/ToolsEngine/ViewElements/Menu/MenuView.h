#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace SuperGameTools
{
    class MenuItemView;

    /// <summary>
    /// Entire top menu bar.
    /// </summary>
    class MenuView
    {
    public:
        MenuView();
        ~MenuView();

        /// <summary>
        /// Get entire menu view.
        /// First key is the top level menu and menu item view are the items inside the menu.
        /// </summary>
        /// <returns>Entire menu view.</returns>
        std::unordered_map<std::string, std::vector<std::shared_ptr<MenuItemView>>> GetMenuItems() const;

        /// <summary>
        /// Adds a top level menu item.
        /// </summary>
        /// <param name="topLevelMenu">Top level selectable. </param>
        /// <returns>True means could add, false means already added. </returns>
        bool AddTopLevelMenuItem(const std::string& topLevelMenu);

        /// <summary>
        /// Add an item to the menu.
        /// </summary>
        /// <param name="topLevelMenu">Top level menu item name. Case-sensitive. </param>
        /// <param name="menuItem">Menu item to add. </param>
        /// <returns>True means could add. </returns>
        bool AddInnerMenuItem(const std::string& topLevelMenu, const std::shared_ptr<MenuItemView>& menuItem);

        /// <summary>
        /// Draws the menu.
        /// </summary>
        void Draw() const;

        /// <summary>
        /// Get menu item from the key.
        /// This is the preferred way to grab a menu item to link events as
        /// the key does not change once created and should not be changed often.
        /// </summary>
        /// <param name="key">Unique identifier. </param>
        /// <returns>The item from the list or empty if could not find. </returns>
        std::shared_ptr<MenuItemView> GetMenuItem(const std::string& key) const;

    private:
        /// <summary>
        /// All menu items.
        /// </summary>
        std::unordered_map<std::string, std::vector<std::shared_ptr<MenuItemView>>> m_menuItems;
    };
}

