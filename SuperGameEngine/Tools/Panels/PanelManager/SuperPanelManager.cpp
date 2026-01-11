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
    std::string uniqueName = panel->GetPanelUniqueName();
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
    m_panels.insert_or_assign(uniqueName, PanelMenuPacket { .Panel = panel, .MenuItem = menuItem });

    SetupPanelForPanelOpen(panel);

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

                // It is important to poll the state again in case the panel has jumped in and stopped the panel opening or closing.
                bool currentState = m_panels.at(menuItem->GetKey()).Panel->OpenState();
                m_panels.at(menuItem->GetKey()).MenuItem->GetSelected()->SetValue(currentState);
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

std::shared_ptr<ToolsPanel> SuperPanelManager::TryFindPanel(const std::string& key) const
{
    if (m_panels.contains(key))
    {
        return m_panels.at(key).Panel;
    }

    return {};
}

void SuperPanelManager::SetupPanelForPanelOpen(const std::shared_ptr<ToolsPanel>& panel) const
{
    bool openState = panel->OnLoadOpenState();
    if (openState)
    {
        panel->ShowWindow();
    }
    else
    {
        panel->HideWindow();
    }

    bool openStateAfterwards = panel->OnLoadOpenState();
    if (openState != openStateAfterwards)
    {
        // The panel itself is stopping us from changing the state.
        return;
    }

    const char* uniqueName = panel->GetPanelUniqueName();
    if (m_panels.contains(uniqueName))
    {
        m_panels.at(uniqueName).MenuItem->GetSelected()->SetValue(openState);
    }
}
