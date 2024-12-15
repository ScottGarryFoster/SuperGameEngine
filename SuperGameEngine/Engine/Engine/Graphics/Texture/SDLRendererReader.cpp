#include "SDLRendererReader.h"

using namespace SuperGameEngine;

SDL_Renderer* SDLRendererReader::GetRenderer()
{
    return m_renderer;
}

SDLRendererState SDLRendererReader::RendererState()
{
    return m_rendererState;
}
