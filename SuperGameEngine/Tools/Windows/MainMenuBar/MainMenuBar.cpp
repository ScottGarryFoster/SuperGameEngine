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
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileOpen","Open"));
    m_mainView->AddTopLevelMenuItem("Windows");
    m_mainView->AddInnerMenuItem("Windows", std::make_shared<MenuItemView>("WindowLogger","Logger"));
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

std::shared_ptr<MenuView> MainMenuBar::GetTopMenuBar() const
{
    return m_mainView;
}
