#pragma once
#include "ToolsEngine.h"
#include <memory>
#include "../../Engine/EngineEntry/ApplicationOperationState.h"
#include "../../Engine/Engine/Graphics/Texture/SDLRenderer.h"
#include "../../Engine/Engine/Factory/EngineEntryFactory.h"
#include "../../Engine/EngineEntry/EngineEntry.h"
#include "../../Engine/Engine/Basic/ExtremelyWeakWrapper.h"

namespace SuperGameEngine
{
    class ImGuiContainer;
}

namespace SuperGameTools
{

    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class ToolsEngineEntry : public EngineEntry
    {
    public:
        /// <summary>
        /// The entry to the engine.
        /// </summary>
        /// <param name="engine">Engine to run. </param>
        /// <returns>
        /// 0 means no errors occured when 
        /// attempting to start the application.
        /// </returns>
        int RunApplication(std::shared_ptr<Engine> engine) override;

    private:

        /// <summary>
        /// Creates the SDL Window loop.
        /// </summary>
        ApplicationOperationState RunSDLWindow(std::shared_ptr<Engine> engine);

        /// <summary>
        /// Renderer given to the game engine.
        /// This will act as though it is destroyed when the game is
        /// 'stopped' to simulate the game restarting.
        /// </summary>
        std::shared_ptr<SDLRenderer> m_gameRenderer;

        /// <summary>
        /// The renderer for the current window.
        /// This will flip flop and change with windows but is the
        /// active window.
        /// </summary>
        std::shared_ptr<SDLRenderer> m_Toolsrenderer;

        /// <summary>
        /// Wraps setup for imgui.
        /// </summary>
        std::shared_ptr<ImGuiContainer> m_imgui;

        /// <summary>
        /// If tools are used, this is engine.
        /// Otherwise, it is an empty pointer.
        /// </summary>
        std::shared_ptr<ToolsEngine> m_toolsEngine;

        std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> m_sdlTexture;
    };

    REGISTER_ENGINE_ENTRY("ToolsEngineEntry", ToolsEngineEntry);
}