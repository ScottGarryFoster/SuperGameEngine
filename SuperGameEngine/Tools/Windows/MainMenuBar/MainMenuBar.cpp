#include "MainMenuBar.h"
#include "../../ImGuiIncludes.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuView.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemView.h"

using namespace SuperGameTools;

void MainMenuBar::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_mainView = std::make_shared<MenuView>(windowPackage->GetColourPalette());

    m_mainView->AddTopLevelMenuItem("File");
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileOpen","Open"));
    m_mainView->AddInnerMenuItem("File", std::make_shared<MenuItemView>("FileSave","Save"));
    m_mainView->AddTopLevelMenuItem("Windows");
    m_mainView->AddInnerMenuItem("Windows", std::make_shared<MenuItemView>("WindowLogger","Logger"));
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
