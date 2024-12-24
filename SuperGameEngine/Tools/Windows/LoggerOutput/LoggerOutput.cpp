#include "LoggerOutput.h"

#include <string>

#include "../../../Engine/Engine/Content/ContentManager.h"
#include "../../../Engine/Imgui/External/imgui_internal.h"
#include "../../Engine/Graphics/ImGuiSuperTexture.h"
#include "../../ToolsEngine/Packages/WindowPackage.h"

using namespace SuperGameTools;

LoggerOutput::LoggerOutput()
{

}

LoggerOutput::~LoggerOutput()
{

}

void LoggerOutput::Setup(const std::shared_ptr<WindowPackage>& windowPackage)
{
    m_windowPackage = windowPackage;

    auto texture = m_windowPackage->GetContentManager()->Texture()->GetTexture(R"(Tools\Icons\Warning\Warning-25.png)");
    m_warningIcon = std::static_pointer_cast<ImGuiSuperTexture>(texture);

    texture = m_windowPackage->GetContentManager()->Texture()->GetTexture(R"(Tools\Icons\Info\Info-25.png)");
    m_infoIcon = std::static_pointer_cast<ImGuiSuperTexture>(texture);

    texture = m_windowPackage->GetContentManager()->Texture()->GetTexture(R"(Tools\Icons\Error\Error-25.png)");
    m_errorIcon = std::static_pointer_cast<ImGuiSuperTexture>(texture);
}

void LoggerOutput::Update()
{
}

void LoggerOutput::Draw()
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("Logger Output");
    if (!ImGui::IsWindowDocked())
    {
        ImGui::End();
        return;
    }

    ImGuiWindow* window = ImGui::FindWindowByName("Logger Output");
    if (window->Size.x < 50 || window->Size.y < 50)
    {
        ImGui::SetWindowPos(window, ImVec2(0, 100));
        ImGui::SetWindowSize(window, ImVec2(400, 200));
    }

    ImGuiTableFlags flags = ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit;
    if (ImGui::BeginTable("table1", 2, flags))
    {
        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow(0, 30);
            for (int column = 0; column < 2; column++)
            {
                ImGui::TableSetColumnIndex(column);
                if (column == 0)
                {

                    m_errorIcon->Draw();
                }
                else
                {
                    // Move down slightly to ensure the text is in the center or close to.
                    float cellHeight = ImGui::GetTextLineHeightWithSpacing();
                    float textHeight = ImGui::GetTextLineHeight();
                    float verticalOffset = (cellHeight - textHeight) * 0.5f;
                    float cursorY = ImGui::GetCursorPosY();
                    ImGui::SetCursorPosY(cursorY + verticalOffset);

                    ImGui::TextUnformatted("Col");
                }

            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void LoggerOutput::TearDown()
{
}
