#include "SDLTextureChest.h"

using namespace SuperGameEngine;

SDLTextureChest::SDLTextureChest()
{
    m_texture = nullptr;
}

SDLTextureChest::SDLTextureChest(SDL_Texture* initialValue)
{
    m_texture = initialValue;
}

SDL_Texture* SDLTextureChest::Get()
{
    return m_texture;
}

void SDLTextureChest::Set(SDL_Texture* newValue)
{
    m_texture = newValue;
}
