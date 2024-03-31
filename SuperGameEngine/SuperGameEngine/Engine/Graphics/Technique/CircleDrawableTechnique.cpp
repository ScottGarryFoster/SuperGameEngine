#include "CircleDrawableTechnique.h"

using namespace SuperGameEngine;
using namespace StandardCLibrary;;
CircleDrawableTechnique::CircleDrawableTechnique(std::weak_ptr<Circle> shape)
{
    m_shape = shape;
    red = 0;
    green = 0;
    blue = 0;
    alpha = 255;
}

CircleDrawableTechnique::~CircleDrawableTechnique()
{

}

void CircleDrawableTechnique::Draw(SDL_Renderer* renderer)
{
    std::shared_ptr<Circle> shared = m_shape.lock();
    if (!shared)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);

    FVector2D location = shared->GetLocation();
    int radius = shared->GetRadius();

    DrawOutline(renderer, location, radius);
}

void CircleDrawableTechnique::SetColour(int r, int g, int b, int a)
{
    red = r < 0 ? 0 : r > 255 ? 255 : r;
    green = g < 0 ? 0 : g > 255 ? 255 : g;
    blue = b < 0 ? 0 : b > 255 ? 255 : b;
    alpha = a < 0 ? 0 : a > 255 ? 255 : a;
}

void CircleDrawableTechnique::DrawFilledIn(SDL_Renderer* renderer, FVector2D& location, int radius)
{
    int x = (int)location.GetX();
    int y = (int)location.GetY();

    for (int width = 0; width < radius * 2; ++width)
    {
        for (int height = 0; height < radius * 2; ++height)
        {
            int adjustedX = radius - width;
            int adjustedY = radius - height;
            if ((adjustedX * adjustedX + adjustedY * adjustedY) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + adjustedX, y + adjustedY);
            }
        }
    }
}

/// <remarks>
/// Taken from this link:
/// https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
/// </remarks>
void CircleDrawableTechnique::DrawOutline(SDL_Renderer* renderer, FVector2D& location, int radius)
{
    int x = (int)location.GetX();
    int y = (int)location.GetY();

    int centerX = radius - 1;
    int centerY = 0;
    int totalX = 1;
    int totalY = 1;
    int error = totalX - (radius << 1);

    while (centerX >= centerY)
    {
        SDL_RenderDrawPoint(renderer, x + centerX, y + centerY);
        SDL_RenderDrawPoint(renderer, x + centerY, y + centerX);
        SDL_RenderDrawPoint(renderer, x - centerY, y + centerX);
        SDL_RenderDrawPoint(renderer, x - centerX, y + centerY);
        SDL_RenderDrawPoint(renderer, x - centerX, y - centerY);
        SDL_RenderDrawPoint(renderer, x - centerY, y - centerX);
        SDL_RenderDrawPoint(renderer, x + centerY, y - centerX);
        SDL_RenderDrawPoint(renderer, x + centerX, y - centerY);

        if (error <= 0)
        {
            centerY++;
            error += totalY;
            totalY += 2;
        }
        if (error > 0)
        {
            centerX--;
            totalX += 2;
            error += totalX - (radius << 1);
        }
    }
}
