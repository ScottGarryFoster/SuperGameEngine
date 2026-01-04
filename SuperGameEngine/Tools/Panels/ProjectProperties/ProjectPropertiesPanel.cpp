#include "ProjectPropertiesPanel.h"

#include "../../../../FatedQuest.Libraries/GamePackage/GamePackage/PackagePaths.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "Engine/Content/ContentManager.h"
#include "Engine/Structural/UniversalObjectData/UniversalObjectDataTemplateProvider.h"
#include "Engine/Structural/UniversalObjectData/Template/SingleLayoutMetaData.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalObjectDataTemplate.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ExplicitDocumentModifiableUniversalObjectData.h"
#include "../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/RapidXMLDocument.h"
#include "Engine/Foundation/ProjectPropertiesProvider.h"
#include "Engine/Structural/UniversalObjectData/Template/SingleLayout.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ProjectPropertiesPanel::ProjectPropertiesPanel()
{
    m_projectPropertiesProvider = std::make_shared<ProjectPropertiesProvider>();
    m_universalObjectData = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();
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

    LoadProjectPropertiesFile();
}

void ProjectPropertiesPanel::Update()
{
}

void ProjectPropertiesPanel::Draw()
{
    if (RenderWindow(GetPanelName()))
    {
        m_projectPropertyLayout->GetLayout()->Draw(m_universalObjectData);
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

bool ProjectPropertiesPanel::HideWindow()
{
    if (m_universalObjectData->IsDirty())
    {
        return false;
    }

    Log::Info("Close");
    return SuperToolsPanel::HideWindow();
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

bool ProjectPropertiesPanel::CreateBaseFileIfOneDoesNotExist() const
{
    bool errorOccuredWhenCreatingFile = false;
    if (!m_projectPropertiesProvider->CanLoadProjectProperties(m_windowPackage->GetContentManager()->GamePackage()))
    {
        std::string basicPropertiesFilePath = Directory::CombinePath(
            m_windowPackage->GetPackagePaths()->ProductsDirectory(),
            m_windowPackage->GetPackagePaths()->ProductsDirectoryName(),
            m_projectPropertiesFileName);

        std::string fileContents = m_projectPropertyLayout->GetTemplate()->CreateBaseFile(basicPropertiesFilePath);
        if (fileContents.empty())
        {
            Log::Error("Tried to make a project properties file but failed. Contents was empty.",
                "ProjectPropertiesPanel::CreateBaseFileIfOneDoesNotExist(const std::shared_ptr<WindowPackage>&)");
            errorOccuredWhenCreatingFile = true;
        }

        File::WriteLine(basicPropertiesFilePath, fileContents);
    }

    return errorOccuredWhenCreatingFile;
}

void ProjectPropertiesPanel::LoadProjectPropertiesFile()
{
    if (CreateBaseFileIfOneDoesNotExist())
    {
        // Loading the base file will fail, could not create one. Errors called out in the method which attempted this.
        return;
    }

    {
        std::string relativePath = m_projectPropertiesProvider->GetProjectPropertiesPath
            (m_windowPackage->GetContentManager()->GamePackage());
        if (relativePath.empty())
        {
            Log::Error("No project path found. "
                       "This should be impossible. Report this as a bug with the "
                       "state of your base products folder and all sub directories one deep.",
                "ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>&)");
            return;
        }

        m_projectFilePath = Directory::CombinePath(
            m_windowPackage->GetPackagePaths()->ProductsDirectory(), 
            m_windowPackage->GetPackagePaths()->ProductsDirectoryName(), 
            relativePath);
    }

    auto xml = std::make_shared<RapidXMLDocument>();
    if (!xml->LoadFromFile(m_projectFilePath))
    {
        Log::Error("Project properties is invalid as an XML file. "
                   "It should be a Universal Object Data file in XML format. Report this.",
            "ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>&)");
        return;
    }

    m_universalObjectData->ImportAsDocument(xml);
}
