#include "GameComponent.h"
#include "GameObject.h"

#include "../../LibraryIncludes.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
GameComponent::GameComponent()
{
    m_parent = nullptr;
    m_doRender = false;
}

GameComponent::~GameComponent()
{
}

void GameComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    m_doRender = false;
}

bool GameComponent::Update(GameTime gameTime)
{
    return false;
}

void GameComponent::Draw()
{
}

GameObject* GameComponent::GetParent()
{
    return m_parent;
}

bool SuperGameEngine::GameComponent::DoRender() const
{
    return m_doRender;
}

void SuperGameEngine::GameComponent::SetDoRender(bool newValue)
{
    m_doRender = newValue;
}
