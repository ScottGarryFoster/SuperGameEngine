#include "ViewportEngine.h"

#include "Engine/Content/ContentManager.h"
#include "Engine/CrossEngineObjects/CrossEngineObjects.h"
#include "Engine/Content/SuperTextureManager.h"
#include "Engine/CrossEngineObjects/OnSceneUpdatedEventArguments.h"
#include "Engine/CrossEngineObjects/SharedSceneChangedEvents.h"
#include "GameEngineEquivalents/Component/Component.h"
#include "GameEngineEquivalents/Component/ComponentDataChangedEventArguments.h"
#include "GameEngineEquivalents/Component/ToolsComponent.h"
#include "GameEngineEquivalents/GameObject/GameObject.h"
#include "GameEngineEquivalents/Scene/Scene.h"
#include "GameEngineEquivalents/SerializableProperties/TextureAssetSerializableProperty.h"
#include "GameEngineEquivalents/SerializableProperties/ToolsSerializableProperty.h"
#include "GameEngineEquivalents/SerializableProperties/Vector2FSerializableProperty.h"
#include "Panels/SceneHierarchy/EventArguments/OnMenuAddComponentEventArguments.h"
#include "Panels/SceneHierarchy/EventArguments/OnMenuDeleteComponentEventArguments.h"
#include "Panels/SceneHierarchy/EventArguments/OnMenuDeleteGameObjectEventArguments.h"
#include "Structural/Assets/Texture/TextureAsset.h"
#include "Structural/Serializable/SerializableProperty.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ViewportEngine::ViewportEngine()
{
    m_currentScene = nullptr;
}

ViewportEngine::~ViewportEngine()
{
}

void ViewportEngine::GiveRenderer(std::shared_ptr<SuperGameEngine::SDLRendererReader> renderer)
{
    m_renderer = renderer;
}

void ViewportEngine::GiveInput(const std::shared_ptr<SuperGameInput::SDLInputManager>& inputManager)
{
    m_inputManager = inputManager;
}

void ViewportEngine::GiveGamePackage(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage)
{
    m_gamePackage = gamePackage;
}

void ViewportEngine::GiveControls(const std::shared_ptr<SuperGameEngine::EngineControls>& engineControls)
{
    m_engineControls = engineControls;
}

ApplicationOperationState ViewportEngine::Event(SDL_Event event)
{
    return ApplicationOperationState::Running;
}

ApplicationOperationState ViewportEngine::Update(Uint64 ticks)
{
    if (!m_currentScene)
    {
        return ApplicationOperationState::Running;
    }

    return ApplicationOperationState::Running;
}

void ViewportEngine::Draw()
{
    for (const std::pair<const uint64_t, ViewportObjectDrawBundle>& drawBundle : m_drawBundle)
    {
        if (!drawBundle.second.IsValidToRender)
        {
            continue;
        }

        drawBundle.second.TextureAsset->Draw(0, drawBundle.second.TransformPosition);
    }
}

void ViewportEngine::WindowStart()
{
}

void ViewportEngine::WindowTeardown()
{
}

void ViewportEngine::EngineStart()
{
    const std::shared_ptr<SharedSceneChangedEvents>& sharedEvents = m_crossEngineObjects->GetSharedSceneChangedEvents();
    if (!sharedEvents)
    {
        Log::Error("No shared events given to Viewport Engine. "
                   "This will not be able to render a scene.",
            "void ViewportEngine::EngineStart()");
        return;
    }

    sharedEvents->OnSceneLoaded()->Subscribe(shared_from_this());
    sharedEvents->OnComponentAdded()->Subscribe(shared_from_this());
    sharedEvents->OnComponentDeleted()->Subscribe(shared_from_this());
    sharedEvents->OnGameObjectDeleted()->Subscribe(shared_from_this());
}

void ViewportEngine::EngineEnd()
{
    // If you stored the scene ensure you let it go here.
}

void ViewportEngine::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto onSceneArgs = std::dynamic_pointer_cast<OnSceneUpdatedEventArguments>(arguments))
    {
        SetupNewScene(onSceneArgs->GetScene());
    }
    else if (auto componentChangedArgs = std::dynamic_pointer_cast<ComponentDataChangedEventArguments>(arguments))
    {
        ChangeDrawBundleBasedOnComponentChange(componentChangedArgs->GetGameObjectGuid(), componentChangedArgs->GetComponentGuid());
    }
    else if (auto componentAdded = std::dynamic_pointer_cast<OnMenuAddComponentEventArguments>(arguments))
    {
        OnComponentAdded(componentAdded->GetComponent()->GetObjectGuid(), componentAdded->GetComponent()->GetUniqueID());
    }
    else if (auto componentDeleted = std::dynamic_pointer_cast<OnMenuDeleteComponentEventArguments>(arguments))
    {
        OnComponentRemoved(componentDeleted->GetComponent());
        Log::Info("Component Deleted");
    }
    else if (auto gameObjectDeleted = std::dynamic_pointer_cast<OnMenuDeleteGameObjectEventArguments>(arguments))
    {
        OnGameObjectDeleted(gameObjectDeleted->GetGameObject());
    }
}

void ViewportEngine::GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects)
{
    m_crossEngineObjects = crossEngineObjects;
    m_crossEngineObjects->OnNewScene()->Subscribe(shared_from_this());
}

void ViewportEngine::SetupNewScene(const std::shared_ptr<Scene>& newScene)
{
    m_drawBundle.clear();
    m_currentScene = newScene;
    for (const std::shared_ptr<GameObject>& gameObject : m_currentScene->GetGameObjects())
    {
        AddGameObjectToScene(gameObject);
    }
}

void ViewportEngine::AddGameObjectToScene(const std::shared_ptr<GameObject>& gameObject)
{
    auto drawBundle = ViewportObjectDrawBundle();
    for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
    {
        bool foundType = false;
        if (component->GetType() == "SpriteComponent")
        {
            foundType = true;
            ExractSpriteDrawBundleProperties(drawBundle, component);
        }
        else if (component->GetType() == "TransformComponent")
        {
            foundType = true;
            ExtractTransformDrawBundleProperties(drawBundle, component);
        }

        if (foundType)
        {
            component->OnPropertyChanged()->Subscribe(shared_from_this());
        }
    }

    ValidateDrawBundle(drawBundle);

    // TODO: Remove this testing.
    if (drawBundle.IsValidToRender)
    {
        Log::Info("TESTING: GUID added: " + gameObject->GetGuid()->ToString());
        m_drawBundle.insert_or_assign(gameObject->GetGuid()->AsNumber(), drawBundle);
    }
    else
    {
        Log::Error("Not valid to render object, defined in: " + gameObject->GetGuid()->ToString());
    }
}

void ViewportEngine::ExractSpriteDrawBundleProperties(ViewportObjectDrawBundle& drawBundle, const std::shared_ptr<Component>& component) const
{
    if (auto toolsComponent = std::dynamic_pointer_cast<ToolsComponent>(component))
    {
        for (const std::shared_ptr<ToolsSerializableProperty>& property : toolsComponent->GetToolsProperties())
        {
            if (property->GetEngineProperty()->GetType() != SerializableDataType::TextureAsset)
            {
                continue;
            }

            if (auto textureProperty = std::dynamic_pointer_cast<TextureAssetSerializableProperty>(property))
            {
                // We are an engine, ensure to use this version.
                drawBundle.TextureAsset = m_crossEngineObjects->
                    GetEngineTextureManager()->GetTextureAsset(textureProperty->GetTextureValue());
            }
        }
    }
}

void ViewportEngine::ExtractTransformDrawBundleProperties(ViewportObjectDrawBundle& drawBundle, const std::shared_ptr<Component>& component) const
{
    if (auto toolsComponent = std::dynamic_pointer_cast<ToolsComponent>(component))
    {
        for (const std::shared_ptr<ToolsSerializableProperty>& property : toolsComponent->GetToolsProperties())
        {
            if (property->GetEngineProperty()->GetType() != SerializableDataType::Vector2F)
            {
                continue;
            }

            if (auto toolsProperty = std::dynamic_pointer_cast<Vector2FSerializableProperty>(property))
            {
                drawBundle.TransformPosition = toolsProperty->GetValue();
            }
        }
    }
}

void ViewportEngine::ChangeDrawBundleBasedOnComponentChange(const std::shared_ptr<Guid>& gameObjectGuid, const std::shared_ptr<Guid>& componentGuid)
{
    const uint64_t gameObjectGuidAsNumber = gameObjectGuid->AsNumber();
    for (const std::shared_ptr<GameObject>& gameObject : m_currentScene->GetGameObjects())
    {
        if (gameObject->GetGuid() != gameObjectGuid)
        {
            continue;
        }

        for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
        {
            if (component->GetUniqueID() != componentGuid)
            {
                continue;
            }

            if (component->GetType() == "SpriteComponent")
            {
                UpdateSpriteBasedOnComponentChange(gameObjectGuidAsNumber, component);
            }
            else if (component->GetType() == "TransformComponent")
            {
                UpdateTransformBasedOnComponentChange(gameObjectGuidAsNumber, component);
            }
        }
    }

    ValidateDrawBundle(m_drawBundle.at(gameObjectGuid->AsNumber()));
}

void ViewportEngine::UpdateSpriteBasedOnComponentChange(const uint64_t gameObjectGuid, const std::shared_ptr<Component>& component)
{
    if (auto toolsComponent = std::dynamic_pointer_cast<ToolsComponent>(component))
    {
        for (const std::shared_ptr<ToolsSerializableProperty>& property : toolsComponent->GetToolsProperties())
        {
            if (property->GetEngineProperty()->GetType() != SerializableDataType::TextureAsset)
            {
                continue;
            }

            if (auto textureProperty = std::dynamic_pointer_cast<TextureAssetSerializableProperty>(property))
            {
                if (textureProperty->GetTextureValue().empty())
                {
                    return;
                }

                // We are an engine, ensure to use this version.
                m_drawBundle.at(gameObjectGuid).TextureAsset = m_crossEngineObjects->
                    GetEngineTextureManager()->GetTextureAsset(textureProperty->GetTextureValue());
            }
        }
    }
}

void ViewportEngine::UpdateTransformBasedOnComponentChange(const uint64_t gameObjectGuid, const std::shared_ptr<Component>& component)
{
    if (auto toolsComponent = std::dynamic_pointer_cast<ToolsComponent>(component))
    {
        for (const std::shared_ptr<ToolsSerializableProperty>& property : toolsComponent->GetToolsProperties())
        {
            if (property->GetEngineProperty()->GetType() != SerializableDataType::Vector2F)
            {
                continue;
            }

            if (auto toolsProperty = std::dynamic_pointer_cast<Vector2FSerializableProperty>(property))
            {
                m_drawBundle.at(gameObjectGuid).TransformPosition = toolsProperty->GetValue();
            }
        }
    }
}

void ViewportEngine::OnComponentAdded(
    const std::shared_ptr<Guid>& gameObjectGuid,
    const std::shared_ptr<Guid>& componentGuid)
{
    if (!m_drawBundle.contains(gameObjectGuid->AsNumber()))
    {
        m_drawBundle.insert_or_assign(gameObjectGuid->AsNumber(), ViewportObjectDrawBundle());
    }

    // Listen for changes.
    for (const std::shared_ptr<GameObject>& gameObject : m_currentScene->GetGameObjects())
    {
        if (gameObject->GetGuid() != gameObjectGuid)
        {
            continue;
        }

        for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
        {
            if (component->GetUniqueID() != componentGuid)
            {
                continue;
            }

            component->OnPropertyChanged()->Subscribe(shared_from_this());
        }
    }

    ChangeDrawBundleBasedOnComponentChange(gameObjectGuid, componentGuid);
}

void ViewportEngine::OnComponentRemoved(const std::shared_ptr<Component>& component)
{
    // Stop listening for changes.
    component->OnPropertyChanged()->Unsubscribe(shared_from_this());

    if (!component)
    {
        return;
    }

    ViewportObjectDrawBundle& drawBundle = m_drawBundle.at(component->GetObjectGuid()->AsNumber());
    RemoveComponentFromDrawBundleIfExists(drawBundle, component);
}

void ViewportEngine::RemoveComponentFromDrawBundleIfExists(
    ViewportObjectDrawBundle& drawBundle,
    const std::shared_ptr<Component>& component)
{
    if (component->GetType() == "SpriteComponent")
    {
        drawBundle.TextureAsset = nullptr;
    }
    else if (component->GetType() == "TransformComponent")
    {
        drawBundle.TransformPosition = {};
    }

    ValidateDrawBundle(drawBundle);
}

void ViewportEngine::ValidateDrawBundle(ViewportObjectDrawBundle& drawBundle) const
{
    if (drawBundle.TextureAsset)
    {
        drawBundle.IsValidToRender = true;
    }
    else
    {
        drawBundle.IsValidToRender = false;
    }
}

void ViewportEngine::OnGameObjectDeleted(const std::shared_ptr<GameObject>& gameObject)
{
    for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
    {
        component->OnPropertyChanged()->Unsubscribe(shared_from_this());
    }

    m_drawBundle.erase(gameObject->GetGuid()->AsNumber());
}
