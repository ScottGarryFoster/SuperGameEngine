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

void SuperGameObject::SetGuid(const std::shared_ptr<Guid>& guid)
{
    if (!guid)
    {
        Log::Error("Empty Guid given.", "SuperGameObject::SetGuid(std::shared_ptr<Guid>)");
        return;
    }

    m_guid = guid;
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
    if (!loadPackage)
    {
        Log::Error("No load package found when setting up GameObject.",
            "SuperGameObject::Setup(std::shared_ptr<GameObjectLoadPackage>)");
        return;
    }

    m_loadPackage = loadPackage;

    m_componentPackage = std::make_shared<SuperComponentLoadPackage>();
    if (std::shared_ptr<ContentManager> contentManager = m_loadPackage->GetContentManager())
    {
        m_componentPackage->SetContentManager(contentManager);
    }
    else
    {
        Log::Error("No content manager found when setting up GameObject.",
            "SuperGameObject::Setup(std::shared_ptr<GameObjectLoadPackage>)");
    }

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

void SuperGameObject::DestroyImmediately()
{
    // Get everything
    std::vector<std::pair<std::string, std::shared_ptr<GameComponent>>> allComponents;
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        for (const std::shared_ptr<GameComponent>& gameComponent : references)
        {
            if (!gameComponent->IsDestroyed())
            {
                gameComponent->DestroyImmediately();
                allComponents.emplace_back(type, gameComponent);
            }
        }
    }

    // Components could be waiting to be updated so ensure these are counted.
    for (auto it = m_pendingGameComponents.begin(); it != m_pendingGameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        for (const std::shared_ptr<GameComponent>& gameComponent : references)
        {
            if (!gameComponent->IsDestroyed())
            {
                gameComponent->DestroyImmediately();
                allComponents.emplace_back(type, gameComponent);
            }
        }
    }

    // Mark us as destroyed.
    Destroy();

    m_gameComponents = std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>>();
    m_pendingGameComponents = std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>>();

    // Let the component do any last minute destruction.
    for (const auto typeComponent : allComponents)
    {
        typeComponent.second->OnDestroyed();
    }
}

void SuperGameObject::OnDestroyed()
{
    // Nothing.
}

std::shared_ptr<GameComponent> SuperGameObject::GetComponent(const std::string& type) const
{
    std::vector<std::shared_ptr<GameComponent>> components;
    auto it = m_gameComponents.find(type);
    if (it != m_gameComponents.end())
    {
        if (!it->second.empty())
        {
            std::vector<std::shared_ptr<GameComponent>> componentList = it->second;
            for (const std::shared_ptr<GameComponent>& gameComponent : componentList)
            {
                // Destroyed game components do not exist.
                if (!gameComponent->IsDestroyed())
                {
                    return gameComponent;
                }
            }
        }
    }

    it = m_pendingGameComponents.find(type);
    if (it != m_pendingGameComponents.end())
    {
        if (!it->second.empty())
        {
            std::vector<std::shared_ptr<GameComponent>> componentList = it->second;
            for (const std::shared_ptr<GameComponent>& gameComponent : componentList)
            {
                // Destroyed game components do not exist.
                if (!gameComponent->IsDestroyed())
                {
                    return gameComponent;
                }
            }
        }
    }

    return {};
}

std::vector<std::shared_ptr<GameComponent>> SuperGameObject::GetAllComponents() const
{
    std::vector<std::shared_ptr<GameComponent>> returnVector;
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        for (const std::shared_ptr<GameComponent>& gameComponent : references)
        {
            if (!gameComponent->IsDestroyed())
            {
                returnVector.emplace_back(gameComponent);
            }
        }
    }

    return returnVector;
}

std::vector<std::shared_ptr<GameComponent>> SuperGameObject::GetComponentsIncludingPending() const
{
    std::vector<std::shared_ptr<GameComponent>> returnVector;
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        returnVector.insert(returnVector.end(), references.begin(), references.end());
    }

    for (auto it = m_pendingGameComponents.begin(); it != m_pendingGameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        returnVector.insert(returnVector.end(), references.begin(), references.end());
    }

    // Ensure destroyed ones are not counted.
    erase_if(returnVector, [](const std::shared_ptr<GameComponent>& component) 
        { return component->IsDestroyed(); });

    return returnVector;
}

std::vector<std::pair<std::string, std::shared_ptr<GameComponent>>> SuperGameObject::GetAllComponentsByType() const
{
    std::vector<std::pair<std::string, std::shared_ptr<GameComponent>>> returnVector;
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;
        for (const std::shared_ptr<GameComponent>& gameComponent : references)
        {
            if (!gameComponent->IsDestroyed())
            {
                returnVector.emplace_back(type, gameComponent);
            }
        }
    }

    return returnVector;
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
    std::vector<std::shared_ptr<GameComponent>> destroyed;
    for (auto it = m_gameComponents.begin(); it != m_gameComponents.end(); ++it)
    {
        std::string type = it->first;
        std::vector<std::shared_ptr<GameComponent>> references = it->second;

        // Allow the component to destroy itself.
        for (const auto& c : references)
        {
            if (c->IsDestroyed())
            {
                c->DestroyImmediately();
                destroyed.push_back(c);
            }
        }

        std::erase_if(
            it->second,
            [](const std::shared_ptr<GameComponent>& c) 
            { return c->IsDestroyed(); });
    }

    // Give the components a chance to clean-up
    for (const auto& c : destroyed)
    {
        c->OnDestroyed();
    }
}


