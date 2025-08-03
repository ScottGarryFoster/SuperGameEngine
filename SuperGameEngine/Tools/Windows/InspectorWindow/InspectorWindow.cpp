#include "InspectorWindow.h"

#include "InspectAssetObject.h"
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

InspectorWindow::InspectorWindow()
{
    m_isSetup = false;
    m_inspectGameObject = std::make_shared<InspectGameObject>();
    m_inspectAssetObject = std::make_shared<InspectAssetObject>();

    m_onMenuDeleteComponent = std::make_shared<FEvent>();
}

void InspectorWindow::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    WindowElement::Setup(windowPackage->GetColourPalette());
    m_windowPackage = windowPackage;
    m_inspectGameObject->OnMenuDelete()->Subscribe(GetWeakDistributed());
    m_inspectGameObject->Setup(m_windowPackage);

    m_inspectAssetObject->Setup(windowPackage);

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

    m_inspectGameObject->Update();
    m_inspectAssetObject->Update();
}

void InspectorWindow::Draw()
{
    if (!m_isSetup)
    {
        return;
    }

    const char* windowName = "Inspector Window";
    if (RenderWindow(windowName))
    {
        m_inspectGameObject->Draw();
        m_inspectAssetObject->Draw();

        if (!m_errorMessage.empty())
        {
            ImGui::Text(m_errorMessage.c_str());
        }

    }
    EndWindowRender(windowName);
}

void InspectorWindow::TearDown()
{
    m_inspectGameObject->TearDown();
    m_inspectAssetObject->TearDown();
}

std::shared_ptr<FEventSubscriptions> InspectorWindow::OnMenuDelete() const
{
    return m_onMenuDeleteComponent;
}

void InspectorWindow::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (!m_isSetup)
    {
        return;
    }

    if (auto onMenuDeleteComponent = std::dynamic_pointer_cast<OnMenuDeleteComponentEventArguments>(arguments))
    {
        m_onMenuDeleteComponent->Invoke(arguments);
    }
}
