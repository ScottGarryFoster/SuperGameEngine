#include "SceneHierarchy.h"


#include "ToolsSceneLoader.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Content/ContentManager.h"
#include "../../GameEngineEquivalents/Component/ToolsComponent.h"
#include "../../GameEngineEquivalents/GameObject/ToolsGameObject.h"
#include "../../ToolsEngine/Documents/Scene/SceneDocument.h"
#include "../../ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "../../ToolsEngine/FrameworkManager/DocumentManager/DocumentManager.h"
#include "../../ToolsEngine/FrameworkManager/DocumentManager/DocumentEvent/DocumentActionEventArguments.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/ColoursAndStyles/ColoursAndStyles.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemView.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemViewEventArguments.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuView.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeView.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItemOnSelectedEventArguments.h"
#include "../SceneHeirachy/GameObjectTreeViewItem.h"
#include "../../GameEngineEquivalents/Scene/ToolsScene.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionChangedEventArguments.h"
#include "../SceneHeirachy/SceneTreeViewItem.h"
#include "EventArguments/OnMenuNewGameObjectEventArguments.h"


using namespace SuperGameTools;

SceneHierarchy::SceneHierarchy() : WindowElement()
{
    m_testPopup = false;
    m_testPopupText = {};
}

void SceneHierarchy::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    WindowElement::Setup(m_windowPackage->GetColourPalette());

    const std::string method = "SceneHierarchy::Setup(std::shared_ptr<WindowPackage>)";
    if (!m_windowPackage->GetFrameworkManager())
    {
        Log::Error("No framework manager. Cannot load scenes.", method);
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetDocumentManager())
    {
        Log::Error("No document manager. Cannot load scenes.", method);
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetDocumentManager()->OnDocumentAction())
    {
        Log::Error("No document action event. Cannot load scenes.", method);
        return;
    }

    m_windowPackage->GetFrameworkManager()->GetDocumentManager()->OnDocumentAction()->Subscribe(shared_from_this());

    // TODO: Automatically load a scene when you open tools from a preferences file #113

    if (!m_windowPackage->GetFrameworkManager()->GetSelectionManager())
    {
        Log::Error("No selection manager. Cannot load scenes.", method);
        return;
    }

    m_windowPackage->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged()->Subscribe(shared_from_this());
}

void SceneHierarchy::Update()
{
    if (m_tree)
    {
        m_tree->Update();
    }

}

void SceneHierarchy::Draw()
{
    const char* windowName = "Scene Hierarchy";
    if (RenderWindow(windowName))
    {
        if (m_tree)
        {
            m_tree->Draw();
        }

        DrawWindowWideContextClickMenu();
    }
    EndWindowRender(windowName);
        

    // Test popup
    if (m_testPopup)
    {
        ImGui::OpenPopup("Selectable Popup");
    }

    if (ImGui::BeginPopupModal("Selectable Popup", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(m_testPopupText.c_str());
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
            m_testPopup = false;
        }
        ImGui::EndPopup();
    }

}

void SceneHierarchy::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto treeViewItemArgs = std::dynamic_pointer_cast<TreeViewItemOnSelectedEventArguments>(arguments))
    {
        OnTreeViewItemOnSelectedEvent(treeViewItemArgs);
    }
    else if (auto documentAction = std::dynamic_pointer_cast<DocumentActionEventArguments>(arguments))
    {
        OnDocumentActionEvent(documentAction);
    }
    else if (auto selectionArgs = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        OnSelectionChangedEvent(selectionArgs);
    }
    else if (auto onMenuNewGameObject = std::dynamic_pointer_cast<OnMenuNewGameObjectEventArguments>(arguments))
    {
        CreateNewGameObject();
    }
}

bool SceneHierarchy::LoadScene(const std::shared_ptr<SceneDocument>& document)
{
    if (!document)
    {
        Log::Error("No document given.",
            "bool SceneHierarchy::LoadScene(std::shared_ptr<SceneDocument>)");
        return false;
    }

    // A scene is already loaded try to re-select the same object in the scene.
    std::shared_ptr<Guid> reselectGameObject = {};
    if (m_scene)
    {
        std::vector<std::weak_ptr<Selectable>> selectables = m_windowPackage->GetFrameworkManager()->
            GetSelectionManager()->GetSelection(SelectionGroup::Inspectable);
        if (selectables.size() == 1)
        {
            if (auto selectableShared = selectables.at(0).lock())
            {
                if (auto gameObject = std::dynamic_pointer_cast<GameObject>(selectableShared))
                {
                    reselectGameObject = selectableShared->GetGuid();
                }
            }
        }
    }

    m_scene = std::make_shared<ToolsScene>(m_windowPackage->GetParser(), document);
    if (!m_scene->Load())
    {
        Log::Error("No document loaded into the scene document.",
            "bool SceneHierarchy::LoadScene(std::shared_ptr<SceneDocument>)");
        return false;
    }

    // It is important to store the shared pointer as a TreeViewItem so Shared from works.
    m_treeViewItem = std::make_shared<SceneTreeViewItem>(m_windowPackage->GetContentManager());
    m_treeViewItem->UpdateDistributedWeakPointer(m_treeViewItem);
    m_sceneTreeViewItem = std::static_pointer_cast<SceneTreeViewItem>(m_treeViewItem);
    m_sceneTreeViewItem->FEventObserver::UpdateDistributedWeakPointer(std::static_pointer_cast<FEventObserver>(m_sceneTreeViewItem));

    m_treeViewItem->GetLabel()->SetValue("Scene");
    m_treeViewItem->GetOpenOnLoad()->SetValue(true);
    m_treeViewItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
    m_treeViewItem->GetIsFramed()->SetValue(true);

    m_sceneTreeViewItem->SetScene(m_scene);

    // Subscribe to OnSelected.
    std::weak_ptr<FEventObserver> weak = shared_from_this();
    m_treeViewItem->OnSelected()->Subscribe(weak);

    auto children = std::vector<std::shared_ptr<TreeViewItem>>();
    auto childrenAsGameObjectTVI = std::vector<std::shared_ptr<GameObjectTreeViewItem>>();
    for (const std::shared_ptr<GameObject>& gameObject : m_scene->GetGameObjects())
    {
        auto childItem = std::make_shared<GameObjectTreeViewItem>(m_windowPackage->GetContentManager());
        childItem->UpdateDistributedWeakPointer(childItem);
        childItem->GetLabel()->SetValue("Game Object");
        childItem->GetIsFramed()->SetValue(false);
        childItem->SetGameObject(gameObject);
        childItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
        childItem->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::NoIcon);

        // Subscribe to OnSelected.
        std::weak_ptr<FEventObserver> weak = shared_from_this();
        childItem->OnSelected()->Subscribe(weak);
        childItem->OnMenuNewGameObject()->Subscribe(weak);

        children.emplace_back(childItem);
        childrenAsGameObjectTVI.emplace_back(childItem);
    }
    m_treeViewItem->GetChildren()->SetValue(children);
    m_sceneTreeViewItem->GetChildrenAsGameObjects()->SetValue(childrenAsGameObjectTVI);

    m_tree = std::make_shared<TreeView>(m_windowPackage->GetContentManager(), m_treeViewItem);
    m_tree->ShouldRootBeFrame(true);
    m_tree->SetDepthToStartIndentation(1);

    if (reselectGameObject)
    {
        for (const std::shared_ptr<GameObject>& gameObject : m_scene->GetGameObjects())
        {
            if (*gameObject->GetGuid() == *reselectGameObject)
            {
                m_windowPackage->GetFrameworkManager()->GetSelectionManager()->SetSelection(gameObject);
            }
        }
    }

    return true;
}

void SceneHierarchy::RemoveSelectionFromAllBut(const std::shared_ptr<TreeViewItem>& treeViewItem, const std::shared_ptr<TreeViewItem>& root)
{
    if (root->GetUniqueID() != treeViewItem->GetUniqueID())
    {
        root->GetIsSelected()->SetValue(false);
    }

    for (const std::shared_ptr<TreeViewItem>& child : root->GetChildren()->GetValue())
    {
        RemoveSelectionFromAllBut(treeViewItem, child);
    }
}

void SceneHierarchy::SaveAllScenes()
{
    if (m_scene)
    {
        if (!m_scene->Save())
        {
            Log::Error("Asked to save scene but could not.",
                "SceneHierarchy::SaveAllScenes()");
            return;
        }

        m_testPopup = true;
        m_testPopupText = "Saved";
    }
}

void SceneHierarchy::OnTreeViewItemOnSelectedEvent(
    const std::shared_ptr<TreeViewItemOnSelectedEventArguments>& arguments)
{
    if (auto treeviewItem = arguments->GetTreeViewItem().lock())
    {
        if (auto gameObjectTreeView = std::dynamic_pointer_cast<GameObjectTreeViewItem>(treeviewItem))
        {
            if (gameObjectTreeView->GetGameObject())
            {
                m_windowPackage->GetFrameworkManager()->GetSelectionManager()->SetSelection(gameObjectTreeView->GetGameObject());
            }
        }

        RemoveSelectionFromAllBut(treeviewItem, m_treeViewItem);
        if (*m_sceneTreeViewItem->GetUniqueID() == *treeviewItem->GetUniqueID())
        {
            m_sceneTreeViewItem->GetIsSelected()->SetValue(true);
        }
        else
        {
            m_sceneTreeViewItem->GetIsSelected()->SetValue(false);
        }
    }
}

void SceneHierarchy::OnDocumentActionEvent(const std::shared_ptr<DocumentActionEventArguments>& arguments)
{
    if (arguments->GetAction() == DocumentEventAction::Open)
    {
        if (arguments->GetDocument())
        {
            if (auto sceneDocument = std::dynamic_pointer_cast<SceneDocument>(arguments->GetDocument()))
            {
                if (LoadScene(sceneDocument))
                {
                    m_testPopup = true;
                    m_testPopupText = "Loaded";
                }
            }
            else
            {
                m_testPopup = true;
                m_testPopupText = "Not a scene document.";
            }
        }
        else
        {
            m_testPopup = true;
            m_testPopupText = "Empty document.";
        }
    }
    else if (arguments->GetAction() == DocumentEventAction::Save)
    {
        if (arguments->GetSaveContext() != DocumentEventSaveContext::Everything)
        {
            return;
        }

        SaveAllScenes();
    }
    else if (arguments->GetAction() == DocumentEventAction::Create)
    {
        std::shared_ptr<Document> document = arguments->GetDocument();
        if (auto sceneDocument = std::dynamic_pointer_cast<SceneDocument>(document))
        {
            UnselectAll();
            LoadScene(sceneDocument);
        }
    }
}

void SceneHierarchy::OnSelectionChangedEvent(const std::shared_ptr<SelectionChangedEventArguments>& arguments)
{
    for (size_t i = 0; i < m_sceneTreeViewItem->GetChildrenAsGameObjects()->GetValue().size(); ++i)
    {
        std::shared_ptr<GameObjectTreeViewItem> gotvi =
            m_sceneTreeViewItem->GetChildrenAsGameObjects()->GetValue().at(i);
        std::shared_ptr<TreeViewItem> treeViewItem =
            m_treeViewItem->GetChildren()->GetValue().at(i);

        gotvi->GetIsSelected()->SetValue(false);
        treeViewItem->GetIsSelected()->SetValue(false);

    }

    for (const std::weak_ptr<Selectable>& selectableWeak : m_windowPackage->
        GetFrameworkManager()->
        GetSelectionManager()->GetSelection(SelectionGroup::Inspectable))
    {
        if (auto selectable = selectableWeak.lock())
        {
            if (auto gameObject = std::dynamic_pointer_cast<GameObject>(selectable))
            {
                for (size_t i = 0; i < m_sceneTreeViewItem->GetChildrenAsGameObjects()->GetValue().size(); ++i)
                {
                    std::shared_ptr<GameObjectTreeViewItem> gotvi =
                        m_sceneTreeViewItem->GetChildrenAsGameObjects()->GetValue().at(i);
                    std::shared_ptr<TreeViewItem> treeViewItem =
                        m_treeViewItem->GetChildren()->GetValue().at(i);

                    if (*gameObject->GetGuid() == *gotvi->GetGameObject()->GetGuid())
                    {
                        gotvi->GetIsSelected()->SetValue(true);
                        treeViewItem->GetIsSelected()->SetValue(true);
                    }
                }
            }
        }
    }
}

void SceneHierarchy::DrawWindowWideContextClickMenu()
{
    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    if (availableSize.y <= 0)
    {
        return;
    }

    ImGui::InvisibleButton("SceneHierarchy-Context-Region", availableSize);
    if (ImGui::BeginPopupContextItem("SceneHierarchy-Context", ImGuiPopupFlags_MouseButtonRight))
    {
        bool haveScene = false;
        if (m_scene)
        {
            haveScene = true;
        }
        if (ImGui::MenuItem("Create new Empty Game Object", nullptr, nullptr, haveScene))
        {
            CreateNewGameObject();
        }

        ImGui::EndPopup();
    }
}

void SceneHierarchy::CreateNewGameObject()
{
    auto newGameObject = std::make_shared<ToolsGameObject>(m_windowPackage->GetParser());
    newGameObject->SetGuid(GUIDHelpers::CreateGUID());

    auto newGoTreeViewItem = std::make_shared<GameObjectTreeViewItem>(m_windowPackage->GetContentManager());
    newGoTreeViewItem->UpdateDistributedWeakPointer(newGoTreeViewItem);
    newGoTreeViewItem->GetLabel()->SetValue("Game Object");
    newGoTreeViewItem->GetIsFramed()->SetValue(false);
    newGoTreeViewItem->SetGameObject(newGameObject);
    newGoTreeViewItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
    newGoTreeViewItem->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::NoIcon);

    // Subscribe to OnSelected.
    std::weak_ptr<FEventObserver> weak = shared_from_this();
    newGoTreeViewItem->OnSelected()->Subscribe(weak);

    // Subscribe to menu items
    newGoTreeViewItem->OnMenuNewGameObject()->Subscribe(weak);

    std::vector<std::shared_ptr<TreeViewItem>> current = m_treeViewItem->GetChildren()->GetValue();
    current.emplace_back(newGoTreeViewItem);
    m_treeViewItem->GetChildren()->SetValue(current);

    std::vector<std::shared_ptr<GameObjectTreeViewItem>> currentGo = m_sceneTreeViewItem->GetChildrenAsGameObjects()->GetValue();
    currentGo.emplace_back(newGoTreeViewItem);
    m_sceneTreeViewItem->GetChildrenAsGameObjects()->SetValue(currentGo);

    m_scene->AddGameObject(newGameObject);
}

void SceneHierarchy::UnselectAll()
{
    if (m_scene)
    {
        for (const std::shared_ptr<GameObject>& go : m_scene->GetGameObjects())
        {
            m_windowPackage->GetFrameworkManager()
                ->GetSelectionManager()
                ->RemoveFromSelection(go);
        }
    }
}
