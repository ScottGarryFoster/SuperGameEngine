#include "SuperViewportToolsButton.h"

#include "ViewportToolsButtonSelectedArguments.h"
#include "../../../../FatedQuest.Libraries/Observer/FEvent.h"
#include "../../../../FatedQuest.Libraries/Logger/AllReferences.h"
#include "Engine/Content/ContentManager.h"
#include "Imgui/External/imgui.h"
#include "ToolsEngine/Packages/WindowPackage.h"


using namespace SuperGameTools;
using namespace FatedQuestLibraries;

SuperViewportToolsButton::SuperViewportToolsButton(
    const std::shared_ptr<WindowPackage>& windowPackage,
    ViewportToolsType buttonType, 
    const ViewportButtonInfo& buttonInfo)
{
    m_toolType = buttonType;
    m_onSelected = std::make_shared<FEvent>();
    m_isSelected = false;

    const std::string& texture = buttonInfo.Textures.at(buttonType);
    m_texture = windowPackage->GetContentManager()->Texture()->GetTexture(texture);

    m_textureWidthHeight = m_texture->Size().GetX();
    if (m_texture->Size().GetX() != m_texture->Size().GetY())
    {
        Log::Error("When creating a viewport tools button the texture was not a square. This will lead to a mis-shapen button."
            "Texture: " + texture,
            "SuperViewportToolsButton");
    }
}

void SuperViewportToolsButton::Draw()
{
    // We need to draw the selection rectangle now but we do not know
    // how big it is going to be. So we split the draw list, and then
    // come back and merge later. 
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->ChannelsSplit(2);
    drawList->ChannelsSetCurrent(1);

    ImGui::BeginGroup();
    ImVec2 groupMin = ImGui::GetCursorScreenPos();

    RectangleInt uv = RectangleInt(0, 0, m_texture->Size().GetX(), m_texture->Size().GetY());
    RectangleInt screen = RectangleInt(0, 0, m_texture->Size().GetX(), m_texture->Size().GetY());
    m_texture->Draw(uv, screen);

    ImVec2 groupMax = ImGui::GetCursorScreenPos();
    groupMax.x += m_textureWidthHeight;
    groupMax.y += m_textureWidthHeight;
    ImGui::EndGroup();

    ImVec2 topLeft = ImVec2(groupMin.x - m_buttonPadding, groupMin.y - m_buttonPadding);
    ImVec2 bottomRight = ImVec2(groupMax.x + m_buttonPadding, groupMax.y + m_buttonPadding);

    if (ImGui::IsMouseHoveringRect(topLeft, bottomRight) &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        Select();
    }

    if (m_isSelected)
    {
        // Draw this first as this is the selection box.
        drawList->ChannelsSetCurrent(0);

        // Fill
        drawList->AddRectFilled(
            topLeft,
            bottomRight,
            IM_COL32(0, 0, 0, 128),
            5.0f,
            ImDrawFlags_None);

        // Border
        drawList->AddRect(
            topLeft,
            bottomRight,
            IM_COL32(255, 255, 255, 200),
            5.0f,
            ImDrawFlags_None,
            2.0f);
    }

    drawList->ChannelsMerge();
}

std::shared_ptr<FEventSubscriptions> SuperViewportToolsButton::OnSelected() const
{
    return m_onSelected;
}

void SuperViewportToolsButton::Invoke(std::shared_ptr<FEventArguments> arguments)
{
    if (auto buttonsArguments = std::dynamic_pointer_cast<ViewportToolsButtonSelectedArguments>(arguments))
    {
        std::string name = EViewportToolsType::ToString(buttonsArguments->GetButtonSelected());
        Log::Info("Called on selected: " + name);

        m_isSelected = false;
    }
}

void SuperViewportToolsButton::Select()
{
    m_isSelected = true;
    auto arguments = std::make_shared<ViewportToolsButtonSelectedArguments>(m_toolType);
    m_onSelected->Invoke(arguments);
}