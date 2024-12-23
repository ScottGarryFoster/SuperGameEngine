#include "ToolsEngineEntry.h"

#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

#include "../ImGuiIncludes.h"

using namespace SuperGameTools;

int ToolsEngineEntry::RunApplication(std::shared_ptr<Engine> engine)
{
    m_imgui = std::make_shared<ImGuiContainer>();
    m_toolsEngine = std::make_shared<ToolsEngine>();
    m_sdlTexture = std::make_shared<ExtremelyWeakWrapper<SDL_Texture>>(nullptr);
    m_toolsEngine->GiveSDLTexture(m_sdlTexture);

    m_gameRenderer = std::make_shared<SDLRenderer>();
    m_Toolsrenderer = std::make_shared<SDLRenderer>();
    ApplicationOperationState windowState = ApplicationOperationState::Restart;
    while (windowState != ApplicationOperationState::Close)
    {
        windowState = RunSDLWindow(engine);
    }

    return 0;
}

ApplicationOperationState ToolsEngineEntry::RunSDLWindow(std::shared_ptr<Engine> engine)
{
    // Pointers to our window and surface
    SDL_Window* window = NULL;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
    {
#ifdef _DEBUG
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
#endif

        return ApplicationOperationState::Close;
    }

    // Set SDL hint to enable VSync
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"))
    {
#ifdef _DEBUG
        std::cout << "Warning: VSync not enabled!" << std::endl;
#endif
    }

    // Create our window
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window)
    {
#ifdef _DEBUG
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
#endif

        return ApplicationOperationState::Close;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
#ifdef _DEBUG
        std::cout << "Could not create Renderer: " << SDL_GetError() << std::endl;
#endif
        // Handle renderer creation failure
        SDL_DestroyWindow(window);
        SDL_Quit();

        return ApplicationOperationState::Close;
    }

    // Initialise IMGUI
    m_imgui->Initialise(renderer, window);

    // Event handler
    SDL_Event e;

    // Setup the engine.
    m_gameRenderer->SetRenderer(renderer);
    engine->GiveRenderer(m_gameRenderer);
    engine->WindowStart();

    // Setup the Tools Engine
    if (m_toolsEngine)
    {
        m_Toolsrenderer->SetRenderer(renderer);
        m_toolsEngine->GiveRenderer(m_Toolsrenderer);
        m_toolsEngine->WindowStart();
    }

    Uint64 startTime = SDL_GetTicks64();

    // Main loop
    ApplicationOperationState operationState = ApplicationOperationState::Running;
    while (operationState == ApplicationOperationState::Running)
    {
        auto eventAnswer = ApplicationOperationState::Running;

        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            eventAnswer = engine->Event(e);
            if (eventAnswer != ApplicationOperationState::Running)
            {
                operationState = eventAnswer;
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
#ifdef _DEBUG
                std::cout << "SDL Quit" << std::endl;
#endif
                operationState = ApplicationOperationState::Close;
            }
        }

        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        ApplicationOperationState updateAnswer = engine->Update(ticksThisFrame);
        if (updateAnswer != ApplicationOperationState::Running)
        {
            operationState = updateAnswer;
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
            std::cout << "The event update and the update loop are both trying to affect the application state but do not agree on what to do." << std::endl;
            std::cout << "Event State: " << EApplicationOperationState::ToString(eventAnswer) << ". ";
            std::cout << "Update State: " << EApplicationOperationState::ToString(updateAnswer) << "." << std::endl;
        }
#endif


        // Make texture to render the SDL Viewport
        SDL_Texture* sdlTexture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
        SDL_SetRenderTarget(renderer, sdlTexture);
        SDL_RenderClear(renderer);

        // Render the game itself
        engine->Draw();
        SDL_SetRenderTarget(renderer, NULL);

        // Give the texture the tools
        m_sdlTexture->Set(sdlTexture);

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

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);

        // Cleanup Texture
        SDL_DestroyTexture(sdlTexture);
        m_sdlTexture->Set(nullptr);
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
