#pragma once
#include <SDL.h>
#include "../External/imgui.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Starts and contains ImGui
    /// </summary>
    class ImGuiContainer
    {
    public:
        ImGuiContainer();
        virtual ~ImGuiContainer();

        /// <summary>
        /// Starts the context.
        /// </summary>
        /// <param name="renderer">SDL Renderer. </param>
        /// <param name="window">SDL Window. </param>
        void Initialise(SDL_Renderer* renderer, SDL_Window* window);

        /// <summary>
        /// Called upon each event in SDL.
        /// </summary>
        void EventCall(const SDL_Event& e);

        /// <summary>
        /// Called at the end of ImGUIs draw before it actually draws.
        /// </summary>
        void FinishCreatingDraw();

        /// <summary>
        /// Called to render the frame itself.
        /// </summary>
        void Render();

        /// <summary>
        /// Call when the renderer and window are about to be destroyed to tear
        /// the IMGUI context down.
        /// </summary>
        void Teardown();

    private:
        /// <summary>
        /// The IMGUI context. 
        /// </summary>
        ImGuiContext* m_context;

        /// <summary>
        /// Current renderer.
        /// </summary>
        SDL_Renderer* m_renderer;
    };

}