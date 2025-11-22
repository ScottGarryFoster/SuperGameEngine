#include "ProjectPropertiesPanel.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ProjectPropertiesPanel::ProjectPropertiesPanel()
{
}

ProjectPropertiesPanel::~ProjectPropertiesPanel()
{
}

void ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    ToolsWindowElement::SetupWindow(m_windowPackage->GetColourPalette());
}

void ProjectPropertiesPanel::Update()
{
}

void ProjectPropertiesPanel::Draw()
{
    RenderWindow(GetPanelName());

    EndWindowRender(GetPanelName());
}

void ProjectPropertiesPanel::TearDown()
{
}

void ProjectPropertiesPanel::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
}

const char* ProjectPropertiesPanel::GetPanelName()
{
    return "Project Properties";
}
