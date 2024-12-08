#include "SuperGameObject.h"

#include "ComponentFactory.h"
#include "../Component/GameComponent.h"
#include "../../Engine/Basic/ExtremelyWeakWrapper.h"

using namespace SuperGameEngine;

SuperGameObject::SuperGameObject()
{
    m_guid = GUIDHelpers::CreateGUID();

    m_sceneGuid = std::shared_ptr<Guid>();
    m_isDestroyed = false;

    m_pointerToSelf = std::make_shared<ExtremelyWeakWrapper<GameObject>>(this);
}

SuperGameObject::~SuperGameObject()
{
    // Ensure if there is a lingering component it does not link back to this game object.
    m_pointerToSelf->Set(nullptr);
}

std::shared_ptr<Guid> SuperGameObject::GetGuid() const
{
    return m_guid;
}

std::shared_ptr<Guid> SuperGameObject::GetSceneGuid() const
{
    return m_sceneGuid;
}

void SuperGameObject::SetScene(std::shared_ptr<Guid> guid)
{
    m_sceneGuid = guid;
}

void SuperGameObject::Setup(std::shared_ptr<SceneLoadPackage> loadPackage)
{
    m_loadPackage = loadPackage;

    // TODO: Add transform here: EnsureTransformIsOnGameObject();
}

void SuperGameObject::Update(const std::shared_ptr<GameTime> gameTime)
{
    if (m_componentsAwaitUpdate)
    {
        MovePendingToMain();
        m_componentsAwaitUpdate = false;
    }

    for (const auto& componentAndType : m_gameComponents)
    {
        std::vector<std::shared_ptr<GameComponent>> components = componentAndType.second;
        for (const auto& component : components)
        {
            // TODO: Add 'Is Destroyed'
            component->Update(gameTime);
        }
    }
}

void SuperGameObject::FixedUpdate(const std::shared_ptr<GameTime> gameTime)
{
}

void SuperGameObject::Draw() const
{
    for (const auto& componentAndType : m_gameComponents)
    {
        std::vector<std::shared_ptr<GameComponent>> components = componentAndType.second;
        for (const auto& component : components)
        {
            if (component->DoRender())
            {
                component->Draw();
            }
        }
    }
}

std::shared_ptr<GameComponent> SuperGameObject::AddComponent(const std::string& type)
{
    auto component = ComponentFactory::CreateComponent(type);
    if (component)
    {
        AddActualComponent(type, component);
        return component;
        // TODO: AddActualComponentFromObject(component);
    }

    return std::shared_ptr<GameComponent>();
}

void SuperGameObject::Destroy()
{
    m_isDestroyed = true;
}

bool SuperGameObject::IsDestroyed() const
{
    return m_isDestroyed;
}

std::shared_ptr<GameComponent> SuperGameObject::GetComponent(const std::string& type) const
{
    return std::shared_ptr<GameComponent>();
}

bool SuperGameObject::AddActualComponent(const std::string& type, std::shared_ptr<GameComponent> reference)
{
    reference->Setup(m_loadPackage, m_pointerToSelf);

    AddComponentToDictionary(type, reference, m_pendingGameComponents);
    m_componentsAwaitUpdate = true;

    return true;
}

void SuperGameObject::MovePendingToMain()
{
    for (auto it = m_pendingGameComponents.begin(); it != m_pendingGameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        for (const auto& reference : references)
        {
            AddComponentToDictionary(type, reference, m_gameComponents);
        }
    }

    m_pendingGameComponents.clear();
}

void SuperGameObject::AddComponentToDictionary(
    const std::string& type, 
    std::shared_ptr<GameComponent> reference,
    std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>>& dictionaryToWriteTo)
{
    std::vector<std::shared_ptr<GameComponent>> components;
    auto it = dictionaryToWriteTo.find(type);
    if (it != dictionaryToWriteTo.end())
    {
        components = dictionaryToWriteTo[type];
    }
    else
    {
        components.push_back(reference);
    }

    dictionaryToWriteTo.insert_or_assign(type, components);
}

