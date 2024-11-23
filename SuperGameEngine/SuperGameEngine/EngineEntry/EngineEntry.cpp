#include "EngineEntry.h"
#include "Engine.h"

#include <SDL.h>
#include <Windows.h>
#ifdef _DEBUG
    #include <iostream>
#endif

using namespace SuperGameEngine;

int EngineEntry::RunApplication(std::shared_ptr<Engine> engine)
{
    WindowExit windowState = WindowExit::Restart;
    while (windowState != WindowExit::Close)
    {
        windowState = RunSDLWindow(engine);
    }

    return 0;
}

WindowExit SuperGameEngine::EngineEntry::RunSDLWindow(std::shared_ptr<Engine> engine)
{
    // Pointers to our window and surface
    SDL_Surface* winSurface = NULL;
    SDL_Window* window = NULL;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
    {
#ifdef _DEBUG
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
#endif

        return WindowExit::Close;
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
        
        return WindowExit::Close;
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

        return WindowExit::Close;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    //GrandScene* grandScene = new GrandScene(renderer);
    Uint64 startTime = SDL_GetTicks64();

    // Main loop
    while (!quit)
    {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (!engine->Event(e))
            {
                quit = true;
            }

            if (e.type == SDL_QUIT)
            {
#ifdef _DEBUG
                std::cout << "SDL Quit" << std::endl;
#endif
                quit = true;
            }
        }

        Uint64 currentTime = SDL_GetTicks64();
        Uint64 ticksThisFrame = currentTime - startTime;
        startTime = currentTime;

        if (!engine->Update(ticksThisFrame))
        {
            quit = true;
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 103, 235, 229, 255);
        SDL_RenderClear(renderer);

        engine->Draw();

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(3);
    }

    // Wait
    //system("pause");

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

#ifdef _DEBUG
    // Close console window in debug mode
    FreeConsole();
#endif

    return WindowExit::Close;
}
