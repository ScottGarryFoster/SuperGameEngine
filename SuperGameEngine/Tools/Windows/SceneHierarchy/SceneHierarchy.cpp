#include "SceneHierarchy.h"
#include "../../ImGuiIncludes.h"
#include "../../ToolsEngine/ViewElements/TreeView.h"
#include "../../ToolsEngine/ViewElements/TreeViewItem.h"

using namespace SuperGameTools;

void SceneHierarchy::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    //TreeNode child1;
    //child1.label = "Inner1";
    //child1.id = 1;

    //TreeNode child2;
    //child2.label = "Inner2";
    //child2.id = 2;

    //TreeNode root;
    //root.label = "Root";
    //root.id = 0;
    //root.children = { child1, child2 };

    //m_treeNode = root;
    auto child1 = std::make_shared<TreeViewItem>();
    child1->GetLabel()->SetValue("Child 1");

    auto child2 = std::make_shared<TreeViewItem>();
    child2->GetLabel()->SetValue("Child 2");

    auto root = std::make_shared<TreeViewItem>();
    root->GetLabel()->SetValue("Root");

    auto children = std::vector<std::shared_ptr<TreeViewItem>>();
    children.emplace_back(child1);
    children.emplace_back(child2);
    root->GetChildren()->SetValue(children);


    m_tree = std::make_shared<TreeView>(root);
}

void SceneHierarchy::Draw()
{
    ImGui::Begin("Scene Hierarchy");

    m_tree->Draw();

    ImGui::End();
}