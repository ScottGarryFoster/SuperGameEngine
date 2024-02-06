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
}

bool GameComponent::Update(GameTime gameTime)
{
    return false;
}

void GameComponent::Draw()
{
}

void GameComponent::Test()
{
    Logger::Info(FString("Hello"));
}