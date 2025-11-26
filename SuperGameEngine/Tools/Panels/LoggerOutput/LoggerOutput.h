#pragma once
#include "../../FatedQuestLibraries.h"
#include "Panels/SuperToolsPanel.h"

namespace SuperGameEngine
{
    class SuperTexture;
}

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    class LogEntry;
    class LoggerCallback;

    /// <summary>
    /// Holds the viewport.
    /// </summary>
    class LoggerOutput : public SuperToolsPanel, public FEventObserver
    {
    public:
        LoggerOutput();
        virtual ~LoggerOutput() override;

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
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;

        /// <summary>
        /// The name of the window to draw.
        /// </summary>
        /// <returns>The name of the window to draw. </returns>
        virtual const char* GetPanelName() const override;

        /// <summary>
        /// If no settings have saved the panel state, how would you like this panel to
        /// begin. True means open.
        /// </summary>
        /// <returns>True means open, provided window settings or layouts do not say otherwise. </returns>
        virtual bool OpenState() const override;

    private:

        /// <summary>
        /// Services to run a window.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// Shown for warning logs.
        /// </summary>
        std::shared_ptr<SuperTexture> m_warningIcon;

        /// <summary>
        /// Shown for info logs.
        /// </summary>
        std::shared_ptr<SuperTexture> m_infoIcon;

        /// <summary>
        /// Shown for error logs.
        /// </summary>
        std::shared_ptr<SuperTexture> m_errorIcon;

        /// <summary>
        /// All logs sent.
        /// </summary>
        std::vector<std::shared_ptr<LogEntry>> m_logEntries;
    };
}
