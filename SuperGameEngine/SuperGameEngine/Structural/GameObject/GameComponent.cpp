#include "GameComponent.h"
#include "GameObject.h"
#include "../Spatial/Collision/Collision.h"

#include "../../LibraryIncludes.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
GameComponent::GameComponent()
{
    m_parent = nullptr;
    m_doRender = false;
    m_loadPackage = nullptr;
}

GameComponent::~GameComponent()
{
}

void GameComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    if (!loadPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Setup"), FString("loadPackage is null"));
        return;
    }

    m_loadPackage = loadPackage;
    m_parent = parent;
    m_doRender = false;
}

bool GameComponent::Update(GameTime gameTime)
{
    return false;
}

void GameComponent::FixedUpdate(GameTime gameTime)
{
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

void GameComponent::OnCollisionBegin(Collision& collision)
{
}

void GameComponent::OnCollisionOccuring(Collision& collision)
{
}

void GameComponent::OnCollisionEnd(Collision& collision)
{
}

SceneLoadPackage* SuperGameEngine::GameComponent::GetLoadPackage()
{
    return m_loadPackage;
}
