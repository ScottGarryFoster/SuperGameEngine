#include "SuperGameObject.h"

#include "ComponentFactory.h"
#include "../Component/GameComponent.h"
#include "../../Engine/Basic/ExtremelyWeakWrapper.h"
#include "../../Structural/Packages/SuperComponentLoadPackage.h"
#include "../Packages/GameObjectLoadPackage.h"

using namespace SuperGameEngine;

SuperGameObject::SuperGameObject()
{
    m_guid = GUIDHelpers::CreateGUID();

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

void SuperGameObject::Setup(std::shared_ptr<GameObjectLoadPackage> loadPackage)
{
    m_loadPackage = loadPackage;

    m_componentPackage = std::make_shared<SuperComponentLoadPackage>();
    m_componentPackage->SetContentManager(m_loadPackage->GetContentManager());

    // TODO: Add transform here: EnsureTransformIsOnGameObject();
}

void SuperGameObject::Update(const std::shared_ptr<GameTime> gameTime)
{
    if (m_componentsAwaitUpdate)
    {
        MovePendingToMain();
        m_componentsAwaitUpdate = false;
    }

    bool isAtLeastOneDestroyed = false;
    for (const auto& componentAndType : m_gameComponents)
    {
        std::vector<std::shared_ptr<GameComponent>> components = componentAndType.second;
        for (const auto& component : components)
        {
            if (component->IsDestroyed())
            {
                isAtLeastOneDestroyed = true;
            }
            else
            {
                component->Update(gameTime);
            }

        }
    }

    // Technically we could miss a destroyed component for
    // one cycle as one component could make another destroyed
    // which was earlier in the list. However the idea is that
    // components are destroy when we want to and this method saves
    // another loop or exposing a method for the component to speak to the GO
    // to say like "Hey, I'm destroyed clean me up"
    if (isAtLeastOneDestroyed)
    {
        RemoveDestroyedComponents();
        isAtLeastOneDestroyed = false;
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
            if (component->DoRender() && !component->IsDestroyed())
            {
                component->Draw();
            }
        }
    }
}

std::shared_ptr<GameComponent> SuperGameObject::AddComponent(const std::string& type)
{
    if (std::shared_ptr<GameComponent> component = ComponentFactory::CreateComponent(type))
    {
        AddActualComponent(type, component);
        return component;
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
    std::vector<std::shared_ptr<GameComponent>> components;
    auto it = m_gameComponents.find(type);
    if (it != m_gameComponents.end())
    {
        if (!it->second.empty())
        {
            return it->second.front();
        }
    }

    it = m_pendingGameComponents.find(type);
    if (it != m_pendingGameComponents.end())
    {
        if (!it->second.empty())
        {
            return it->second.front();
        }
    }

    return {};
}

bool SuperGameObject::AddActualComponent(const std::string& type, const std::shared_ptr<GameComponent>& reference)
{
    reference->Setup(m_componentPackage, m_pointerToSelf);

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
        components.push_back(reference);
    }
    else
    {
        components.push_back(reference);
    }

    dictionaryToWriteTo.insert_or_assign(type, components);
}

void SuperGameObject::RemoveDestroyedComponents()
{
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;

        std::erase_if(
            it->second,
            [](const std::shared_ptr<GameComponent>& c) 
            { return c->IsDestroyed(); });
    }
}


