#include "DebugMenuItem.h"

using namespace QuestLauncher;

DebugMenuItem::DebugMenuItem(const std::string& label, ActionType actionType, MenuType menuType)
{
    m_label = label;
    m_actionType = actionType;
    m_menuType = menuType;
}

std::string DebugMenuItem::GetLabel() const
{
    return m_label;
}

ActionType DebugMenuItem::GetActionType() const
{
    return m_actionType;
}

MenuType DebugMenuItem::GetMenuType() const
{
    return m_menuType;
}
