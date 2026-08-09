#include "ViewportToolsSettingsPanel.h"

#include "ViewportToolsSettings.h"
#include "../../ImGuiIncludes.h"
#include "../../../../FatedQuest.Libraries/StoredDocument/Converters/SimpleDocumentToXml.h"
#include "../../../../FatedQuest.Libraries/XmlDocument/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/AllReferences.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/Structural/UniversalObjectData/UniversalObjectDataTemplateProvider.h"
#include "Engine/Structural/UniversalObjectData/Template/SingleLayout.h"
#include "Engine/Structural/UniversalObjectData/Template/SingleLayoutMetaData.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalObjectDataFileType.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalObjectDataTemplate.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/PanelSelectionChangedArguments.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ViewportToolsSettingsPanel::ViewportToolsSettingsPanel()
{
    m_universalObjectData = std::make_shared<ExplicitDocumentModifiableUniversalObjectData>();
    m_documentToXml = std::make_shared<FatedQuestLibraries::SimpleDocumentToXml>();
    m_viewportToolsSettings = std::make_shared<ViewportToolsSettings>(m_universalObjectData);

    m_thisPanelsName = PanelSelectionName::ViewportToolsSettings;
    m_currentSelectedPanel = PanelSelectionName::None;
    if (SetupFilePath().empty())
    {
        Log::Error("Could not find a good path for the settings file",
            "ViewportToolsSettingsPanel::ViewportToolsSettingsPanel");
    }
}

void ViewportToolsSettingsPanel::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    SetupWindow(m_windowPackage->GetColourPalette(), GetPanelUniqueName(),
        {
            .ResetLayoutUsingLayouts = true,
            .StartPosition = {.X = 50, .Y = 50}
        });

    m_viewportSettingsLayout = FindSettingsFileAndTemplateLayout();
    if (!m_viewportSettingsLayout)
    {
        Log::Error("Could not find a valid file template/layout for project properties. Is there one within the Universal Templates folder?",
            "ProjectPropertiesPanel::Setup(const std::shared_ptr<WindowPackage>&)");
        return;
    }

    LoadSettingsFile();
}

void ViewportToolsSettingsPanel::Update()
{
    if (m_previousDirtyStateOfDocument != m_universalObjectData->IsDirty())
    {
        m_previousDirtyStateOfDocument = m_universalObjectData->IsDirty();
        UpdateUnsavedState(m_previousDirtyStateOfDocument);
    }
}

void ViewportToolsSettingsPanel::Draw()
{
    bool closeWindow = false;
    if (RenderWindow(GetPanelName()))
    {
        HandlePanelSelection(m_panelSelectionManager, PanelSelectionName::ProjectProperties);
        m_viewportSettingsLayout->GetLayout()->Draw(m_universalObjectData);

        closeWindow = ActionButtons();
    }
    EndWindowRender(GetPanelName());

    if (closeWindow)
    {
        HideWindow();
    }
}

void ViewportToolsSettingsPanel::TearDown()
{
}

void ViewportToolsSettingsPanel::Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments)
{
    if (auto args = std::dynamic_pointer_cast<PanelSelectionChangedArguments>(arguments))
    {
        m_currentSelectedPanel = args->GetSelectionName();
    }
}

const char* ViewportToolsSettingsPanel::GetPanelName() const
{
    return "Tools Viewport Settings";
}

const char* ViewportToolsSettingsPanel::GetPanelUniqueName() const
{
    return "ToolsViewportSettings";
}

bool ViewportToolsSettingsPanel::OnLoadOpenState() const
{
    return false;
}

void ViewportToolsSettingsPanel::ResetPanel()
{
    ResetWindowLayout();
}

bool ViewportToolsSettingsPanel::HideWindow()
{
    return SuperToolsPanel::HideWindow();
}

std::shared_ptr<ViewportToolsSettings> ViewportToolsSettingsPanel::GetViewportToolsSettings() const
{
    return m_viewportToolsSettings;
}

std::shared_ptr<const SingleLayoutMetaData> ViewportToolsSettingsPanel::FindSettingsFileAndTemplateLayout() const
{
    std::vector<std::shared_ptr<const SingleLayoutMetaData>> fileLayouts =
        m_windowPackage->GetUniversalObjectDataTemplateProvider()->GetObjectDataTemplates();

    std::shared_ptr<const SingleLayoutMetaData> propertyLayout = {};
    for (const std::shared_ptr<const SingleLayoutMetaData>& layout : fileLayouts)
    {
        if (layout->GetTemplate()->GetUniversalObjectDataFileType() != UniversalObjectDataFileType::ToolsViewportSettings)
        {
            continue;
        }

        if (layout->GetTemplate()->ShouldUseTemplate(m_settingFileName))
        {
            propertyLayout = layout;
            break;
        }
    }

    return propertyLayout;
}

bool ViewportToolsSettingsPanel::CreateBaseFileIfOneDoesNotExist() const
{
    if (File::Exists(m_fullPathToSettingsFile))
    {
        return false;
    }

    bool errorOccuredWhenCreatingFile = false;
    std::string fileContents = m_viewportSettingsLayout->GetTemplate()->CreateBaseFile(m_fullPathToSettingsFile);
    if (fileContents.empty())
    {
        Log::Error("Tried to make a project properties file but failed. Contents was empty.",
            "ProjectPropertiesPanel::CreateBaseFileIfOneDoesNotExist(const std::shared_ptr<WindowPackage>&)");
        errorOccuredWhenCreatingFile = true;
    }

    File::WriteLine(m_fullPathToSettingsFile, fileContents);

    return errorOccuredWhenCreatingFile;
}

void ViewportToolsSettingsPanel::LoadSettingsFile()
{
    if (CreateBaseFileIfOneDoesNotExist())
    {
        // Loading the base file will fail, could not create one. Errors called out in the method which attempted this.
        return;
    }

    auto xml = std::make_shared<RapidXMLDocument>();
    if (!xml->LoadFromFile(m_fullPathToSettingsFile))
    {
        Log::Error("Viewport Tools Settings is invalid as an XML file. "
            "It should be a Universal Object Data file in XML format. Report this.",
            "ViewportToolsSettingsPanel::LoadSettingsFile()");
        return;
    }

    m_universalObjectData->ImportAsDocument(xml);
    m_viewportToolsSettings->SettingsHaveUpdated();
}

void ViewportToolsSettingsPanel::SaveSettings()
{
    // Do not save if there was nothing to save.
    if (!m_universalObjectData->IsDirty())
    {
        return;
    }

    std::shared_ptr<ModifiableDocument> document = m_universalObjectData->ExportToDocument();
    if (!document)
    {
        Log::Error("Could not export universal document to xml: " + m_fullPathToSettingsFile,
            "ViewportToolsSettingsPanel::SaveSettings()");
        return;
    }

    std::string fileContents = m_documentToXml->ConvertToXml(document);

    if (!File::WriteLine(m_fullPathToSettingsFile, fileContents))
    {
        Log::Error("Could not write file contents to path: " + m_fullPathToSettingsFile,
            "ViewportToolsSettingsPanel::SaveSettings()");
        return;
    }

    m_universalObjectData->MarkSaved();
    m_previousDirtyStateOfDocument = false;
    UpdateUnsavedState(m_previousDirtyStateOfDocument);
    m_viewportToolsSettings->SettingsHaveUpdated();
}

bool ViewportToolsSettingsPanel::ActionButtons()
{
    bool closeWindow = false;

    float okButtonWidth = 50;
    float cancelButtonWidth = 60;
    float applyButtonWidth = 50;
    float padding = 10;
    float windowVisibleX2 = ImGui::GetWindowContentRegionMax().x;

    float rightMost = okButtonWidth + padding + cancelButtonWidth + padding + applyButtonWidth - 2;
    ImGui::SetCursorPosX(windowVisibleX2 - rightMost);

    if (ImGui::Button("Ok", ImVec2(okButtonWidth, 0)))
    {
        SaveSettings();
        closeWindow = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel", ImVec2(cancelButtonWidth, 0)))
    {
        LoadSettingsFile();
    }

    ImGui::SameLine();

    if (ImGui::Button("Apply", ImVec2(applyButtonWidth, 0)))
    {
        SaveSettings();
    }

    return closeWindow;
}

std::string ViewportToolsSettingsPanel::SetupFilePath()
{
    std::string idealFolder = Directory::CombinePath(Directory::GetTempDirectory(), "SuperGameEngine", "Settings", "Tools");
    if (!Directory::Exists(idealFolder))
    {
        Directory::CreateDirectories(idealFolder);
    }

    m_fullPathToSettingsFile = Directory::CombinePath(idealFolder, m_settingFileName);
    return m_fullPathToSettingsFile;
}
