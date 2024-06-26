#pragma once
#include "GameObject.h"
#include "GameComponent.h"
#include "../../LibraryIncludes.h"
#include "../Components/Spatial/TransformComponent.h"
#include "../Spatial/Collision/Collision.h"
#include "../../Structural/Components/Colliders/Collider.h"
#include "../Scene/SceneToGameObjectPackage.h"
#include "../Spatial/Collision/CollisionDectection.h"
#include "../../Structural/Scene/GrandScene.h"
using namespace SuperGameEngine;
using namespace StandardCLibrary;

SuperGameEngine::GameObject::GameObject()
{
    m_guid = GUIDHelpers::CreateGUID();

    m_gameObjectPackage = nullptr;
    m_loadPackage = nullptr;
    m_sceneGuid = std::shared_ptr<Guid>();
    m_isDestroyed = false;
}

GameObject::~GameObject()
{
    m_transform.reset();
    m_guid.reset();
}

std::shared_ptr<Guid> GameObject::GetGuid()
{
    return m_guid;
}

std::shared_ptr<Guid> GameObject::GetSceneGuid()
{
    return m_sceneGuid;
}

void GameObject::SetScene(std::shared_ptr<Guid> guid)
{
    m_sceneGuid = guid;
}

void GameObject::Setup(SceneLoadPackage* loadPackage, SceneToGameObjectPackage* gameObjectPackage)
{
    if (!loadPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), 
            FString("Setup"), FString("loadPackage is null"));
        return;
    }
    m_loadPackage = loadPackage;

    if (!gameObjectPackage)
    {
        Logger::Assert(ArgumentNullException(), GetTypeName(), 
            FString("Setup"), FString("gameObjectPackage is null"));
        return;
    }
    m_gameObjectPackage = gameObjectPackage;

    EnsureTransformIsOnGameObject();
}

bool GameObject::Update(const GameTime gameTime)
{
    if (m_componentNeedsSetup)
    {
        for (size_t i = 0; i < m_gameComponents.Count(); ++i)
        {
            std::shared_ptr<GameComponent> component = m_gameComponents[i];
            if (m_gameComponents[i] != nullptr)
            {
                if (!component->IsSetup())
                {
                    component->Setup(m_loadPackage, this);
                }
            }

        }

        m_componentNeedsSetup = false;
    }

    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->Update(gameTime);
        }
    }


    return true;
}

void GameObject::FixedUpdate(const GameTime gameTime)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            if (component->IsSetup())
            {
                component->FixedUpdate(gameTime);
            }
        }
    }
}

void GameObject::Draw()
{
    FList<std::shared_ptr<GameComponent>> componentsToDraw = m_gameComponents
        .Where([](const std::shared_ptr<GameComponent> c) 
            { return c->DoRender(); });
    for (size_t i = 0; i < componentsToDraw.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = componentsToDraw[i];
        if (componentsToDraw[i] != nullptr)
        {
            component->Draw();
        }
    }
}

void GameObject::OnCollisionBegin(Collision& collision)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->OnCollisionBegin(collision);
        }
    }
}

void GameObject::OnCollisionOccuring(Collision& collision)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->OnCollisionOccuring(collision);
        }
    }
}

void GameObject::OnCollisionEnd(Collision& collision)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            component->OnCollisionEnd(collision);
        }
    }
}

std::shared_ptr<TransformComponent> GameObject::GetTransformComponent()
{
    return m_transform;
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
    return m_transform;
}

std::shared_ptr<GameObject> GameObject::CreateNewGameObject()
{
    return m_gameObjectPackage->GetScene()->CreateNewGameObject(this);
}

void GameObject::OnGameObjectDestroyed(const Guid& guid)
{
    for (size_t i = 0; i < m_gameComponents.Count(); ++i)
    {
        std::shared_ptr<GameComponent> component = m_gameComponents[i];
        if (m_gameComponents[i] != nullptr)
        {
            if (component->IsSetup())
            {
                component->OnGameObjectDestroyed(guid);
            }
        }

    }
}

void GameObject::Destroy()
{
    m_isDestroyed = true;
}

bool GameObject::IsDestroyed() const
{
    return m_isDestroyed;
}

bool GameObject::AddActualComponentFromObject(std::shared_ptr<Object> newObject)
{
    bool typeIsCorrect = TypeHelpers::IsDerivedFrom<Object, GameComponent>();
    if (typeIsCorrect)
    {
        std::shared_ptr<GameComponent> componentPtr = std::static_pointer_cast<GameComponent>(newObject);
        AddActualComponent(componentPtr);
    }

    return typeIsCorrect;
}

void GameObject::AddActualComponent(std::shared_ptr<GameComponent> newComponent)
{
    if (m_loadPackage == nullptr)
    {
        Logger::Assert(SystemNullReference(), GetTypeName(), FString("AddActualComponent"),
            FString("Cannot add Component because do not have scene load package."));
        return;
    }

    m_componentNeedsSetup = true;

    std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(newComponent);
    if (collider)
    {
        m_gameObjectPackage->GetCollisionDectection()->GiveActiveCollider(collider);
    }

    m_gameComponents.Add(newComponent);
}

void GameObject::EnsureTransformIsOnGameObject()
{
    if (m_transform) 
    {
        return;
    }

    std::shared_ptr<TransformComponent> transform = GetGameComponent<TransformComponent>();
    if (transform == nullptr)
    {
        transform = AddComponent<TransformComponent>();
    }

    m_transform = transform;
}
