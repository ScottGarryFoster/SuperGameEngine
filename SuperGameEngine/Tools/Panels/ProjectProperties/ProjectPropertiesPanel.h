#pragma once
#include <memory>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"
#include "Panels/SuperToolsPanel.h"

namespace SuperGameEngine
{
    class ProjectPropertiesProvider;
}

namespace SuperGameTools
{
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
        /// Looks for the project properties layout and returns the value.
        /// </summary>
        /// <returns>The ability to create and edit the project properties file with its layout. </returns>
        std::shared_ptr<const SingleLayoutMetaData> FindProjectPropertyFileAndTemplateLayout() const;
    };
}
