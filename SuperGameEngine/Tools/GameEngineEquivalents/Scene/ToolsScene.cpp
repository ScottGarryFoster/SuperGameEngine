#include "ToolsScene.h"

#include "../../ToolsEngine/Documents/Scene/SceneDocument.h"
#include "../GameObject/ToolsGameObject.h"
#include "../../FatedQuestLibraries.h"
#include "../../ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"
#include "../Component/Component.h"
#include "ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsScene::ToolsScene(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<SceneDocument>& document,
    const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_parser = parser;
    m_sceneDocument = document;
    m_windowPackage = windowPackage;
    m_dirtyFlag = std::make_shared<bool>();
    *m_dirtyFlag = false;
    m_onDirtyFlagChanged = std::make_shared<FEvent>();
}

std::shared_ptr<FEventSubscriptions> ToolsScene::OnDirtyFlagChanged() const
{
    return m_onDirtyFlagChanged;
}

bool ToolsScene::Save() const
{
    auto root = std::make_shared<ModifiableNode>();
    root->SetName("Scene");

    if (m_guid)
    {
        auto guid = std::make_shared<ModifiableAttribute>("Guid", m_guid->ToString());
        std::vector<std::shared_ptr<StoredDocumentAttribute>> attributes;
        attributes.emplace_back(guid);
        root->SetAttributes(attributes);
    }

    std::vector<std::shared_ptr<ModifiableNode>> children;
    for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
    {
        children.emplace_back(gameObject->Save());
    }
    root->SetAllChildrenNodes(children);

    m_sceneDocument->GetDocument()->SetRootElement(root);
    bool couldSave = m_sceneDocument->Save();
    UpdateDirtyFlag(!couldSave);
    return couldSave;
}

bool ToolsScene::Load()
{
    if (!m_sceneDocument)
    {
        Log::Error("Cannot load when there is no document.",
            "ToolsScene::Load()");
        return false;
    }

    if (!m_sceneDocument->GetDocument())
    {
        Log::Error("Cannot load when there is no document.",
            "ToolsScene::Load()");
        return false;
    }

    if (!m_sceneDocument->GetDocument()->GetModifiableRoot())
    {
        Log::Error("Cannot load when there is no data in the document.",
            "ToolsScene::Load()");
        return false;
    }

    // Get rid of old information if any

    // Ensure we unsubscribe from old events.
    for (const std::shared_ptr<GameObject>& gameObject : m_gameObjects)
    {
        gameObject->OnDirtyFlagChanged()->Unsubscribe(shared_from_this());
    }
    m_gameObjects.clear();
    m_guid = {};

    std::shared_ptr<ModifiableNode> root = m_sceneDocument->GetDocument()->GetModifiableRoot();
    if (auto guid = root->Attribute("Guid", CaseSensitivity::IgnoreCase))
    {
        if (auto guidObject = GUIDHelpers::CreateFromString(guid->Value()))
        {
            m_guid = guidObject;
        }
    }

    for (std::shared_ptr<StoredDocumentNode> child = root->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        // Create the game object
        auto gameObject = std::make_shared<ToolsGameObject>(m_parser);
        gameObject->Load(child);

        // Listen to dirtied events.
        gameObject->OnDirtyFlagChanged()->Subscribe(shared_from_this());

        m_gameObjects.emplace_back(gameObject);
    }

    UpdateDirtyFlag(false);
    return true;
}

std::vector<std::shared_ptr<GameObject>> ToolsScene::GetGameObjects() const
{
    return m_gameObjects;
}

bool ToolsScene::GetDirty() const
{
    return *m_dirtyFlag;
}

void ToolsScene::MarkDirty()
{
    UpdateDirtyFlag(true);
}

void ToolsScene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
{
    m_gameObjects.emplace_back(gameObject);
}

void ToolsScene::RemoveGameObject(const std::shared_ptr<GameObject>& gameObject)
{
    std::erase_if(m_gameObjects, [gameObject](const std::shared_ptr<GameObject>& current)
        {
            return gameObject->GetGuid()->ToString() == current->GetGuid()->ToString();
        });
}

void ToolsScene::RemoveComponentFromGameObject(
    const std::shared_ptr<GameObject>& gameObject,
    const std::shared_ptr<Component>& component)
{
    bool didRemove = false;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (gameObject->GetGuid()->ToString() == go->GetGuid()->ToString())
        {
            gameObject->RemoveComponent(component);
            didRemove = true;
        }
    }

    if (didRemove)
    {
        UpdateDirtyFlag(true);
    }
}

void ToolsScene::Invoke(const std::shared_ptr<FEventArguments>& arguments)
{
    if (auto dirtyArgs = std::dynamic_pointer_cast<DirtiedDataEventArguments>(arguments))
    {
        // Only respond if the children now have data to save
        // as if clean, this does not mean everything is clean,
        // only that something was saved.
        if (dirtyArgs->GetDirtyFlagState())
        {
            UpdateDirtyFlag(dirtyArgs->GetDirtyFlagState());
        }
    }
}

bool ToolsScene::SelectGameObject(const FatedQuestLibraries::Guid& guid)
{
    const std::string compare = guid.ToString();
    bool didFind = false;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->GetGuid()->ToString() == compare)
        {
            m_windowPackage->GetFrameworkManager()->GetSelectionManager()->SetSelection(go);
            didFind = true;
            break;
        }
    }

    return didFind;
}

bool ToolsScene::SelectGameObject(const std::string& guid)
{
    bool didFind = false;
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->GetGuid()->ToString() == guid)
        {
            m_windowPackage->GetFrameworkManager()->GetSelectionManager()->SetSelection(go);
            didFind = true;
            break;
        }
    }

    return didFind;
}

std::shared_ptr<GameObject> ToolsScene::GetGameObjectByGuid(const std::string& guid) const
{
    for (const std::shared_ptr<GameObject>& go : m_gameObjects)
    {
        if (go->GetGuid()->ToString() == guid)
        {
            return go;
        }
    }

    return {};
}

void ToolsScene::UpdateDirtyFlag(bool newValue) const
{
    if (newValue != *m_dirtyFlag)
    {
        *m_dirtyFlag = newValue;
        m_onDirtyFlagChanged->Invoke(std::make_shared<DirtiedDataEventArguments>(newValue));
    }
}
