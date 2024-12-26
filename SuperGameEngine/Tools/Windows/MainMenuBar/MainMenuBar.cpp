#include "MainMenuBar.h"
#include "../../ImGuiIncludes.h"
#include "../../ToolsEngine/ViewElements/MenuView.h"
#include "../../ToolsEngine/ViewElements/MenuItemView.h"

using namespace SuperGameTools;

void MainMenuBar::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    m_mainView = std::make_shared<MenuView>();

    m_mainView->AddTopLevelMenuItem("File");
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("Open"));
    m_mainView->AddTopLevelMenuItem("Windows");
    m_mainView->AddInnerMenuItem("Windows", std::make_shared<MenuItemView>("Logger"));
}

void MainMenuBar::Update()
{
    if (!m_windowPackage)
    {
        return;
    }
}

void MainMenuBar::Draw()
{
    if (!m_windowPackage)
    {
        return;
    }

    m_mainView->Draw();
}

void MainMenuBar::TearDown()
{
    if (!m_windowPackage)
    {
        return;
    }
}
