#include "ProjectPropertiesPanel.h"

#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "Engine/Content/ContentManager.h"
#include "Engine/Foundation/ProjectPropertiesProvider.h"
#include "Engine/Structural/UniversalObjectData/UniversalObjectDataTemplateProvider.h"
#include "Engine/Structural/UniversalObjectData/Template/SingleLayoutMetaData.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalObjectDataTemplate.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ProjectPropertiesPanel::ProjectPropertiesPanel()
{
    m_projectPropertiesProvider = std::make_shared<ProjectPropertiesProvider>();
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

    m_projectPropertyLayout = FindProjectPropertyFileAndTemplateLayout();
    if (!m_projectPropertyLayout)
    {
        Log::Error("Could not find a valid file template/layout for project properties. Is there one within the Universal Templates folder?",
            "ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>&)");
        return;
    }

    if (!m_projectPropertiesProvider->CanLoadProjectProperties(windowPackage->GetContentManager()->GamePackage()))
    {
        std::string basicPropertiesFilePath = Directory::CombinePath(
            m_windowPackage->GetPackagePaths()->ProductsDirectory(), 
            m_windowPackage->GetPackagePaths()->ProductsDirectoryName(),
            m_projectPropertiesFileName);

        std::string fileContents = m_projectPropertyLayout->GetTemplate()->CreateBaseFile(basicPropertiesFilePath);
        if (fileContents.empty())
        {
            Log::Error("Tried to make a project properties file but failed. Contents was empty.",
                "ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>&)");
            return;
        }

        File::WriteLine(basicPropertiesFilePath, fileContents);
    }

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

std::shared_ptr<const SingleLayoutMetaData> ProjectPropertiesPanel::FindProjectPropertyFileAndTemplateLayout() const
{
    std::vector<std::shared_ptr<const SingleLayoutMetaData>> fileLayouts =
        m_windowPackage->GetUniversalObjectDataTemplateProvider()->GetObjectDataTemplates();

    std::shared_ptr<const SingleLayoutMetaData> propertyLayout = {};
    for (const std::shared_ptr<const SingleLayoutMetaData>& layout : fileLayouts)
    {
        if (layout->GetTemplate()->GetUniversalObjectDataFileType() != UniversalObjectDataFileType::Properties)
        {
            continue;
        }

        if (layout->GetTemplate()->ShouldUseTemplate(m_projectPropertiesFileName))
        {
            propertyLayout = layout;
            break;
        }
    }

    return propertyLayout;
}
