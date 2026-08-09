#include "MainMenuBar.h"
#include "../../ImGuiIncludes.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuView.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemView.h"
#include "Panels/ToolsPanel.h"
#include "Panels/PanelManager/PanelManager.h"
#include "ToolsEngine/ViewElements/Menu/MenuItemViewEventArguments.h"

using namespace SuperGameTools;

void MainMenuBar::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_mainView = std::make_shared<MenuView>(windowPackage->GetColourPalette());
    m_windowPackage = windowPackage;

    m_mainView->AddTopLevelMenuItem("File");
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileNew","New Scene"));
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileOpen","Open"));
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileSave","Save"));
    m_mainView->AddTopLevelMenuItem("Windows");

    // Setup all menu items which should open up a panel.
    m_openPanelMenuItems.insert_or_assign("FileProjectProperties", "ProjectProperties");
}

void MainMenuBar::Update()
{
}

void MainMenuBar::Draw()
{
    m_mainView->Draw();
}

void MainMenuBar::TearDown()
{
}

std::shared_ptr<MenuView> MainMenuBar::GetTopMenuBar() const
{
    return m_mainView;
}

void MainMenuBar::SetupPostPanels() const
{
    if (!m_windowPackage)
    {
        Log::Error("Setup was not called before Panel Setup. Some menu items will be missing",
            "MainMenuBar::SetupPostPanels()");
        return;
    }

    auto menuItemView = std::make_shared<MenuItemView>("FileProjectProperties", "Project Properties");
    m_mainView->AddInnerMenuItem("File", menuItemView);
    menuItemView->OnSelected()->Subscribe(GetWeakDistributed());
}

void MainMenuBar::Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments)
{
    if (auto menuArg = std::dynamic_pointer_cast<MenuItemViewEventArguments>(arguments))
    {
        if (auto invokedMenuItem = menuArg->GetMenuItem().lock())
        {
            if (m_openPanelMenuItems.contains(invokedMenuItem->GetKey()))
            {
                TryToOpenPanel(m_openPanelMenuItems.at(invokedMenuItem->GetKey()));
            }
        }
    }
}

bool MainMenuBar::TryToOpenPanel(const std::string& key) const
{
    std::shared_ptr<PanelManager> panelManager = m_windowPackage->GetPanelManager();
    if (std::shared_ptr<ToolsPanel> panel = panelManager->TryFindPanel(key))
    {
        if (!panel->OpenState())
        {
            panel->ShowWindow();
        }

        panel->ResetPanel();
        return true;
    }
    
    Log::Error("Could not find panel, it appears not to be registered. Key: " + key,
        "MainMenuBar::TryToOpenPanel(const std::string&)");
    return false;
}
