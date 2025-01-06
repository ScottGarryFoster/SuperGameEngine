#include "MenuView.h"

#include <ranges>

#include "../../../ImGuiIncludes.h"
#include "MenuItemView.h"
#include "../ColoursAndStyles/ColoursAndStyles.h"

using namespace SuperGameTools;

MenuView::MenuView(const std::shared_ptr<ColoursAndStyles>& coloursAndStyles)
{
    m_menuItems = {};
    m_coloursAndStyles = coloursAndStyles;

    m_menuBarState = false;
    m_menuBarHoverState = false;
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

    if (!m_isHovered.contains(topLevelMenu))
    {
        m_isHovered.insert_or_assign(topLevelMenu, false);
    }

    if (!m_isOpen.contains(topLevelMenu))
    {
        m_isOpen.insert_or_assign(topLevelMenu, false);
    }

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

    if (!m_isHovered.contains(topLevelMenu))
    {
        m_isHovered.insert_or_assign(topLevelMenu, false);
    }

    if (!m_isOpen.contains(topLevelMenu))
    {
        m_isOpen.insert_or_assign(topLevelMenu, false);
    }

    return true;
}

void MenuView::Draw()
{
    m_coloursAndStyles->SetTopMenuColoursAndStyles();
    if (ImGui::BeginMainMenuBar())
    {
        for (const auto& topLevelMenu : m_menuItems)
        {
            if (CreateMenuMenu(topLevelMenu.first.c_str()))
            {
                std::vector<std::shared_ptr<MenuItemView>> menuItems = topLevelMenu.second;
                for (const auto& menuItem : menuItems)
                {
                    menuItem->Draw();
                }

                ImGui::EndMenu();
            }
            EndMenuMenu();
        }
    }
    ImGui::EndMainMenuBar();
    m_coloursAndStyles->PopTopMenuColoursAndStyles();

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

bool MenuView::CreateMenuMenu(const char* name)
{
    m_coloursAndStyles->SetMenuColoursAndStyles(m_isOpen.at(name), m_isHovered.at(name));
    m_isOpen.at(name) = ImGui::BeginMenu(name);
    m_isHovered.at(name) = ImGui::IsItemHovered();

    return m_isOpen.at(name);
}

void MenuView::EndMenuMenu()
{

    m_coloursAndStyles->PopMenuColoursAndStyles();
}
