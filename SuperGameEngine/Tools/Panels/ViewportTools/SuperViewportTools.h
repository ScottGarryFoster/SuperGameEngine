#pragma once
#include <memory>
#include <unordered_map>

#include "ViewportButtonInfo.h"
#include "ViewportDebugOption.h"
#include "ViewportTools.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace SuperGameTools
{
    class ViewportToolsSettings;
    class ViewportToolsSettingsPanel;
}

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameTools
{
    struct ViewportButtonInfo;
    class SuperViewportToolsButton;
    class WindowPackage;

    /// <summary>
    /// The tools which accompany the scene viewport.
    /// </summary>
    class SuperViewportTools : public virtual ViewportTools, public FatedQuestLibraries::FEventObserver
    {
    public:

        SuperViewportTools(const std::shared_ptr<WindowPackage>& windowPackage);

        /// <summary>
        /// Sets up the tools.
        /// Should only be called once.
        /// </summary>
        void Setup();

        /// <summary>
        /// Gets the currently selected tool.
        /// </summary>
        /// <returns>The selected tool. </returns>
        virtual ViewportToolsType GetSelectedTool() const override;

        /// <summary>
        /// Selects a new tool.
        /// </summary>
        /// <param name="newValue">New tool to select. </param>
        virtual void SelectTool(ViewportToolsType newValue) override;

        /// <summary>
        /// Called every frame.
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// Draw the viewport tools bar. 
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments) override;

        /// <summary>
        /// Invoked when selected tool is changed.
        /// </summary>
        /// <returns>Invoked when selected tool is changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEvent> OnSelectedToolChanged() const override;

        /// <summary>
        /// Invoked when debug options changed.
        /// Uses ViewportDebugOptionsChanged Event Arguments.
        /// </summary>
        /// <returns>Invoked when debug options changed. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEvent> OnDebugOptionsChanged() const override;

        /// <summary>
        /// Get the actual settings from the panel.
        /// </summary>
        /// <returns>The actual settings from the panel.</returns>
        virtual std::shared_ptr<ViewportToolsSettings> GetViewportToolsSettings() const override;

    private:

        /// <summary>
        /// The currently selected tool.
        /// </summary>
        ViewportToolsType m_selectedTool;

        /// <summary>
        /// The ability to draw and access other systems.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// The viewport buttons.
        /// </summary>
        std::unordered_map<ViewportToolsType, std::shared_ptr<SuperViewportToolsButton>> m_toolsButtons;

        /// <summary>
        /// Defines all the viewport button information in a raw format.
        /// </summary>
        ViewportButtonInfo m_viewportButtonInfo;

        /// <summary>
        /// Invoked when selected tool is changed.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onSelectedToolChanged;

        /// <summary>
        /// Invoked when debug options changed.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onDebugOptionsChanged;

        /// <summary>
        /// The option selected to view different debug information in the viewport.
        /// </summary>
        ViewportDebugOption m_debugOption;

        /// <summary>
        /// The settings panel for the viewport tools.
        /// </summary>
        std::shared_ptr<ViewportToolsSettingsPanel> m_settingsPanel;
    };
}
