#pragma once
#include <memory>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "Panels/SuperToolsPanel.h"

namespace FatedQuestLibraries
{
    class ExplicitDocumentModifiableUniversalObjectData;
}

namespace SuperGameEngine
{
    class ProjectPropertiesProvider;
}

namespace SuperGameTools
{
    class EditableProjectPropertiesUniversalObjectData;
    class SingleLayoutMetaData;
    class WindowPackage;

    class ProjectPropertiesPanel : public SuperToolsPanel, public FatedQuestLibraries::FEventObserver
    {
    public:
        ProjectPropertiesPanel();
        virtual ~ProjectPropertiesPanel() override;

        /// <summary>
        /// Called once on setup.
        /// </summary>
        /// <param name="windowPackage">Everything needed to run a window. </param>
        virtual void Setup(const std::shared_ptr<WindowPackage>& windowPackage) override;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Called on draw.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called on destroy.
        /// </summary>
        virtual void TearDown() override;

        /// <summary>
        /// Subscribed to the logger events.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

        /// <summary>
        /// The name of the window to draw.
        /// </summary>
        /// <returns>The name of the window to draw. </returns>
        virtual const char* GetPanelName() const override;

        /// <summary>
        /// The unique name of the panel. This must be unique to this panel.
        /// </summary>
        /// <returns>The unique name of the panel. This must be unique to this panel. </returns>
        virtual const char* GetPanelUniqueName() const override;

        /// <summary>
        /// If no settings have saved the panel state, how would you like this panel to
        /// begin. True means open.
        /// </summary>
        /// <returns>True means open, provided window settings or layouts do not say otherwise. </returns>
        virtual bool OnLoadOpenState() const override;

        /// <summary>
        /// Reset the panel for whatever that means, location, content etc.
        /// </summary>
        virtual void ResetPanel() override;

        /// <summary>
        /// Hides the panel.
        /// </summary>
        virtual bool HideWindow() override;


    private:

        /// <summary>
        /// Services to run a window.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// Loads and Project Property file and provides the results.
        /// </summary>
        std::shared_ptr<SuperGameEngine::ProjectPropertiesProvider> m_projectPropertiesProvider;

        /// <summary>
        /// The file name to look for in the file system for a project properties file.
        /// </summary>
        const char* m_projectPropertiesFileName = "ProjectProperties.uod";

        /// <summary>
        /// The ability to create and edit the project properties file with its layout.
        /// </summary>
        std::shared_ptr<const SingleLayoutMetaData> m_projectPropertyLayout;

        /// <summary>
        /// The path to the actual file.
        /// We manage updating this from the provider and this is a cached location.
        /// </summary>
        std::string m_projectFilePath;

        /// <summary>
        /// Manages the data currently being edited. Could be not commited to file.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::ExplicitDocumentModifiableUniversalObjectData> m_universalObjectData;

        /// <summary>
        /// The last state of the dirty flag of the properties document.
        /// Used to update windows and ensure we are not calling things unnecessarily. 
        /// </summary>
        bool m_previousDirtyStateOfDocument;

        /// <summary>
        /// Converts a Stored Document to XML.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::DocumentToXml> m_documentToXml;

        /// <summary>
        /// Looks for the project properties layout and returns the value.
        /// </summary>
        /// <returns>The ability to create and edit the project properties file with its layout. </returns>
        std::shared_ptr<const SingleLayoutMetaData> FindProjectPropertyFileAndTemplateLayout() const;

        /// <summary>
        /// Check to see if the provider can find a properties file, if not attempt to create one.
        /// The outcome of this is either that a properties file exists, or the provider fails.
        /// </summary>
        /// <returns>Were there errors? True means yes there were errors, false means the file exists. </returns>
        /// <remarks>
        /// This logic is here because it is only used by the Tools and creating a custom class for this is
        /// likely overkill.
        /// </remarks>
        bool CreateBaseFileIfOneDoesNotExist() const;

        /// <summary>
        /// Refresh/Load the project properties file ensuring it exists and is now editable in this editor.
        /// </summary>
        void LoadProjectPropertiesFile();

        /// <summary>
        /// Saves the project properties file.
        /// </summary>
        void SaveProperties();

        /// <summary>
        /// Displays and creates the logic for the action buttons.
        /// </summary>
        /// <returns>True means close the window. </returns>
        /// <remarks>Ensure to close the window outside of any existing window.</remarks>
        bool ActionButtons();
    };
}
