#pragma once
#include "../../FatedQuestLibraries.h"
#include "Panels/SuperToolsPanel.h"

namespace SuperGameEngine
{
    class SuperTexture;
}

namespace SuperGameTools
{
    class AssetFileProvider;
    class AssetFolderRender;
    class AssetFolder;

    /// <summary>
    /// Displays assets for the game package and helps manage these. Also is the selector for the inspector and scene view.
    /// </summary>
    class AssetBrowser : public SuperToolsPanel, public FatedQuestLibraries::FEventObserver
    {
    public:
        AssetBrowser();
        virtual ~AssetBrowser() override;

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
        virtual bool OpenState() const override;

    private:

        /// <summary>
        /// Services to run a window.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// Provides all the asset files for viewing and editing.
        /// </summary>
        std::shared_ptr<AssetFileProvider> m_assetFileProvider;

        /// <summary>
        /// Renderers the folders as tiles.
        /// </summary>
        std::shared_ptr<AssetFolderRender> m_tileFolderRenderer;
    };
}
