#include "MainEngine.h"

using namespace SuperGameEngine;

void MainEngine::GiveRenderer(std::shared_ptr<SDLRendererReader> renderer)
{

}

void MainEngine::GiveInput(const std::shared_ptr<SuperGameInput::InputHandler>& inputHandler)
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
