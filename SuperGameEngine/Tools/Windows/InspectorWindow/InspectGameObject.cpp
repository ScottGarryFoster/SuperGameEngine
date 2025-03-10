#include "InspectGameObject.h"
#include "../../ImGuiIncludes.h"
#include "../../GameEngineEquivalents/Component/Component.h"
#include "../../GameEngineEquivalents/Component/ComponentTreeViewHeaderItem.h"
#include "../../GameEngineEquivalents/Component/ComponentTreeViewItem.h"
#include "../../GameEngineEquivalents/Component/ToolsComponent.h"
#include "../../ToolsEngine/FrameworkManager/FrameworkManager.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionChangedEventArguments.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionGroup.h"
#include "../../ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeView.h"
#include "../../GameEngineEquivalents/GameObject/ToolsGameObject.h"
#include "../../ToolsEngine/ViewElements/TreeView/TreeViewItem.h"
#include "../../../Engine/Structural/GameObject/ComponentFactory.h"
#include "../SceneHierarchy/EventArguments/OnMenuDeleteComponentEventArguments.h"

using namespace SuperGameTools;

InspectGameObject::InspectGameObject()
{
    m_isSetup = false;
    m_onMenuDeleteComponent = std::make_shared<FEvent>();
}

void InspectGameObject::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;

    if (!m_windowPackage->GetFrameworkManager())
    {
        Log::Error("No framework manager found, "
            "this means we do not know what is selected.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetSelectionManager())
    {
        Log::Error("No selection manager found, "
            "this means we do not know what is selected.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    std::weak_ptr<FEventObserver> observer = shared_from_this();
    m_windowPackage->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged()->Subscribe(observer);

    if (!m_windowPackage->GetContentManager())
    {
        Log::Error("No content manager found, "
            "this means we cannot create a tree for the components.",
            "InspectorWindow::Setup(std::shared_ptr<WindowPackage>)");
        return;
    }

    m_isSetup = true;
}

void InspectGameObject::Update()
{
    if (!m_isSetup)
    {
        return;
    }

    if (m_components)
    {
        m_components->Update();
    }
}

void InspectGameObject::Draw()
{
    if (!m_isSetup)
    {
        return;
    }

    if (!m_gameObject)
    {
        return;
    }

    if (m_components)
    {
        m_components->Draw();
    }

    DrawInspectContextWindow();
}

void InspectGameObject::TearDown()
{
    if (!m_windowPackage->GetFrameworkManager())
    {
        return;
    }

    if (!m_windowPackage->GetFrameworkManager()->GetSelectionManager())
    {
        return;
    }

    std::weak_ptr<FEventObserver> observer = shared_from_this();
    m_windowPackage->GetFrameworkManager()->GetSelectionManager()->OnSelectionChanged()->Unsubscribe(observer);
}

std::shared_ptr<FEventSubscriptions> InspectGameObject::OnMenuDelete() const
{
    return m_onMenuDeleteComponent;
}

void InspectGameObject::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (!m_isSetup)
    {
        return;
    }

    if (auto selectionArguments = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        OnSelectionChanged();
    }
    else if (auto onMenuDeleteComponentArguments = std::dynamic_pointer_cast<OnMenuDeleteComponentEventArguments>(arguments))
    {
        OnDeleteComponent(onMenuDeleteComponentArguments->GetUniqueId(), onMenuDeleteComponentArguments->GetComponent());
    }
}

void InspectGameObject::CreateTreeFromObject(const std::shared_ptr<GameObject>& gameObject)
{
    m_gameObject = gameObject;

    std::vector<std::shared_ptr<TreeViewItem>> componentsInTreeView;
    for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
    {
        auto componentTVI =
            CreateComponentTreeViewItemFromComponent(component);
        componentsInTreeView.emplace_back(componentTVI);
    }

    auto root = std::make_shared<TreeViewItem>(m_windowPackage->GetContentManager());
    root->GetLabel()->SetValue("Root... hide me");
    root->GetChildren()->SetValue(componentsInTreeView);
    root->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
    root->GetOpenOnLoad()->SetValue(true);
    root->GetShouldRender()->SetValue(false);

    m_components = std::make_shared<TreeView>(m_windowPackage->GetContentManager(), root);
    m_components->SetDepthToStartIndentation(1);
}

void InspectGameObject::DrawInspectContextWindow()
{
    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    if (availableSize.y <= 0)
    {
        return;
    }

    if (!m_gameObject)
    {
        return;
    }

    // Draw add component context menu.
    ImGui::InvisibleButton("SceneHierarchy-Context-Region", availableSize);
    if (ImGui::BeginPopupContextItem("SceneHierarchy-Context", ImGuiPopupFlags_MouseButtonRight))
    {
        ImGui::MenuItem("Add Component", nullptr, nullptr, false);

        std::vector<std::string> types = SuperGameEngine::ComponentFactory::GetAllComponentTypes();
        for (const std::string& type : types)
        {
            if (ImGui::MenuItem(type.c_str(), nullptr, nullptr))
            {
                std::shared_ptr<Component> component = m_gameObject->AddComponent(type);

                std::vector<std::shared_ptr<TreeViewItem>> children = m_components->GetRootItem()->GetChildren()->GetValue();
                auto componentTVI =
                    CreateComponentTreeViewItemFromComponent(component);
                children.emplace_back(componentTVI);

                m_components->GetRootItem()->GetChildren()->SetValue(children);
            }
        }


        ImGui::EndPopup();
    }
}

std::shared_ptr<TreeViewItem>
InspectGameObject::CreateComponentTreeViewItemFromComponent(
    const std::shared_ptr<Component>& component)
{
    auto item = std::make_shared<ComponentTreeViewHeaderItem>(m_windowPackage->GetContentManager());
    item->GetLabel()->SetValue(component->GetType());
    item->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::OpenCloseFromArrowOnly);
    item->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::Arrow);
    item->GetIsFramed()->SetValue(true);
    item->UpdateDistributedWeakPointer(item);
    item->GetOpenOnLoad()->SetValue(true);
    item->OnMenuDelete()->Subscribe(shared_from_this());

    // [#156] Copying the Vectors here is awful. Address this. 
    // Create the renderer of our properties.
    auto componentChild = std::make_shared<ComponentTreeViewItem>(m_windowPackage->GetContentManager());
    componentChild->SetComponent(component);
    std::vector<std::shared_ptr<TreeViewItem>> children;
    children.emplace_back(componentChild);
    item->GetChildren()->SetValue(children);

    componentChild->UpdateDistributedWeakPointer(componentChild);

    std::vector<std::shared_ptr<ComponentTreeViewItem>> componentTreeViewItemChildren;
    componentTreeViewItemChildren.emplace_back(componentChild);
    item->GetChildrenAsComponents()->SetValue(componentTreeViewItemChildren);

    return item;
}

void InspectGameObject::OnSelectionChanged()
{
    std::vector<std::weak_ptr<Selectable>> inSelection =
        m_windowPackage->GetFrameworkManager()->GetSelectionManager()->GetSelection(SelectionGroup::Inspectable);

    if (inSelection.empty())
    {
        m_components = {};
        m_gameObject = {};
        m_errorMessage = {};
        return;
    }

    if (inSelection.size() > 1)
    {
        m_components = {};
        m_gameObject = {};
        m_errorMessage = "There is more than one selection. Select a single item to inspect it.";
        return;
    }

    if (auto sharedObject = inSelection.at(0).lock())
    {
        if (auto asGameObject = std::dynamic_pointer_cast<GameObject>(sharedObject))
        {
            // There is one selection, it is a game object, hold on to it - it is what you are now inspecting.
            m_components = {};
            m_gameObject = asGameObject;
            CreateTreeFromObject(asGameObject);
            m_errorMessage = {};
            return;
        }
        else
        {
            m_components = {};
            m_gameObject = {};
            m_errorMessage = "Selection type cannot be inspected.";
            return;
        }
    }
}

void InspectGameObject::OnDeleteComponent(
    const std::shared_ptr<Guid>& treeViewItemGuid,
    const std::shared_ptr<Component>& component)
{
    m_components->GetRootItem()->GetChildren()->Remove([treeViewItemGuid](const std::shared_ptr<TreeViewItem>& tvi)
    {
            return tvi->GetUniqueID() == treeViewItemGuid;
    });

    m_onMenuDeleteComponent->Invoke(std::make_shared<OnMenuDeleteComponentEventArguments>(treeViewItemGuid, component));
}
