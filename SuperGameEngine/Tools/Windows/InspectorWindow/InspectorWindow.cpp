#include "InspectorWindow.h"
#include "../../ImGuiIncludes.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"

void SuperGameTools::InspectorWindow::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    WindowElement::Setup(windowPackage->GetColourPalette());
}

void SuperGameTools::InspectorWindow::Draw()
{
    const char* windowName = "Inspector Window";
    RenderWindow(windowName);
    EndWindowRender(windowName);
}
