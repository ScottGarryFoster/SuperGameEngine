#include "RenderDrawColourFromDebugName.h"
#include <SDL.h>

#include "Engine/Graphics/Texture/SDLRendererReader.h"

using namespace SuperGameEngine;

void RenderDrawColourFromDebugName::SetColour(const std::shared_ptr<SDLRendererReader>& renderer, DebugColourName colour) const
{
    SDL_Renderer* actualRenderer = renderer->GetRenderer();
    if (!actualRenderer)
    {
        return;
    }

    switch (colour)
    {
    case DebugColourName::Blue:
        SDL_SetRenderDrawColor(actualRenderer, 0, 0, 255, 180);
        return;
    case DebugColourName::Red:
        SDL_SetRenderDrawColor(actualRenderer, 255, 0, 0, 180);
        return;
    case DebugColourName::Cyan:
        SDL_SetRenderDrawColor(actualRenderer, 0, 255, 255, 180);
        return;
    case DebugColourName::Green:
    case DebugColourName::Default:
    case DebugColourName::Unknown:
    default:
        SDL_SetRenderDrawColor(actualRenderer, 0, 255, 0, 180);
        return;
    }
}