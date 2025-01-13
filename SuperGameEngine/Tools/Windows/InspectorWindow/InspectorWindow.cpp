#include "InspectorWindow.h"
#include "../../ImGuiIncludes.h"
#include "../../GameEngineEquivalents/Component/Component.h"
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

using namespace SuperGameTools;

InspectorWindow::InspectorWindow()
{
    m_isSetup = false;
}

void InspectorWindow::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    WindowElement::Setup(windowPackage->GetColourPalette());
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

void InspectorWindow::Update()
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

void InspectorWindow::Draw()
{
    if (!m_isSetup)
    {
        return;
    }

    const char* windowName = "Inspector Window";
    RenderWindow(windowName);

    if (m_components)
    {
        m_components->Draw();
    }

    if (!m_errorMessage.empty())
    {
        ImGui::Text(m_errorMessage.c_str());
    }

    EndWindowRender(windowName);
}

void InspectorWindow::TearDown()
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

void InspectorWindow::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (!m_isSetup)
    {
        return;
    }

    if (auto selectionArguments = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        std::vector<std::weak_ptr<Selectable>> inSelection = 
            m_windowPackage->GetFrameworkManager()->GetSelectionManager()->GetSelection(SelectionGroup::Inspectable);

        if (inSelection.empty())
        {
            m_components = {};
            m_currentGameObject = {};
            m_errorMessage = {};
            return;
        }

        if (inSelection.size() > 1)
        {
            m_components = {};
            m_currentGameObject = {};
            m_errorMessage = "There is more than one selection. Select a single item to inspect it.";
            return;
        }

        if (auto sharedObject = inSelection.at(0).lock())
        {
            if (auto asGameObject = std::dynamic_pointer_cast<GameObject>(sharedObject))
            {
                // There is one selection, it is a game object, hold on to it - it is what you are now inspecting.
                m_components = {};
                m_currentGameObject = asGameObject;
                CreateTreeFromObject(asGameObject);
                m_errorMessage = {};
                return;
            }
            else
            {
                m_components = {};
                m_currentGameObject = {};
                m_errorMessage = "Selection type cannot be inspected.";
                return;
            }
        }
    }
}

void InspectorWindow::CreateTreeFromObject(const std::shared_ptr<GameObject>& gameObject)
{
    std::vector<std::shared_ptr<TreeViewItem>> componentsInTreeView;
    for (const std::shared_ptr<Component>& component : *gameObject->GetComponents())
    {
        auto item = std::make_shared<TreeViewItem>(m_windowPackage->GetContentManager());
        item->GetLabel()->SetValue(component->GetType());
        item->GetCollapsibleType()->SetValue(TreeViewItemCollapsibleBehaviour::AlwaysShown);
        item->GetCollapsibleIcon()->SetValue(TreeViewItemCollapsibleIcon::Arrow);
        item->GetIsFramed()->SetValue(true);

        // Create the renderer of our properties.
        auto componentChild = std::make_shared<ComponentTreeViewItem>(m_windowPackage->GetContentManager());
        componentChild->SetComponent(component);
        std::vector<std::shared_ptr<TreeViewItem>> children;
        children.emplace_back(componentChild);
        item->GetChildren()->SetValue(children);

        componentsInTreeView.emplace_back(item);
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
