#include "SuperViewportTools.h"

#include "SuperViewportToolsButton.h"
#include "ViewportButtonInfo.h"
#include "ViewportDebugOptionsChangedArguments.h"
#include "ViewportToolsButtonSelectedArguments.h"
#include "Engine/Content/ContentManager.h"
#include "Panels/SceneHierarchy/GameObjectTreeViewItem.h"
#include "ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

SuperViewportTools::SuperViewportTools(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;
    m_selectedTool = ViewportToolsType::Select;
    m_viewportButtonInfo = {};
    m_onSelectedToolChanged = std::make_shared<FEvent>();
    m_onDebugOptionsChanged = std::make_shared<FEvent>();
    m_debugOption = ViewportDebugOption::None;
}

void SuperViewportTools::Setup()
{
    if (!m_toolsButtons.empty())
    {
        Log::Error("Setup called more than once.",
            "SuperViewportTools::Setup");
        return;
    }

    // Create all buttons.
    for (const ViewportToolsType& toolsType : EViewportToolsType::ToVector())
    {
        m_toolsButtons.insert_or_assign(toolsType, std::make_shared<SuperViewportToolsButton>(m_windowPackage, toolsType, m_viewportButtonInfo));
    }

    // Ensure each of them know when others are selected.
    for (const ViewportToolsType& toolsType : EViewportToolsType::ToVector())
    {

        for (const ViewportToolsType& innerToolsType : EViewportToolsType::ToVector())
        {
            if (toolsType == innerToolsType)
            {
                continue;
            }

            m_toolsButtons.at(toolsType)->OnSelected()->Subscribe(m_toolsButtons.at(innerToolsType));
        }

        m_toolsButtons.at(toolsType)->OnSelected()->Subscribe(FEventObserver::shared_from_this());
    }

    // Select the select tool by default
    m_toolsButtons.at(ViewportToolsType::Select)->Select();
}

ViewportToolsType SuperViewportTools::GetSelectedTool() const
{
    return m_selectedTool;
}

void SuperViewportTools::SelectTool(ViewportToolsType newValue)
{
    m_selectedTool = newValue;
    m_toolsButtons.at(newValue)->Select();
}

void SuperViewportTools::Draw()
{
    for (const ViewportToolsType& toolsType : EViewportToolsType::ToVector())
    {
        m_toolsButtons.at(toolsType)->Draw();
        ImGui::SameLine();
    }

    // Add a little margin to anything rendered after the tools.
    ImVec2 groupMin = ImGui::GetCursorPos();
    ImGui::SetCursorPosY(groupMin.y + 35);
    ImGui::SetCursorPosX(8);

    ImGui::SameLine();
    ImGui::BeginChild(
        "PanelWithMenu",
        ImVec2(0, 20),
        ImGuiChildFlags_None,
        ImGuiWindowFlags_MenuBar
    );

    bool debugOptionsChanged = false;
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            if (ImGui::BeginMenu("Debug Overlays"))
            {
                for (const ViewportDebugOption& option : EViewportDebugOption::ToVector())
                {
                    if (option == ViewportDebugOption::None)
                    {
                        continue;
                    }

                    if (ImGui::Selectable(EViewportDebugOption::ToString(option).c_str(), 
                        EViewportDebugOption::HasFlag(m_debugOption, option), 
                        ImGuiSelectableFlags_NoAutoClosePopups))
                    {
                        m_debugOption ^= option;
                        debugOptionsChanged = true;
                    }
                }

                if (ImGui::Selectable("Reset", false, ImGuiSelectableFlags_NoAutoClosePopups))
                {
                    m_debugOption = ViewportDebugOption::None;
                    debugOptionsChanged = true;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    ImGui::EndChild();

    // Ensure the height is still drawn the same.
    ImGui::SetCursorPosY(groupMin.y + 35);

    if (debugOptionsChanged)
    {
        m_onDebugOptionsChanged->Invoke(std::make_shared<ViewportDebugOptionsChanged>(m_debugOption));
    }
}

void SuperViewportTools::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
    if (auto args = std::dynamic_pointer_cast<ViewportToolsButtonSelectedArguments>(arguments))
    {
        m_selectedTool = args->GetButtonSelected();
        m_onSelectedToolChanged->Invoke(args);
    }
}

std::shared_ptr<FatedQuestLibraries::FEvent> SuperViewportTools::OnSelectedToolChanged() const
{
    return m_onSelectedToolChanged;
}

std::shared_ptr<FatedQuestLibraries::FEvent> SuperViewportTools::OnDebugOptionsChanged() const
{
    return m_onDebugOptionsChanged;
}
