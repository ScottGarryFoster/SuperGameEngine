#include "SDLRenderer.h"

using namespace SuperGameEngine;

SDLRenderer::SDLRenderer()
{
    m_rendererState = SDLRendererState::Unknown;
    m_renderer = nullptr;
}

void SDLRenderer::SetRenderer(SDL_Renderer* newValue)
{
    m_renderer = newValue;
    if (m_renderer == nullptr)
    {
        m_rendererState = SDLRendererState::Destroyed;
    }
    else
    {
        m_rendererState = SDLRendererState::Active;
    }
}
