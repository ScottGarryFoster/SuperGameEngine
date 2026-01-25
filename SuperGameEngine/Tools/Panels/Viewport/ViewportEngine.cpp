#include "ViewportEngine.h"

#include "Engine/Content/SuperTextureManager.h"
#include "Structural/Assets/Texture/TextureAsset.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ViewportEngine::ViewportEngine()
{
}

ViewportEngine::~ViewportEngine()
{
}

void ViewportEngine::GiveRenderer(std::shared_ptr<SuperGameEngine::SDLRendererReader> renderer)
{
    m_renderer = renderer;
}

void ViewportEngine::GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager)
{
    m_inputManager = inputManager;
}

void ViewportEngine::GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

ApplicationOperationState ViewportEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ViewportEngine::Update(Uint64 ticks)
{
    return ApplicationOperationState::Running;
}

void ViewportEngine::Draw()
{
    testTexture->Draw();
}

void ViewportEngine::WindowStart()
{
    auto textureManager = std::make_shared<SuperTextureManager>(m_renderer, m_gamePackage);
    m_textureManager = textureManager;
    textureManager->UpdateDistributedWeakPointer(m_textureManager);
    testTexture = m_textureManager->GetTextureAsset("Engine\\TestImages\\collideCircle.png");
}

void ViewportEngine::WindowTeardown()
{
}
