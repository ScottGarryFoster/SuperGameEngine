#include "SDLWindowManager.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/AllReferences.h"
#include <SDL.h>

#include "Engine/Foundation/ProjectProperties.h"
#include "Engine/Graphics/Texture/SDLRenderer.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SDLWindowManager::SDLWindowManager()
{
    m_window = nullptr;
    m_defaultRenderer = std::make_shared<SDLRenderer>();
}

SDLWindowManager::~SDLWindowManager()
{
    if (m_window != nullptr)
    {
        DestroySDLWindow();
    }

    if (m_defaultRenderer->RendererState() == SDLRendererState::Active)
    {
        DestroySDLWindow();
    }
}

void SDLWindowManager::Setup(const std::shared_ptr<ProjectProperties>& projectProperties)
{
    m_projectProperties = projectProperties;
}

bool SDLWindowManager::CreateGameWindow(
    const std::string& name, 
    WindowPredefinedPosition position,
    const FPoint& size)
{
    if (m_window != nullptr)
    {
        DestroyWindow();
    }

    if (m_defaultRenderer->RendererState() == SDLRendererState::Active)
    {
        DestroyWindow();
    }

    // Set SDL hint to enable VSync
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"))
    {
        Log::Error("Warning: VSync not enabled!");
        return false;
    }

    // Create our window
    FPoint actualPosition = PredefinedPositionConverter(position);
    m_window = SDL_CreateWindow(m_projectProperties->GetWindowTitle().c_str(), actualPosition.GetX(), actualPosition.GetY(), 1280, 720, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!m_window)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Error creating window: " + sdlError);
        return false;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::string sdlError = SDL_GetError();
        Log::Error("Could not create Renderer: " + sdlError);

        // Handle renderer creation failure
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    m_defaultRenderer->SetRenderer(renderer);
    return true;
}

void SDLWindowManager::DestroyWindow()
{
    DestroySDLWindow();
}

std::shared_ptr<SDLRenderer> SDLWindowManager::GetDefaultRenderer() const
{
    return m_defaultRenderer;
}

void SDLWindowManager::DestroySDLWindow()
{
    // Ensure the engine knows we no longer have a window
    if (m_defaultRenderer->RendererState() == SDLRendererState::Active)
    {
        SDL_DestroyRenderer(m_defaultRenderer->GetRenderer());
        m_defaultRenderer->SetRenderer(nullptr);
    }

    // Destroy the window. This will also destroy the surface
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

FPoint SDLWindowManager::PredefinedPositionConverter(WindowPredefinedPosition position) const
{
    auto returnPosition = FPoint(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
    switch (position)
    {
    case WindowPredefinedPosition::Unknown:
        returnPosition.SetXYValue(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
        break;
    case WindowPredefinedPosition::Centered:
        returnPosition.SetXYValue(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        break;
    default:
        Log::Error("Do not have a window position for the given type. Type: "
            + EWindowPredefinedPosition::ToString(position),
            "FPoint SDLWindowManager::PredefinedPositionConverter(WindowPredefinedPosition)");
        break;
    }

    return returnPosition;
}
