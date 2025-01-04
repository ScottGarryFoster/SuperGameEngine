#include "SceneHierarchy.h"


#include "ToolsSceneLoader.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Content/ContentManager.h"
#include "../../ToolsEngine/Documents/Scene/SceneDocument.h"
#include "../../ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "../../ToolsEngine/FrameworkManager/DocumentManager/DocumentManager.h"
#include "../../ToolsEngine/FrameworkManager/DocumentManager/DocumentEvent/DocumentActionEventArguments.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemView.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuItemViewEventArguments.h"
#include "../../ToolsEngine/ViewElements/Menu/MenuView.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeView.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItemOnSelectedEventArguments.h"

using namespace SuperGameTools;

SceneHierarchy::SceneHierarchy()
{
    m_testPopup = false;
    m_testPopupText = {};
}

void SceneHierarchy::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;

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
    ImGui::Begin("Scene Hierarchy");

    if (m_tree)
    {
        m_tree->Draw();
    }


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

    ImGui::End();



}

void SceneHierarchy::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto treeViewItemArgs = std::dynamic_pointer_cast<TreeViewItemOnSelectedEventArguments>(arguments))
    {
        // Test Popup
        m_testPopup = true;
        m_testPopupText = treeViewItemArgs->GetTreeViewItem()->GetLabel()->GetValue();
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

    m_treeViewItem = std::make_shared<TreeViewItem>();
    m_treeViewItem->GetLabel()->SetValue("Scene");
    m_treeViewItem->GetOpenOnLoad()->SetValue(true);

    auto children = std::vector<std::shared_ptr<TreeViewItem>>();
    for (std::shared_ptr<StoredDocumentNode> child = sceneDocument->GetRoot()->GetFirstChild(); child; child = child->GetAdjacentNode())
    {
        auto childItem = std::make_shared<TreeViewItem>();
        childItem->GetLabel()->SetValue("Game Object");

        // Subscribe to OnSelected.
        std::weak_ptr<FEventObserver> weak = shared_from_this();
        childItem->OnSelected()->Subscribe(weak);

        children.emplace_back(childItem);

        // Add components. This will be removed when we move these to the inspector.
        auto compChildren = std::vector<std::shared_ptr<TreeViewItem>>();
        for (std::shared_ptr<StoredDocumentNode> compChild = child->GetFirstChild(); compChild; compChild = compChild->GetAdjacentNode())
        {
            auto compItem = std::make_shared<TreeViewItem>();
            compItem->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::NoIcon);
            compItem->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::AlwaysShown);

            std::shared_ptr<StoredDocumentAttribute> typeAtt = compChild->Attribute("Type", CaseSensitivity::IgnoreCase);
            if (typeAtt)
            {
                compItem->GetLabel()->SetValue(typeAtt->Value());
            }
            else
            {
                compItem->GetLabel()->SetValue("Component");
            }

            // Subscribe to OnSelected.
            std::weak_ptr<FEventObserver> weak = shared_from_this();
            compItem->OnSelected()->Subscribe(weak);
            compChildren.emplace_back(compItem);
        }
        childItem->GetChildren()->SetValue(compChildren);
    }
    m_treeViewItem->GetChildren()->SetValue(children);

    m_tree = std::make_shared<TreeView>(m_windowPackage->GetContentManager(), m_treeViewItem);
    m_tree->ShouldRootBeFrame(true);
    m_tree->SetDepthToStartIndentation(1);

    return true;
}