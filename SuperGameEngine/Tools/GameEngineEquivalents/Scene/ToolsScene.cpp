#include "ToolsScene.h"

#include "../../ToolsEngine/Documents/Scene/SceneDocument.h"
#include "../GameObject/ToolsGameObject.h"
#include "../../FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

ToolsScene::ToolsScene(
    const std::shared_ptr<SerializableParser>& parser,
    const std::shared_ptr<SceneDocument>& document)
{
    m_parser = parser;
    m_sceneDocument = document;
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
    return m_sceneDocument->Save();
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
        m_gameObjects.emplace_back(gameObject);
    }

    return true;
}

std::vector<std::shared_ptr<GameObject>> ToolsScene::GetGameObjects() const
{
    return m_gameObjects;
}
