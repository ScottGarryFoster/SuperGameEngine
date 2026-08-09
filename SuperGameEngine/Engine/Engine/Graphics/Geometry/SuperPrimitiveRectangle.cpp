#include "SuperPrimitiveRectangle.h"

#include <SDL_rect.h>

#include "Engine/Graphics/Texture/SDLRendererReader.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperPrimitiveRectangle::SuperPrimitiveRectangle(
    const std::shared_ptr<SDLRendererReader>& renderer,
    const FVector2F& location,
    const FVector2F& size)
    : m_rectangle(location.GetX(), location.GetY(), size.GetX(), size.GetY())
{
    m_renderer = renderer;
    m_debugColours = RenderDrawColourFromDebugName();
}

void SuperPrimitiveRectangle::Move(const FVector2F& newLocation)
{
    m_rectangle.SetLocation(newLocation.GetX(), newLocation.GetY());
}

void SuperPrimitiveRectangle::Draw() const
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        auto rect = SDL_Rect(
            static_cast<int>(m_rectangle.GetLeft()), 
            static_cast<int>(m_rectangle.GetTop()), 
            static_cast<int>(m_rectangle.GetWidth()), 
            static_cast<int>(m_rectangle.GetHeight()));

        SDL_Renderer* renderer = m_renderer->GetRenderer();
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 180);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
}

void SuperPrimitiveRectangle::SetSize(const FVector2F& newSize)
{
    m_rectangle.SetSize(newSize.GetX(), newSize.GetY());
}

void SuperPrimitiveRectangle::DrawInPlace(int x, int y, int width, int height) const
{
    DrawInPlace(x, y, width, height, DebugColourName::Default);
}

void SuperPrimitiveRectangle::DrawInPlace(int x, int y, int width, int height, DebugColourName colour) const
{
    if (m_renderer->RendererState() == SDLRendererState::Active)
    {
        auto rect = SDL_Rect(x, y, width, height);

        SDL_Renderer* renderer = m_renderer->GetRenderer();
        m_debugColours.SetColour(m_renderer, colour);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
}
