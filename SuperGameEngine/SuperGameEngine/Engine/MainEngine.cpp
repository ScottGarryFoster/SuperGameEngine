#include "MainEngine.h"

using namespace SuperGameEngine;

void MainEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{

}

bool MainEngine::Event(SDL_Event event)
{
    return true;
}

bool MainEngine::Update(Uint64 ticks)
{
    return true;
}

void MainEngine::Draw()
{
}

void MainEngine::WindowStart()
{
}

void MainEngine::WindowTeardown()
{
}
