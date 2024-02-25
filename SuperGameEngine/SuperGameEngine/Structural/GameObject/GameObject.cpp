#pragma once
#include "GameObject.h"
#include "GameComponent.h"
#include "../../LibraryIncludes.h"
#include "../Components/Spatial/TransformComponent.h"
using namespace SuperGameEngine;
using namespace StandardCLibrary;

GameObject::GameObject()
{
    m_loadPackage = nullptr;
    m_transform = nullptr;
}

GameObject::~GameObject()
{

}

void GameObject::Setup(SceneLoadPackage* loadPackage)
{
    if (!loadPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), FString("Setup"), FString("loadPackage is null"));
        return;
    }
    m_loadPackage = loadPackage;

    EnsureTransformIsOnGameObject();
}

bool GameObject::Update(GameTime gameTime)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
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
    FList<GameComponent*> componentsToDraw = m_gameComponents
        .Where([](const GameComponent* c) { return c->DoRender(); });
    for (size_t i = 0; i < componentsToDraw.Count(); ++i)
    {
        GameComponent* component = componentsToDraw[i];
        if (componentsToDraw[i] != nullptr)
        {
            component->Draw();
        }
    }
}

TransformComponent* GameObject::GetTransform()
{
    return m_transform;
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
        Logger::Assert(SystemNullReference(), GetTypeName(), FString("AddActualComponent"),
            FString("Cannot add Component because do not have scene load package."));
        return;
    }
    newComponent->Setup(m_loadPackage, this);
    newComponent->SetDoRender(true);
    m_gameComponents.Add(newComponent);
}

void GameObject::EnsureTransformIsOnGameObject()
{
    if (m_transform != nullptr)
    {
        return;
    }

    TransformComponent* transform = GetGameComponent<TransformComponent>();
    if (transform == nullptr)
    {
        transform = AddComponent<TransformComponent>();
    }

    m_transform = transform;
}
