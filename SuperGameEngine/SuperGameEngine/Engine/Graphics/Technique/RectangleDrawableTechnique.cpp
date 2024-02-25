#include <SDL.h>

#include "RectangleDrawableTechnique.h"

using namespace SuperGameEngine;
RectangleDrawableTechnique::RectangleDrawableTechnique(std::weak_ptr<Rectangle> shape)
{
    m_shape = shape;
}

RectangleDrawableTechnique::~RectangleDrawableTechnique()
{
}

void RectangleDrawableTechnique::Draw(SDL_Renderer* renderer)
{
    std::shared_ptr<Rectangle> shared = m_shape.lock();
    if (!shared)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect rect = SDL_Rect();
    rect.x = (int)shared->GetLeft();
    rect.y = (int)shared->GetTop();
    rect.w = (int)shared->GetWidth();
    rect.h = (int)shared->GetHeight();

    SDL_RenderDrawRect(renderer, &rect);
}
