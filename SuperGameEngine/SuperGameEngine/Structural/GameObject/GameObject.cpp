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
    if (!loadPackage)
    {
        Logger::Exception(ArgumentNullException(), GetTypeName(), FString("Setup"), FString("loadPackage is null"));
        return;
    }
    m_loadPackage = loadPackage;
}

bool GameObject::Update(GameTime gameTime)
{
    for (size_t i = 0; i < m_gameComponents.size(); ++i)
    {
        GameComponent* component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->Update(gameTime);
        }
    }

    return true;
}

void GameObject::Draw()
{
    for (size_t i = 0; i < m_gameComponents.size(); ++i)
    {
        GameComponent* component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->Draw();
        }
    }
}

bool GameObject::AddActualComponentFromObject(Object* newObject)
{
    bool typeIsCorrect = TypeHelpers::IsDerivedFrom<Object, GameComponent>();
    if (typeIsCorrect)
    {
        GameComponent* componentPtr = dynamic_cast<GameComponent*>(newObject);
        AddActualComponent(componentPtr);
    }

    return typeIsCorrect;
}

void GameObject::AddActualComponent(GameComponent* newComponent)
{
    if (m_loadPackage == nullptr)
    {
        Logger::Exception(SystemNullReference(), GetTypeName(), FString("AddActualComponent"),
            FString("Cannot add Component because do not have scene load package."));
        return;
    }
    newComponent->Setup(m_loadPackage, this);
    m_gameComponents.push_back(newComponent);
}