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
        // Test Popup
        //m_testPopup = true;
        //m_testPopupText = treeViewItemArgs->GetTreeViewItem()->GetLabel()->GetValue();

        if (!treeViewItemArgs->GetTreeViewItem())
        {
            return;
        }

        if (auto gameObjectTreeView = std::dynamic_pointer_cast<GameObjectTreeViewItem>(treeViewItemArgs->GetTreeViewItem()))
        {
            if (gameObjectTreeView->GetGameObject())
            {
                m_windowPackage->GetFrameworkManager()->GetSelectionManager()->SetSelection(gameObjectTreeView->GetGameObject());
            }
        }

        RemoveSelectionFromAllBut(treeViewItemArgs->GetTreeViewItem(), m_treeViewItem);
    }
    else if (auto menuItemSelected = std::dynamic_pointer_cast<DocumentActionEventArguments>(arguments))
    {
        if (menuItemSelected->GetDocument())
        {
            if (auto sceneDocument = std::dynamic_pointer_cast<SceneDocument>(menuItemSelected->GetDocument()))
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
}

bool SceneHierarchy::LoadScene(const std::shared_ptr<SceneDocument>& document)
{
    if (!document)
    {
        Log::Error("No document given.",
            "bool SceneHierarchy::LoadScene(std::shared_ptr<SceneDocument>)");
        return false;
    }
    m_sceneDocument = document;

    std::shared_ptr<ModifiableDocument> sceneDocument = document->GetDocument();
    if (!sceneDocument)
    {
        Log::Error("No document loaded into the scene document.",
            "bool SceneHierarchy::LoadScene(std::shared_ptr<SceneDocument>)");
        return false;
    }

    m_treeViewItem = std::make_shared<TreeViewItem>(m_windowPackage->GetContentManager());
    m_treeViewItem->GetLabel()->SetValue("Scene");
    m_treeViewItem->GetOpenOnLoad()->SetValue(true);
    m_treeViewItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
    m_treeViewItem->GetIsFramed()->SetValue(true);

    // Subscribe to OnSelected.
    std::weak_ptr<FEventObserver> weak = shared_from_this();
    m_treeViewItem->OnSelected()->Subscribe(weak);

    auto children = std::vector<std::shared_ptr<TreeViewItem>>();
    for (std::shared_ptr<StoredDocumentNode> child = sceneDocument->GetRoot()->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        auto childItem = std::make_shared<GameObjectTreeViewItem>(m_windowPackage->GetContentManager());
        childItem->GetLabel()->SetValue("Game Object");
        childItem->GetIsFramed()->SetValue(false);

        // Create the game object
        auto gameObject = std::make_shared<ToolsGameObject>();
        childItem->SetGameObject(gameObject);
        bool createdGuid = false;
        if (std::shared_ptr<StoredDocumentAttribute> attribute = child->Attribute("Guid", CaseSensitivity::IgnoreCase))
        {
            if (!attribute->Value().empty())
            {
                gameObject->SetGuid(GUIDHelpers::CreateFromString(attribute->Value()));
                createdGuid = true;
            }
        }

        if (!createdGuid)
        {
            gameObject->SetGuid(GUIDHelpers::CreateGUID());
        }

        // Subscribe to OnSelected.
        std::weak_ptr<FEventObserver> weak = shared_from_this();
        childItem->OnSelected()->Subscribe(weak);
        childItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
        childItem->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::NoIcon);
        children.emplace_back(childItem);

        for (std::shared_ptr<StoredDocumentNode> compChild = child->GetFirstChild(); compChild; compChild = compChild->GetAdjacentNode())
        {
            std::string typeName = {};
            std::shared_ptr<StoredDocumentAttribute> typeAtt = compChild->Attribute("Type", CaseSensitivity::IgnoreCase);
            if (typeAtt)
            {
                typeName = typeAtt->Value();
            }
            else
            {
                typeName = "Component";
            }

            // The component to the game object.
            auto componentObject = std::make_shared<ToolsComponent>();
            componentObject->SetType(typeName);
            gameObject->GetComponents()->emplace_back(componentObject);
        }
    }
    m_treeViewItem->GetChildren()->SetValue(children);

    m_tree = std::make_shared<TreeView>(m_windowPackage->GetContentManager(), m_treeViewItem);
    m_tree->ShouldRootBeFrame(true);
    m_tree->SetDepthToStartIndentation(1);

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