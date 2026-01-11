#pragma once
#include <memory>
#include <SDL_video.h>

#include "SDLEngineWindowManager.h"
#include "Engine/Basic/ExtremelyWeakWrapper.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Creates windows using SDL.
    /// </summary>
    class SDLWindowManager : public virtual SDLEngineWindowManager
    {
    public:
        SDLWindowManager();
        virtual ~SDLWindowManager();

        /// <summary>
        /// Setup the window manager.
        /// This can be run more than once and should be run if anything given fundamentally changes and
        /// it would be better to use the data from these.
        /// </summary>
        /// <param name="projectProperties">The foundational properties for setting up the project for the product. </param>
        virtual void Setup(const std::shared_ptr<ProjectProperties>& projectProperties) override;

        /// <summary>
        /// Creates new window.
        /// </summary>
        /// <param name="name">Title of the window. </param>
        /// <param name="position">Position to spawn the window. </param>
        /// <param name="size">Size of the window when spawned. </param>
        /// <return>True when could create window, false otherwise. Will log issues. </return>
        virtual bool CreateGameWindow(
            const std::string& name, 
            WindowPredefinedPosition position, 
            const FatedQuestLibraries::FPoint& size) override;

        /// <summary>
        /// Destroy the window created previously.
        /// Will do nothing if there is no window.
        /// </summary>
        virtual void DestroyWindow() override;

        /// <summary>
        /// A renderer should be created when the window is created.
        /// This is the renderer created when the window is created.
        /// </summary>
        /// <returns>A wrapper for SDL_Renderer to wrap the renderer from the SDL framework.</returns>
        virtual std::shared_ptr<SDLRenderer> GetDefaultRenderer() const override;

    private:

        /// <summary>
        /// The actual stored window.
        /// </summary>
        /// <remarks>
        /// This manager should be the only thing using this window.
        /// If not, sub in a smart pointer or ExtremelyWeakWrapper.
        /// </remarks>
        SDL_Window* m_window;

        /// <summary>
        /// The renderer created when the window was created.
        /// </summary>
        std::shared_ptr<SDLRenderer> m_defaultRenderer;

        /// <summary>
        /// The foundational properties for setting up the project for the product.
        /// </summary>
        std::shared_ptr<ProjectProperties> m_projectProperties;

        /// <summary>
        /// All destroy operations for this level.
        /// </summary>
        void DestroySDLWindow();

        FatedQuestLibraries::FPoint PredefinedPositionConverter(WindowPredefinedPosition position) const;
    };
}
