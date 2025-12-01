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
    SetupWindow(m_windowPackage->GetColourPalette(), GetPanelUniqueName(), 
        {
            .ResetLayoutUsingLayouts = true,
            .StartPosition = {.X = 50, .Y = 50}
            });

    //ProjectPropertiesProvider
}

void ProjectPropertiesPanel::Update()
{
}

void ProjectPropertiesPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        
    }
    EndWindowRender(GetPanelName());
}

void ProjectPropertiesPanel::TearDown()
{
}

void ProjectPropertiesPanel::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
}

const char* ProjectPropertiesPanel::GetPanelName() const
{
    return "Project Properties";
}

const char* ProjectPropertiesPanel::GetPanelUniqueName() const
{
    return "ProjectProperties";
}

bool ProjectPropertiesPanel::OnLoadOpenState() const
{
    return false;
}

void ProjectPropertiesPanel::ResetPanel()
{
    ResetWindowLayout();
}
