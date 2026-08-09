#pragma once
#include "Panels/SuperToolsPanel.h"
#include "../../../../FatedQuest.Libraries/Observer/AllReferences.h"
#include "Engine/Basic/ExtremelyWeakWrapper.h"
#include <SDL.h>

#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameEngine
{
    class EngineControls;
}

namespace SuperGameTools
{
    class ViewportEngineAndPanelCommunication;
    class ViewportTools;

    /// <summary>
    /// Renders the scene and allows visual modification.
    /// </summary>
    class ViewportPanel : public SuperToolsPanel, public FatedQuestLibraries::FEventObserver
    {
    public:
        ViewportPanel();
        virtual ~ViewportPanel() override;

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
        virtual void Invoke(const std::shared_ptr<FatedQuestLibraries::FEventArguments>& arguments) override;

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
        /// Defines and communicates engine level changes.
        /// </summary>
        /// <param name="engine">Defines and communicates engine level changes. </param>
        void GiveEngineControls(const std::shared_ptr<SuperGameEngine::EngineControls>& engine);

        /// <summary>
        /// The tools which accompany the scene viewport.
        /// These are rendered in a panel or as part of the viewport panel.
        /// </summary>
        /// <param name="viewportTools">The tools which accompany the scene viewport. </param>
        void GiveViewportTools(const std::shared_ptr<ViewportTools>& viewportTools);

        /// <summary>
        /// Give object which allow the viewport engine and the panel which renders it to communicate information.
        /// </summary>
        /// <param name="engineAndPanelCommunication">New communication Object. </param>
        void GiveViewportEngineAndPanelCommunication(const std::shared_ptr<ViewportEngineAndPanelCommunication>& engineAndPanelCommunication);

    private:

        /// <summary>
        /// Services to run a window.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// A cached link to the SDL Renderer.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SDLRendererReader> m_renderer;

        /// <summary>
        /// Defines and communicates engine level changes.
        /// </summary>
        std::shared_ptr<SuperGameEngine::EngineControls> m_engineControls;

        /// <summary>
        /// Where to position the SDL Viewport.
        /// </summary>
        SDL_Rect m_viewport;

        /// <summary>
        /// True means the size has changed and another texture size is required.
        /// </summary>
        bool m_sizeHasChanged;

        /// <summary>
        /// True when either the X Y Width Height has changed.
        /// </summary>
        bool m_sizeOrPositionHasChanged;

        /// <summary>
        /// True means we should render the viewport tools at the top.
        /// </summary>
        bool m_renderViewportTools;

        /// <summary>
        /// The tools which accompany the scene viewport.
        /// </summary>
        std::shared_ptr<ViewportTools> m_viewportTools;

        /// <summary>
        /// Objects which allow the viewport engine and the panel which renders it to communicate information.
        /// </summary>
        std::shared_ptr<ViewportEngineAndPanelCommunication> m_viewportEngineAndPanelCommunication;

        /// <summary>
        /// The location and size of the viewport image in the window.
        /// </summary>
        SuperGameEngine::RectangleInt m_viewportImage;

        /// <summary>
        /// Updates the viewport to match the window.
        /// </summary>
        void UpdateTheSDLViewport() const;
    };
}
