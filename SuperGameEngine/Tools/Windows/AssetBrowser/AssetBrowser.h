#pragma once
#include "../UpdateableObject/UpdateableObject.h"
#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/ViewElements/Window/WindowElement.h"

namespace SuperGameEngine
{
    class SuperTexture;
}

namespace SuperGameTools
{
    class AssetFolderRender;
    class AssetFolder;
}

namespace SuperGameTools
{
    class AssetFileProvider;

    /// <summary>
    /// Displays assets for the game package and helps manage these. Also is the selector for the inspector and scene view.
    /// </summary>
    class AssetBrowser : public UpdateableObject, public FatedQuestLibraries::FEventObserver, public WindowElement
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
