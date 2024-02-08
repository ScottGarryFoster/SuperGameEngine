#include "GameComponent.h"
#include "GameObject.h"

#include "../../../FatedQuest.Libraries/Logging/Logger.h"
#include "../../../FatedQuest.Libraries/StandardCLibrary/Collection/Organised/FList.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
GameComponent::GameComponent()
{
    FList<FString> collection(FString("Insde"));
    collection.Add(FString("Something else"));
    collection.Add(FString("Pokemon 2"));

    Logger::Info(FString("=============="));

    for (FString val : collection)
    {
        Logger::Info(val.AsStdString());
    }

    Logger::Info(FString("=============="));

    for (FString val : collection.Where([](const FString& c) { return c.ToLower().AsStdString() == "something else"; }))
    {
        Logger::Info(val.AsStdString());
    }

    Logger::Info(FString("=============="));
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