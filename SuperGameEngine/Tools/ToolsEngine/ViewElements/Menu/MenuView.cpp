#include "MenuView.h"

#include <ranges>

#include "../../../ImGuiIncludes.h"
#include "MenuItemView.h"

using namespace SuperGameTools;

MenuView::MenuView()
{
    m_menuItems = {};
}

MenuView::~MenuView()
{
}

std::unordered_map<std::string, std::vector<std::shared_ptr<MenuItemView>>> MenuView::GetMenuItems() const
{
    return m_menuItems;
}


bool MenuView::AddTopLevelMenuItem(const std::string& topLevelMenu)
{
    auto it = m_menuItems.find(topLevelMenu);
    if (it != m_menuItems.end())
    {
        // Found the item already.
        return false;
    }

    m_menuItems.try_emplace(topLevelMenu, std::vector<std::shared_ptr<MenuItemView>>());
    return true;
}

bool MenuView::AddInnerMenuItem(const std::string& topLevelMenu, const std::shared_ptr<MenuItemView>& menuItem)
{
    auto it = m_menuItems.find(topLevelMenu);
    if (it == m_menuItems.end())
    {
        // Could not find the top level.
        return false;
    }

    m_menuItems.at(topLevelMenu).emplace_back(menuItem);
    return true;
}

void MenuView::Draw() const
{
    if (ImGui::BeginMainMenuBar())
    {
        for (const auto& topLevelMenu : m_menuItems)
        {
            if (ImGui::BeginMenu(topLevelMenu.first.c_str()))
            {
                std::vector<std::shared_ptr<MenuItemView>> menuItems = topLevelMenu.second;
                for (const auto& menuItem : menuItems)
                {
                    menuItem->Draw();
                }

                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();
    }
}

std::shared_ptr<MenuItemView> MenuView::GetMenuItem(const std::string& key) const
{
    if (key.empty())
    {
        Log::Error("Key is empty.", "MenuView::GetMenuItem(std::string)");
        return {};
    }

    for (const auto& menuItemViews : m_menuItems | std::views::values)
    {
        for (const std::shared_ptr<MenuItemView>& menuItem: menuItemViews)
        {
            if (menuItem->GetKey() == key)
            {
                return menuItem;
            }
        }
    }

    return {};
}
