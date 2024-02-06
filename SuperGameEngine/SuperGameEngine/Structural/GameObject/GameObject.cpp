#pragma once
#include "GameObject.h"
#include "GameComponent.h"
#include "../../LibraryIncludes.h"
using namespace SuperGameEngine;
using namespace StandardCLibrary;

GameObject::GameObject()
{
    m_loadPackage = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::Setup(SceneLoadPackage* loadPackage)
{
    m_loadPackage = loadPackage;
    if (!m_loadPackage)
    {
        Logger::Error(FString("ARGUMENTNULLEXCEPTION: ") + FString("GameObject::Setup: ")
            + FString(" loadPackage was null. "));
        return;
    }
}

bool GameObject::Update(GameTime gameTime)
{
    return true;
}

void GameObject::Draw()
{

}

bool GameObject::AddActualComponentFromObject(Object* newObject)
{
    bool typeIsCorrect = TypeHelpers::IsBaseOf<GameComponent, Object>();
    if (typeIsCorrect)
    {
        GameComponent* componentPtr = dynamic_cast<GameComponent*>(newObject);
        AddActualComponent(componentPtr);
    }

    return typeIsCorrect;
}

void GameObject::AddActualComponent(GameComponent* newComponent)
{
    newComponent->Test();
    m_gameComponents.push_back(newComponent);
}