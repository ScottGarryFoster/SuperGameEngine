#include "ToolsEngineEntry.h"

#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "../ImGuiIncludes.h"
#include "Communication/ToolsEngineEntryCommunication.h"
#include "Communication/EngineFlowPlayControl.h"
#include "Communication/ToolsEngineControl.h"

using namespace SuperGameTools;

ToolsEngineEntry::ToolsEngineEntry()
{
    auto toolsEngineEntry = std::make_shared<ToolsEngineEntryCommunication>();
    m_engineEntryCommunication = toolsEngineEntry;

    m_engineFlow = std::make_shared<ToolsEngineControl>();
    toolsEngineEntry->SetPlayControls(m_engineFlow);
}

int ToolsEngineEntry::RunApplication(const std::string& engineType)
{
    m_imgui = std::make_shared<ImGuiContainer>();
    m_toolsEngine = std::make_shared<ToolsEngine>();
    m_toolsEngine->GiveEnginePlayControls(m_engineEntryCommunication);

    m_sdlTexture = std::make_shared<ExtremelyWeakWrapper<SDL_Texture>>(nullptr);
    m_toolsEngine->GiveSDLTexture(m_sdlTexture);

    m_gameRenderer = std::make_shared<SDLRenderer>();
    m_Toolsrenderer = std::make_shared<SDLRenderer>();
    ApplicationOperationState windowState = ApplicationOperationState::Restart;
    while (windowState != ApplicationOperationState::Close)
    {
        windowState = RunSDLWindow(engineType);
    }

    return 0;
}

ApplicationOperationState ToolsEngineEntry::RunSDLWindow(const std::string& engineType)
{
    // Pointers to our window and surface
    SDL_Window* window = nullptr;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Error initializing SDL: " + sdlError);
        return ApplicationOperationState::Close;
    }

    // Set SDL hint to enable VSync
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"))
    {
        Log::Error("Warning: VSync not enabled!");
        return ApplicationOperationState::Close;
    }

    // Create our window
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Error creating window: " + sdlError);
        return ApplicationOperationState::Close;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Could not create Renderer: " + sdlError);

        // Handle renderer creation failure
        SDL_DestroyWindow(window);
        SDL_Quit();

        return ApplicationOperationState::Close;
    }

    // Initialise IMGUI
    m_imgui->Initialise(renderer, window);

    // Event handler
    SDL_Event e;

    // Setup the Tools Engine
    if (m_toolsEngine)
    {
        m_Toolsrenderer->SetRenderer(renderer);
        m_toolsEngine->GiveRenderer(m_Toolsrenderer);
        m_toolsEngine->WindowStart();
    }

    Uint64 startTime = SDL_GetTicks64();

    std::shared_ptr<Engine> engine = {};

    // Main loop
    ApplicationOperationState operationState = ApplicationOperationState::Running;
    while (operationState == ApplicationOperationState::Running)
    {
        auto eventAnswer = ApplicationOperationState::Running;

        if (m_engineFlow->DoRecreate())
        {
            engine = EngineFactory::CreateEngine(engineType);
            if (!engine)
            {
                Log::Error("Could not create Engine from factory, mid flow: " + engineType);
                return ApplicationOperationState::Close;
            }

            if (engine)
            {
                m_gameRenderer->SetRenderer(renderer);
                engine->GiveRenderer(m_gameRenderer);
                engine->WindowStart();
            }

        }

        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (engine && m_engineFlow->DoRunEvents())
            {
                eventAnswer = engine->Event(e);
                if (eventAnswer != ApplicationOperationState::Running)
                {
                    operationState = eventAnswer;
                }
            }


            // Tools Engine should also take events
            if (m_toolsEngine)
            {
                eventAnswer = m_toolsEngine->Event(e);
                if (eventAnswer != ApplicationOperationState::Running)
                {
                    operationState = eventAnswer;
                }
            }

            // IMGui also needs events:
            m_imgui->EventCall(e);

            if (e.type == SDL_QUIT)
            {
                Log::Info("Engine has indicated from Events it would like to QUIT.");
                operationState = ApplicationOperationState::Close;
            }
        }

        // Let the flow know this occured.
        if (engine && m_engineFlow->DoRunEvents())
        {
            m_engineFlow->RanEvents();
        }


        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        ApplicationOperationState updateAnswer = ApplicationOperationState::Running;

        if (engine && m_engineFlow->DoRunUpdate())
        {
            updateAnswer = engine->Update(ticksThisFrame);
            if (updateAnswer != ApplicationOperationState::Running)
            {
                operationState = updateAnswer;
            }

            m_engineFlow->RanUpdate();
        }


        // Predraw update for Tools.
        if (m_toolsEngine)
        {
            updateAnswer = m_toolsEngine->Update(ticksThisFrame);
            if (updateAnswer != ApplicationOperationState::Running)
            {
                operationState = updateAnswer;
            }
        }

        // Unlikely to occur but in the situation the event and update loop
        // try to override one another we should log this, incase we get a bug
        // here.
#ifdef _DEBUG
        if (eventAnswer != ApplicationOperationState::Running &&
            updateAnswer != ApplicationOperationState::Running &&
            eventAnswer != updateAnswer)
        {
            Log::Warning("The event update and the update loop are both trying to affect the application state but do not agree on what to do."
                "Event State: " + EApplicationOperationState::ToString(eventAnswer) +
                "Update State: " + EApplicationOperationState::ToString(updateAnswer));
        }
#endif

        SDL_Texture* sdlTexture = nullptr;
        if (engine && m_engineFlow->DoRunDraw())
        {
            // We only want to refresh this if we have a new frame.
            // This is so we can move one frame at a time.
            if (m_sdlTexture->GetState() == PointerState::Active)
            {
                SDL_DestroyTexture(m_sdlTexture->Get());
                m_sdlTexture->Set(nullptr);
            }

            // Make texture to render the SDL Viewport
            sdlTexture = SDL_CreateTexture(
                renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
            SDL_SetRenderTarget(renderer, sdlTexture);
            SDL_RenderClear(renderer);

            // Render the game itself
            engine->Draw();
            SDL_SetRenderTarget(renderer, nullptr);

            // Give the texture the tools
            m_sdlTexture->Set(sdlTexture);

            m_engineFlow->RanDraw();
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 103, 235, 229, 255);
        SDL_RenderClear(renderer);

        // Start Tools Draw
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Actual draw for Tools
        if (m_toolsEngine)
        {
            m_toolsEngine->Draw();
        }

        // Ensure ImGUI Draws are in buffer
        m_imgui->FinishCreatingDraw();

        // Actually render to the screen.
        m_imgui->Render();

        // Update screen
        SDL_RenderPresent(renderer);

        if (engine && m_engineFlow->DoDestroy())
        {
            m_gameRenderer->SetRenderer(nullptr);
            engine->WindowTeardown();
            engine = {};
        }

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);

        // Cleanup Texture
        //SDL_DestroyTexture(sdlTexture);
        //m_sdlTexture->Set(nullptr);
    }


    // Wait
    // Cleanup Imgui
    m_imgui->Teardown();

    // Ensure the engine knows we no longer have a window
    SDL_DestroyRenderer(m_gameRenderer->GetRenderer());
    m_gameRenderer->SetRenderer(nullptr);
    engine->WindowTeardown();

    // Cleanup Tools
    if (m_toolsEngine)
    {
        // There should be nothing here.
        m_Toolsrenderer->SetRenderer(nullptr);
        engine->WindowTeardown();
    }

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

#ifdef _DEBUG
    // Close console window in debug mode
    FreeConsole();
#endif

    return operationState;
}
