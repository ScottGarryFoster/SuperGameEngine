#include "ViewportEngine.h"

#include "Engine/Content/ContentManager.h"
#include "Engine/CrossEngineObjects/CrossEngineObjects.h"
#include "Engine/Content/SuperTextureManager.h"
#include "Engine/CrossEngineObjects/OnSceneUpdatedEventArguments.h"
#include "GameEngineEquivalents/Component/Component.h"
#include "GameEngineEquivalents/Component/ComponentDataChangedEventArguments.h"
#include "GameEngineEquivalents/Component/ToolsComponent.h"
#include "GameEngineEquivalents/GameObject/GameObject.h"
#include "GameEngineEquivalents/Scene/Scene.h"
#include "GameEngineEquivalents/SerializableProperties/TextureAssetSerializableProperty.h"
#include "GameEngineEquivalents/SerializableProperties/ToolsSerializableProperty.h"
#include "GameEngineEquivalents/SerializableProperties/Vector2FSerializableProperty.h"
#include "Structural/Assets/Texture/TextureAsset.h"
#include "Structural/Serializable/SerializableProperty.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ViewportEngine::ViewportEngine()
{
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
    if (!m_crossEngineObjects->GetScene())
    {
        return ApplicationOperationState::Running;
    }

    return ApplicationOperationState::Running;
}

void ViewportEngine::Draw()
{
    for (const std::pair<const uint64_t, ViewportObjectDrawBundle>& drawBundle : m_drawBundle)
    {
        if (!drawBundle.second.TextureAsset)
        {
            return;
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
}

void ViewportEngine::EngineEnd()
{
    // If you stored the scene ensure you let it go here.
}

void ViewportEngine::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto onSceneArgs = std::dynamic_pointer_cast<OnSceneUpdatedEventArguments>(arguments))
    {
        m_drawBundle.clear();
        for (const std::shared_ptr<GameObject>& gameObject : m_crossEngineObjects->GetScene()->GetGameObjects())
        {
            auto drawBundle = ViewportObjectDrawBundle();
            for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
            {
                if (component->GetType() == "SpriteComponent")
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

                    component->OnPropertyChanged()->Subscribe(shared_from_this());
                }
                else if (component->GetType() == "TransformComponent")
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

                    component->OnPropertyChanged()->Subscribe(shared_from_this());
                }
                
            }

            if (drawBundle.TextureAsset)
            {
                Log::Info("GUID added: " + gameObject->GetGuid()->ToString());
                m_drawBundle.insert_or_assign(gameObject->GetGuid()->AsNumber(), drawBundle);
            }
            else
            {
                Log::Error("No texture defined in object. " + gameObject->GetGuid()->ToString());
            }
        }
    }
    else if (auto componentChangedArgs = std::dynamic_pointer_cast<ComponentDataChangedEventArguments>(arguments))
    {
        const uint64_t gameObjectGuid = componentChangedArgs->GetGameObjectGuid()->AsNumber();
        for (const std::shared_ptr<GameObject>& gameObject : m_crossEngineObjects->GetScene()->GetGameObjects())
        {
            if (gameObject->GetGuid() != componentChangedArgs->GetGameObjectGuid())
            {
                continue;
            }

            for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
            {
                if (component->GetUniqueID() != componentChangedArgs->GetComponentGuid())
                {
                    continue;
                }

                if (component->GetType() == "SpriteComponent")
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
                                m_drawBundle.at(gameObjectGuid).TextureAsset = m_crossEngineObjects->
                                    GetEngineTextureManager()->GetTextureAsset(textureProperty->GetTextureValue());
                            }
                        }
                    }
                }
                else if (component->GetType() == "TransformComponent")
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
            }
        }
    }

}

void ViewportEngine::GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects)
{
    m_crossEngineObjects = crossEngineObjects;
    m_crossEngineObjects->OnNewScene()->Subscribe(shared_from_this());
}
