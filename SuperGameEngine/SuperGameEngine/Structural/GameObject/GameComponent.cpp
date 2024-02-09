#include "GameComponent.h"
#include "GameObject.h"

#include "../../LibraryIncludes.h"

using namespace StandardCLibrary;
using namespace SuperGameEngine;
GameComponent::GameComponent()
{
    m_parent = nullptr;

    FString s = FString("Insde");
    FList<FString> collection(s);
    collection.Add(FString("Something else"));
    collection.Add(FString("Pokemon 2"));
    collection.Add(FString("Bulbasaur"));
    collection.Add(FString("Bayleef"));

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

    FCollection<std::string> selectedSquares = collection.Select<std::string>([](const FString& num){ return num.AsStdString(); });

    Logger::Info(FString("As string::"));
    for (std::string val : selectedSquares)
    {
        Logger::Info(FString(val));
    }
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