#include "SuperPanelManager.h"
#include "Panels/ToolsPanel.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "ToolsEngine/Packages/WindowPackage.h"
#include "ToolsEngine/ViewElements/Menu/MenuItemView.h"
#include "ToolsEngine/ViewElements/Menu/MenuItemViewEventArguments.h"
#include "ToolsEngine/ViewElements/Menu/MenuView.h"
#include "ToolsEngine/ViewElements/Window/ToolsWindowShownArguments.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void SuperPanelManager::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
}

bool SuperPanelManager::RegisterPanel(const std::shared_ptr<ToolsPanel>& panel)
{
    std::string uniqueName = panel->GetPanelName();
    if (m_panels.contains(uniqueName))
    {
        Log::Error("Panel already registered with that name. Name: " + uniqueName,
            "SuperPanelManager::RegisterPanel(const std::shared_ptr<ToolsPanel>&)");
        return false;
    }


    auto menuItem = std::make_shared<MenuItemView>(uniqueName, uniqueName);
    m_windowPackage->GetTopMenu()->AddInnerMenuItem("Windows", menuItem);

    menuItem->OnSelected()->Subscribe(GetWeakDistributed());
    panel->OnWindowShownOrHidden()->Subscribe(GetWeakDistributed());

    menuItem->GetSelected()->SetValue(true);
    panel->ShowWindow();

    m_panels.insert_or_assign(uniqueName, PanelMenuPacket { .Panel = panel, .MenuItem = menuItem });
    return true;
}

void SuperPanelManager::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto menuArguments = std::dynamic_pointer_cast<MenuItemViewEventArguments>(arguments))
    {
        if (std::shared_ptr<MenuItemView> menuItem = menuArguments->GetMenuItem().lock())
        {
            if (m_panels.contains(menuItem->GetKey()))
            {
                bool currentSelected = menuItem->GetSelected()->GetValue();
                if (currentSelected)
                {
                    m_panels.at(menuItem->GetKey()).Panel->HideWindow();
                }
                else
                {
                    m_panels.at(menuItem->GetKey()).Panel->ShowWindow();
                }

                m_panels.at(menuItem->GetKey()).MenuItem->GetSelected()->SetValue(!currentSelected);
            }
        }
    }
    else if (auto windowShownArguments = std::dynamic_pointer_cast<ToolsWindowShownArguments>(arguments))
    {
        const std::string& uniqueName = windowShownArguments->GetUniqueName();
        if (m_panels.contains(uniqueName))
        {
            bool isShown = windowShownArguments->GetNewShownValue();
            m_panels.at(uniqueName).MenuItem->GetSelected()->SetValue(isShown);
        }
    }
}
