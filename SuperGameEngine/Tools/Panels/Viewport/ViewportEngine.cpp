#include "ViewportEngine.h"

#include <ranges>

#include "ViewportEngineAndPanelCommunication.h"
#include "../../../Input/InputManagement/SDLInputManager.h"
#include "Engine/Content/ContentManager.h"
#include "Engine/CrossEngineObjects/CrossEngineObjects.h"
#include "Engine/Content/SuperTextureManager.h"
#include "Engine/CrossEngineObjects/OnSceneUpdatedEventArguments.h"
#include "Engine/CrossEngineObjects/SharedSceneChangedEvents.h"
#include "Engine/Graphics/Geometry/PrimitiveRectangle.h"
#include "Engine/Graphics/Geometry/SuperPrimitiveShapeProvider.h"
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
#include "ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/SelectionChangedEventArguments.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

ViewportEngine::ViewportEngine()
{
    m_currentScene = nullptr;
    m_mouseCollision = RectangleInt();
    m_previousSelectionKeyDownStatus = false;
    m_selectionButtonStatusIsDirty = false;
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
    // This must always be called first to ensure dirty flags flip.
    UpdateSelectionButtonDirtyFlag();

    ProcessDrawBundleInteractions();
    return ApplicationOperationState::Running;
}

void ViewportEngine::Draw()
{
    // Mouse Rectangle
    m_debugRectangle->DrawInPlace(
        m_mouseCollision.GetLeft(),
        m_mouseCollision.GetTop(),
        m_mouseCollision.GetWidth(),
        m_mouseCollision.GetHeight());


    for (const std::pair<const uint64_t, ViewportObjectDrawBundle>& drawBundle : m_drawBundle)
    {
        const bool mouseOver = EDrawBundleSelectionState::HasFlag(drawBundle.second.SelectionState, DrawBundleSelectionState::Hover);
        const bool leftClick = EDrawBundleSelectionState::HasFlag(drawBundle.second.SelectionState, DrawBundleSelectionState::SelectionKeyDown);
        const bool selected = EDrawBundleSelectionState::HasFlag(drawBundle.second.SelectionState, DrawBundleSelectionState::Selected);
        if (selected)
        {
            m_debugRectangle->DrawInPlace(
                drawBundle.second.FaceRectangle.GetLeft(),
                drawBundle.second.FaceRectangle.GetTop(),
                drawBundle.second.FaceRectangle.GetWidth(),
                drawBundle.second.FaceRectangle.GetHeight(),
                DebugColourName::Red);
        }
        else if (!mouseOver)
        {
            m_debugRectangle->DrawInPlace(
                drawBundle.second.FaceRectangle.GetLeft(),
                drawBundle.second.FaceRectangle.GetTop(),
                drawBundle.second.FaceRectangle.GetWidth(),
                drawBundle.second.FaceRectangle.GetHeight(),
                DebugColourName::Default);
        }
        else if (leftClick)
        {
            m_debugRectangle->DrawInPlace(
                drawBundle.second.FaceRectangle.GetLeft(),
                drawBundle.second.FaceRectangle.GetTop(),
                drawBundle.second.FaceRectangle.GetWidth(),
                drawBundle.second.FaceRectangle.GetHeight(),
                DebugColourName::Blue);
        }
        if (mouseOver)
        {
            m_debugRectangle->DrawInPlace(
                drawBundle.second.FaceRectangle.GetLeft(),
                drawBundle.second.FaceRectangle.GetTop(),
                drawBundle.second.FaceRectangle.GetWidth(),
                drawBundle.second.FaceRectangle.GetHeight(),
                DebugColourName::Cyan);
        }

        DrawBundle(drawBundle.second);
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

    if (!m_renderer)
    {
        Log::Error("No renderer was given to the viewport engine.",
            "void ViewportEngine::EngineStart()");
        return;
    }

    m_primitiveShapeProvider = std::make_shared<SuperPrimitiveShapeProvider>(m_renderer);
    m_debugRectangle = m_primitiveShapeProvider->CreateRectangle(FVector2F(), FVector2F(50, 50));

    m_crossEngineObjects->GetWindowPackage()->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged(SelectionGroup::Inspectable)->Subscribe(shared_from_this());
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
    else if (auto selectionChanged = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        OnSelectionChanged(selectionChanged);
    }
}

void ViewportEngine::GiveCrossEngineObjects(const std::shared_ptr<CrossEngineObjects>& crossEngineObjects)
{
    m_crossEngineObjects = crossEngineObjects;
    m_crossEngineObjects->OnNewScene()->Subscribe(shared_from_this());
}

void ViewportEngine::GiveViewportEngineAndPanelCommunication(
    const std::shared_ptr<ViewportEngineAndPanelCommunication>& engineAndPanelCommunication)
{
    m_viewportEngineAndPanelCommunication = engineAndPanelCommunication;
}

void ViewportEngine::DrawBundle(const ViewportObjectDrawBundle& drawBundle, const FPoint& mousePosition)
{
    DrawBundle(drawBundle);

    bool draw = true;
    if (drawBundle.FaceRectangle.Contains(mousePosition))
    {
        draw = false;
    }

    if (draw)
    {

        m_debugRectangle->DrawInPlace(
            drawBundle.FaceRectangle.GetLeft(),
            drawBundle.FaceRectangle.GetTop(),
            drawBundle.FaceRectangle.GetWidth(),
            drawBundle.FaceRectangle.GetHeight());
    }
}

void ViewportEngine::DrawBundle(const ViewportObjectDrawBundle& drawBundle)
{
    if (!drawBundle.IsValidToRender)
    {
        return;
    }

    drawBundle.TextureAsset->Draw(0, drawBundle.TransformPosition);
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
    auto drawBundle = CreateDrawBundle(gameObject);
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
                UpdateCollisionRectangle(drawBundle);
                return;
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
                UpdateCollisionRectangle(drawBundle);
                return;
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
                UpdateCollisionRectangle(m_drawBundle.at(gameObjectGuid));
                return;
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
                UpdateCollisionRectangle(m_drawBundle.at(gameObjectGuid));
                return;
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
        m_drawBundle.insert_or_assign(gameObjectGuid->AsNumber(), CreateDrawBundle(gameObjectGuid));
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
        UpdateCollisionRectangle(drawBundle);
    }
    else if (component->GetType() == "TransformComponent")
    {
        drawBundle.TransformPosition = {};
        UpdateCollisionRectangle(drawBundle);
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

void ViewportEngine::UpdateCollisionRectangle(ViewportObjectDrawBundle& drawBundle) const
{
    auto size = FVector2I(32, 32);
    if (drawBundle.TextureAsset)
    {
        size = drawBundle.TextureAsset->SizeOfSingleTile();
    }

    drawBundle.FaceRectangle.SetSize(size.GetX(), size.GetY());
    drawBundle.FaceRectangle.SetLocation(
        (float)drawBundle.TransformPosition.GetX(),
        (float)drawBundle.TransformPosition.GetY());
}

ViewportObjectDrawBundle ViewportEngine::CreateDrawBundle(const std::shared_ptr<GameObject>& gameObject) const
{
    return CreateDrawBundle(gameObject->GetGuid());
}

ViewportObjectDrawBundle ViewportEngine::CreateDrawBundle(const std::shared_ptr<Guid>& gameObjectGuid) const
{
    auto drawBundle = ViewportObjectDrawBundle();
    drawBundle.Guid = gameObjectGuid->ToString();
    drawBundle.SelectionState = DrawBundleSelectionState::NoInteraction;
    return drawBundle;
}

void ViewportEngine::ProcessDrawBundleInteractions()
{
    std::pair<bool, SuperGameEngine::RectangleInt> mousePosition = GetMousePosition();
    bool mousePositionIsValid = mousePosition.first;
    m_mouseCollision = mousePosition.second;
    if (!mousePositionIsValid)
    {
        return;
    }

    bool leftClick = false;
    if (m_selectionButtonStatusIsDirty)
    {
        leftClick = IsSelectionButtonDown();
    }

    auto updateStateAdd = [](ViewportObjectDrawBundle& drawBundle, DrawBundleSelectionState newState)
        {
            if (drawBundle.SelectionState == DrawBundleSelectionState::NoInteraction)
            {
                drawBundle.SelectionState = newState;
            }
            else
            {
                drawBundle.SelectionState |= newState;
            }
        };

    auto updateStateRemove = [](ViewportObjectDrawBundle& drawBundle, DrawBundleSelectionState newState)
        {
            if (EDrawBundleSelectionState::HasFlag(drawBundle.SelectionState, newState))
            {
                drawBundle.SelectionState &= ~newState;
            }
        };

    for (ViewportObjectDrawBundle& drawBundle : m_drawBundle | std::views::values)
    {
        const bool mouseOver = drawBundle.FaceRectangle.Contains(mousePosition.second);
        if (mouseOver)
        {
            updateStateAdd(drawBundle, DrawBundleSelectionState::Hover);
        }
        else
        {
            updateStateRemove(drawBundle, DrawBundleSelectionState::Hover);
        }

        // This ensures we only ever run this code once a frame if we need to.
        // The state updating is not a big load on the viewport but selection will be.
        if (m_selectionButtonStatusIsDirty)
        {
            if (leftClick)
            {
                updateStateAdd(drawBundle, DrawBundleSelectionState::SelectionKeyDown);
            }
            else
            {
                updateStateRemove(drawBundle, DrawBundleSelectionState::SelectionKeyDown);
            }

            if (mouseOver && leftClick)
            {
                if (!EDrawBundleSelectionState::HasFlag(drawBundle.SelectionState, DrawBundleSelectionState::Selected))
                {
                    m_currentScene->SelectGameObject(drawBundle.Guid);
                }
            }
        }
    }

}

void ViewportEngine::OnSelectionChanged(const std::shared_ptr<SelectionChangedEventArguments>& arguments)
{
    const SelectionChangeType selectionType = arguments->GetSelectionChangeType();
    if (selectionType == SelectionChangeType::Set)
    {
        for (ViewportObjectDrawBundle& drawBundle : m_drawBundle | std::views::values)
        {
            if (EDrawBundleSelectionState::HasFlag(drawBundle.SelectionState, DrawBundleSelectionState::Selected))
            {
                drawBundle.SelectionState &= ~DrawBundleSelectionState::Selected;
            }
        }
    }

    for (const std::shared_ptr<const Guid>& guid : arguments->GetAllSelectableGuids())
    {
        if (m_drawBundle.contains(guid->AsNumber()))
        {
            ViewportObjectDrawBundle& drawBundle = m_drawBundle.at(guid->AsNumber());
            if (!EDrawBundleSelectionState::HasFlag(drawBundle.SelectionState, DrawBundleSelectionState::Selected))
            {
                if (selectionType == SelectionChangeType::Set || selectionType == SelectionChangeType::Add)
                {
                    drawBundle.SelectionState |= DrawBundleSelectionState::Selected;
                }
            }
            else if(selectionType == SelectionChangeType::Remove)
            {
                // Have selected state and we are removing from the selection.
                drawBundle.SelectionState &= ~DrawBundleSelectionState::Selected;
            }

        }
    }
}

void ViewportEngine::UpdateSelectionButtonDirtyFlag()
{
    bool currentSelectionButton = IsSelectionButtonDown();
    m_selectionButtonStatusIsDirty = currentSelectionButton != m_previousSelectionKeyDownStatus;

    m_previousSelectionKeyDownStatus = currentSelectionButton;
}

bool ViewportEngine::IsSelectionButtonDown() const
{
    const SuperGameInput::MouseState mouseState = m_inputManager->GetMouseState();
    return mouseState.ButtonState.at(SuperGameInput::MouseButton::Left) == SuperGameInput::KeyOrButtonState::Down &&
        mouseState.ButtonState.at(SuperGameInput::MouseButton::Right) == SuperGameInput::KeyOrButtonState::Unpressed &&
        mouseState.ButtonState.at(SuperGameInput::MouseButton::Middle) == SuperGameInput::KeyOrButtonState::Unpressed &&
        mouseState.ButtonState.at(SuperGameInput::MouseButton::Back) == SuperGameInput::KeyOrButtonState::Unpressed &&
        mouseState.ButtonState.at(SuperGameInput::MouseButton::Forward) == SuperGameInput::KeyOrButtonState::Unpressed;
}

std::pair<bool, SuperGameEngine::RectangleInt> ViewportEngine::GetMousePosition() const
{
    const FPoint mousePosition = m_inputManager->GetMousePosition();
    RectangleInt viewport = m_viewportEngineAndPanelCommunication->GetViewportLocation();
    bool mousePositionIsValid = viewport.Contains(mousePosition);

    // Adjust the mouse position from window space to viewport space.
    const FPoint adjustedPosition = FPoint(mousePosition.GetX() - viewport.GetLeft(), mousePosition.GetY() - viewport.GetTop());

    return
    {
        mousePositionIsValid,
        RectangleInt(adjustedPosition.GetX(), adjustedPosition.GetY(), 1, 1)
       };
}
