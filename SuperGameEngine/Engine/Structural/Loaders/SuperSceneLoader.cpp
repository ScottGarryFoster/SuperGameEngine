#include "SuperSceneLoader.h"
#include "../../FatedQuestReferences.h"
#include "../../Structural/Scene/SuperScene.h"
#include "../GameObject/SuperGameObject.h"
#include "../Component/SuperGameComponent.h"

using namespace SuperGameEngine;
using namespace FatedQuestLibraries;

SuperSceneLoader::SuperSceneLoader(const std::shared_ptr<SceneLoadPackage>& sceneLoadPackage)
{
    m_sceneLoadPackage = sceneLoadPackage;
}

std::shared_ptr<Scene> SuperSceneLoader::Create(
    const std::shared_ptr<StoredDocument>& storedDocument)
{
    if (!storedDocument)
    {
        Log::Error("Presented with an document to load. Could not create scene.",
            "SuperSceneLoader::Create(std::shared_ptr<StoredDocument>)");
        return {};
    }

    std::shared_ptr<SuperScene> returnScene;
    if (auto rootNode = storedDocument->GetRoot())
    {
        if (rootNode->Name() == "Scene")
        {
            returnScene = std::make_shared<SuperScene>();
            returnScene->Setup(m_sceneLoadPackage);
            CreateSceneLevelAttributesAndNodes(rootNode, returnScene);
        }
    }

    return returnScene;
}

std::shared_ptr<StoredDocument> SuperSceneLoader::Save(const std::shared_ptr<Scene>& scene)
{
    if (!scene)
    {
        Log::Error("Presented with an empty scene to save. Could not save scene.",
            "SuperSceneLoader::Save(std::shared_ptr<Scene>)");
        return {};
    }

    auto root = std::make_shared<ModifiableNode>();
    root->SetName("Scene");
    SaveSceneLevelAttributesAndNodes(root, scene);

    auto document = std::make_shared<ModifiableDocument>();
    document->SetRootElement(root);

    return document;
}

void SuperSceneLoader::CreateSceneLevelAttributesAndNodes(
    const std::shared_ptr<StoredDocumentNode>& sceneNode, 
    const std::shared_ptr<SuperScene>& scene) const
{
    if (auto guid = sceneNode->Attribute("Guid", false))
    {
        if (std::shared_ptr<Guid> parsed = GUIDHelpers::CreateFromString(guid->Value()))
        {
            scene->SetGuid(parsed);
        }
    }

    for (std::shared_ptr<StoredDocumentNode> child = sceneNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() != "GameObject")
        {
            continue;
        }

        std::shared_ptr<GameObject> go = scene->CreateAndAddNewGameObject();
        if (std::shared_ptr<SuperGameObject> sgo = std::static_pointer_cast<SuperGameObject>(go))
        {
            CreateGameObjectAttributesAndNodes(child, sgo);
        }
    }
}

void SuperSceneLoader::CreateGameObjectAttributesAndNodes(
    const std::shared_ptr<StoredDocumentNode>& gameObjectNode,
    const std::shared_ptr<SuperGameObject>& superGameObject) const
{
    if (auto guid = gameObjectNode->Attribute("Guid", false))
    {
        if (std::shared_ptr<Guid> parsed = GUIDHelpers::CreateFromString(guid->Value()))
        {
            superGameObject->SetGuid(parsed);
        }
    }

    for (std::shared_ptr<StoredDocumentNode> child = gameObjectNode->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        if (child->Name() != "Component")
        {
            continue;
        }

        std::string componentType = {};
        if (auto typeAttribute = child->Attribute("Type", false))
        {
            componentType = typeAttribute->Value();
        }

        // If there is no type on component skip.
        if (componentType.empty())
        {
            continue;
        }

        std::shared_ptr<GameComponent> component = superGameObject->AddComponent(componentType);
        if (std::shared_ptr<SuperGameComponent> sgc = std::static_pointer_cast<SuperGameComponent>(component))
        {
            CreateGameComponentAttributesAndNodes(child, sgc);
        }
    }
}

void SuperSceneLoader::CreateGameComponentAttributesAndNodes(const std::shared_ptr<StoredDocumentNode>& componentNode,
    const std::shared_ptr<SuperGameComponent>& superGameComponent) const
{

}

void SuperSceneLoader::SaveSceneLevelAttributesAndNodes(
    const std::shared_ptr<ModifiableNode>& sceneNode,
    const std::shared_ptr<Scene>& scene) const
{
    auto sceneAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    if (std::shared_ptr<Guid> guid = scene->GetGuid())
    {
        std::string guidString = GUIDHelpers::ToString(*guid);
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Guid", guidString);
        sceneAttributes.emplace_back(attribute);
    }

    sceneNode->SetAttributes(sceneAttributes);

    std::vector<std::shared_ptr<StoredDocumentNode>> allNodes;

    bool haveAdjacent = false;
    std::shared_ptr<ModifiableNode> current;
    for (const std::shared_ptr<GameObject>& go : scene->GetChildren())
    {
        auto node = std::make_shared<ModifiableNode>();
        node->SetName("GameObject");
        SaveGameObjectAttributesAndNodes(node, go);

        if (haveAdjacent)
        {
            current->SetAdjacentNode(node);
        }

        current = node;
        allNodes.emplace_back(current);
        haveAdjacent = true;
    }

    if (!allNodes.empty())
    {
        sceneNode->SetFirstChild(allNodes.front());
        if (allNodes.size() > 1)
        {
            sceneNode->SetLastChild(allNodes.back());
        }
    }

}

void SuperSceneLoader::SaveGameObjectAttributesAndNodes(
    const std::shared_ptr<ModifiableNode>& gameObjectNode,
    const std::shared_ptr<GameObject>& gameObject) const
{
    auto sceneAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    if (std::shared_ptr<Guid> guid = gameObject->GetGuid())
    {
        std::string guidString = GUIDHelpers::ToString(*guid);
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Guid", guidString);
        sceneAttributes.emplace_back(attribute);
    }

    gameObjectNode->SetAttributes(sceneAttributes);

    std::vector<std::shared_ptr<StoredDocumentNode>> allNodes;
    std::shared_ptr<ModifiableNode> current;
    bool haveAdjacent = false;
    for (const std::shared_ptr<GameComponent>& component : gameObject->GetAllComponents())
    {
        auto node = std::make_shared<ModifiableNode>();
        node->SetName("Component");
        SaveGameComponentAttributesAndNodes(node, component);

        if (haveAdjacent)
        {
            current->SetAdjacentNode(node);
        }

        current = node;
        allNodes.emplace_back(current);
        haveAdjacent = true;
    }

    if (!allNodes.empty())
    {
        gameObjectNode->SetFirstChild(allNodes.front());
        if (allNodes.size() > 1)
        {
            gameObjectNode->SetLastChild(allNodes.back());
        }
    }
}

void SuperSceneLoader::SaveGameComponentAttributesAndNodes(const std::shared_ptr<ModifiableNode>& componentNode,
    const std::shared_ptr<GameComponent>& component) const
{
    auto componentAttributes = std::vector<std::shared_ptr<StoredDocumentAttribute>>();
    {
        auto attribute = std::make_shared<ModifiableAttribute>
            ("Type", component->TypeName());
        componentAttributes.emplace_back(attribute);
    }

    componentNode->SetAttributes(componentAttributes);
}
