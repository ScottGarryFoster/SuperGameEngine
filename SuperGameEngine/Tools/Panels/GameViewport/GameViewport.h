#pragma once
#include <SDL_rect.h>

#include "../../ToolsEngine/ViewElements/Window/ToolsWindowElement.h"
#include "../UpdateableObject/UpdateableObject.h"
#include "Panels/SuperToolsPanel.h"

namespace SuperGameTools
{
    /// <summary>
    /// Holds the viewport.
    /// </summary>
    class GameViewport : public SuperToolsPanel
    {
    public:
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
        /// Where to position the SDL Viewport.
        /// </summary>
        SDL_Rect m_viewport;

        /// <summary>
        /// Wraps the SDL Renderer such that upon the death of the
        /// SDL Window this becomes invalid and the textures wait for a
        /// new texture.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SDLRendererReader> m_renderer;

        /// <summary>
        /// Everything a Window Package might need to run.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// Updates the viewport to match the window.
        /// </summary>
        void UpdateTheSDLViewport();
    };
}
