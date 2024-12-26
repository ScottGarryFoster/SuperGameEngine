#include "EngineEntry.h"
#include "Engine.h"

#include <Windows.h>

#include "../Engine/Factory/EngineFactory.h"
#include "../Engine/Graphics/Texture/SDLRenderer.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

int EngineEntry::RunApplication(const std::string& engineType)
{
    m_renderer = std::make_shared<SDLRenderer>();
    ApplicationOperationState windowState = ApplicationOperationState::Restart;
    while (windowState != ApplicationOperationState::Close)
    {
        windowState = RunSDLWindow(engineType);
    }

    return 0;
}

ApplicationOperationState EngineEntry::RunSDLWindow(const std::string& engineType)
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


    // Event handler
    SDL_Event e;

    // Setup the engine.
    if (!m_engine)
    {
        m_engine = EngineFactory::CreateEngine(engineType);
        if (m_engine == nullptr)
        {
            Log::Error("Could not create Engine from factory: " + engineType);
            return ApplicationOperationState::Close;
        }
    }


    m_renderer->SetRenderer(renderer);
    m_engine->GiveRenderer(m_renderer);
    m_engine->WindowStart();

    Uint64 startTime = SDL_GetTicks64();

    // Main loop
    ApplicationOperationState operationState = ApplicationOperationState::Running;
    while (operationState == ApplicationOperationState::Running)
    {
        auto eventAnswer = ApplicationOperationState::Running;

        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            eventAnswer = m_engine->Event(e);
            if (eventAnswer != ApplicationOperationState::Running)
            {
                operationState = eventAnswer;
            }

            if (e.type == SDL_QUIT)
            {
                Log::Info("Engine has indicated from Events it would like to QUIT.");
                operationState = ApplicationOperationState::Close;
            }
        }

        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        ApplicationOperationState updateAnswer = m_engine->Update(ticksThisFrame);
        if (updateAnswer != ApplicationOperationState::Running)
        {
            operationState = updateAnswer;
        }

        // Unlikely to occur but in the situation the event and update loop
        // try to override one another we should log this, in case we get a bug
        // here.
#if defined _DEBUG || defined _TOOLS
        if (eventAnswer != ApplicationOperationState::Running &&
            updateAnswer != ApplicationOperationState::Running &&
            eventAnswer != updateAnswer)
        {
            Log::Warning("The event update and the update loop are both trying to affect the application state but do not agree on what to do."
                      "Event State: " + EApplicationOperationState::ToString(eventAnswer) +
                      "Update State: " + EApplicationOperationState::ToString(updateAnswer));
        }
#endif

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 103, 235, 229, 255);
        SDL_RenderClear(renderer);

        m_engine->Draw();

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);
    }



    // Wait
    //system("pause");

    // Ensure the engine knows we no longer have a window
    SDL_DestroyRenderer(m_renderer->GetRenderer());
    m_renderer->SetRenderer(nullptr);
    m_engine->WindowTeardown();

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
