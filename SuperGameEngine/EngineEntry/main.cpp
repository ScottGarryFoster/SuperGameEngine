#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "../StandardCLibrary/FString.h"
#include "../Logging/Logger.h"
#include "../SuperGameEngine/Native/Graphics/Texture.h"

using namespace StandardCLibrary;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

#ifdef _DEBUG
    AllocConsole();
    FILE* pCout;
    FILE* pCerr;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    freopen_s(&pCerr, "CONOUT$", "w", stderr);
    std::cout << "Super Game Engine Version 0.0.1 Pre-Alpha" << std::endl;
#endif

    // Pointers to our window and surface
    SDL_Surface* winSurface = NULL;
    SDL_Window* window = NULL;
    
    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
#ifdef _DEBUG
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
#endif
        system("pause");
        // End the program
        return 1;
    }

    // Create our window
    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window)
    {
#ifdef _DEBUG
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
#endif
        system("pause");
        // End the program
        return 1;
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
        return 1;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    Texture* texture = nullptr;

    // Main loop
    while (!quit)
    {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
#ifdef _DEBUG
                std::cout << "SDL Quit" << std::endl;
#endif
                quit = true;
            }
        }


        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 103, 235, 229, 255);
        SDL_RenderClear(renderer);

        if (texture == nullptr)
        {
            std::vector<FString>* errors = new std::vector<FString>();
            texture = new Texture(renderer);
            if (!texture->LoadImageFromFile(FString("E:/Development/SuperGameEngine-SDL/A_pressed.png"), *errors))
            {
                for (const FString str : *errors)
                {
                    Logger::Info(StandardCLibrary::FString(str));
                } 
            }

            delete errors;
        }

        if (texture != nullptr)
        {
            texture->Draw();
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to avoid 100% CPU usage
        SDL_Delay(10);
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

    // End the program
    return 0;
}