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
    class ToolsLayoutSettings;
    class EngineFlowPlayControl;

    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class ToolsEngineEntry : public EngineEntry
    {
    public:
        ToolsEngineEntry();
        virtual ~ToolsEngineEntry() override = default;

        /// <summary>
        /// The entry to the engine.
        /// </summary>
        /// <param name="engineType">
        /// The type of the engine to create.
        /// The factory uses the type name to define which to create.
        /// </param>
        /// <returns>
        /// 0 means no errors occured when 
        /// attempting to start the application.
        /// </returns>
        virtual int RunApplication(const std::string& engineType) override;

    private:

        /// <summary>
        /// Creates the SDL Window loop.
        /// </summary>
        /// <param name="engineType">
        /// The type of the engine to create.
        /// The factory uses the type name to define which to create.
        /// </param>
        /// <returns>
        /// How to handle exiting the game loop.
        /// </returns>
        ApplicationOperationState RunSDLWindow(const std::string& engineType);

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

        /// <summary>
        /// The last frame rendered by the game engine.
        /// </summary>
        std::shared_ptr<ExtremelyWeakWrapper<SDL_Texture>> m_sdlTexture;

        /// <summary>
        /// Complete control over how and when the game engine runs.
        /// </summary>
        std::shared_ptr<EngineFlowPlayControl> m_engineFlow;

        /// <summary>
        /// Communication with the tools engine.
        /// </summary>
        std::shared_ptr<EngineEntryCommunication> m_engineEntryCommunication;

        /// <summary>
        /// Helps to keep settings for the main window.
        /// </summary>
        std::shared_ptr<ToolsLayoutSettings> m_layoutSettings;

        /// <summary>
        /// Handles and updates user input.
        /// </summary>
        std::shared_ptr<SuperGameInput::SDLInputManager> m_inputManager;
    };

    REGISTER_ENGINE_ENTRY("ToolsEngineEntry", ToolsEngineEntry);
}