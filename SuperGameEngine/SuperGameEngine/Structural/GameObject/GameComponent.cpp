#include "GameComponent.h"
#include "GameObject.h"

#include "../../../FatedQuest.Libraries/Logging/Logger.h"

using namespace SuperGameEngine;
GameComponent::GameComponent()
{

}

GameComponent::~GameComponent()
{
}

void GameComponent::Setup(SceneLoadPackage* loadPackage, GameObject* parent)
{
    Test();
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

void GameComponent::Test()
{
    Logger::Info(FString("Hello"));
}