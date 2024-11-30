#include "MainEngine.h"

using namespace SuperGameEngine;

void MainEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{

}

ApplicationOperationState MainEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState MainEngine::Update(Uint64 ticks)
{
    return ApplicationOperationState::Running;
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
