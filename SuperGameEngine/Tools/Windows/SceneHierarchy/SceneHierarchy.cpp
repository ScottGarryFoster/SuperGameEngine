#include "SceneHierarchy.h"


#include "ToolsSceneLoader.h"
#include "../../ImGuiIncludes.h"
#include "../../../Engine/Engine/Content/ContentManager.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/TreeView.h"
#include "../../ToolsEngine/ViewElements/TreeViewItem.h"
#include "../../ToolsEngine/ViewElements/TreeViewItemOnSelectedEventArguments.h"

using namespace SuperGameTools;

SceneHierarchy::SceneHierarchy()
{
    m_testPopup = false;
    m_testPopupText = {};
}

void SceneHierarchy::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    if (!windowPackage->GetContentManager())
    {
        Log::Error("No Content Manager found.", "SceneHierarchy::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    if (!windowPackage->GetContentManager()->GamePackage())
    {
        Log::Error("No Game Package found.", "SceneHierarchy::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    m_sceneLoader = std::make_shared<ToolsSceneLoader>(
        windowPackage->GetContentManager()->GamePackage());

    std::string path = "savedOut.txt";
    std::shared_ptr<ModifiableDocument> document = 
        m_sceneLoader->LoadScene(path);
    if (!document)
    {
        Log::Error("Could not load scene. Path: " + path, 
            "SceneHierarchy::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    m_treeViewItem = std::make_shared<TreeViewItem>();
    m_treeViewItem->GetLabel()->SetValue("Scene");

    auto children = std::vector<std::shared_ptr<TreeViewItem>>();
    for (std::shared_ptr<StoredDocumentNode> child = document->GetRoot()->GetFirstChild(); child; child = child->GetAdjacentNode())
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

    m_tree = std::make_shared<TreeView>(windowPackage->GetContentManager(), m_treeViewItem);
    m_tree->ShouldRootBeFrame(true);
    m_tree->SetDepthToStartIndentation(1);
}

void SceneHierarchy::Draw()
{
    ImGui::Begin("Scene Hierarchy");

    m_tree->Draw();

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
    if (auto treeViewItemArgs = std::static_pointer_cast<TreeViewItemOnSelectedEventArguments>(arguments))
    {
        // Test Popup
        m_testPopup = true;
        m_testPopupText = treeViewItemArgs->GetTreeViewItem()->GetLabel()->GetValue();
    }
}
