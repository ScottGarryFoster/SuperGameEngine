#include "DebugEngine.h"

using namespace SuperEngineDebug;
using namespace SuperGameEngine;

void DebugEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{
}

bool DebugEngine::Event(SDL_Event event)
{
    return true;
}

bool DebugEngine::Update(Uint64 ticks)
{
    return true;
}

void DebugEngine::Draw()
{
}

void DebugEngine::WindowStart()
{
}

void DebugEngine::WindowTeardown()
{
}
