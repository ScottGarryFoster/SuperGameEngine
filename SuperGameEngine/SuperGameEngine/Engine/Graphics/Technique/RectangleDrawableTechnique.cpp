#include <SDL.h>

#include "RectangleDrawableTechnique.h"

using namespace SuperGameEngine;
RectangleDrawableTechnique::RectangleDrawableTechnique(std::weak_ptr<Rectangle> shape)
{
    m_shape = shape;
    red = 0;
    green = 0;
    blue = 0;
    alpha = 255;
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

    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);

    SDL_Rect rect = SDL_Rect();
    rect.x = (int)shared->GetLeft();
    rect.y = (int)shared->GetTop();
    rect.w = (int)shared->GetWidth();
    rect.h = (int)shared->GetHeight();

    SDL_RenderDrawRect(renderer, &rect);
}

void SuperGameEngine::RectangleDrawableTechnique::UpdateColour(int r, int g, int b, int a)
{
    red = r < 0 ? 0 : r > 255 ? 255 : r;
    green = g < 0 ? 0 : g > 255 ? 255 : g;
    blue = b < 0 ? 0 : b > 255 ? 255 : b;
    alpha = a < 0 ? 0 : a > 255 ? 255 : a;
}
