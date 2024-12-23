#include "LoggerOutput.h"

#include <string>

#include "../../../Engine/Imgui/External/imgui_internal.h"

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
}

void LoggerOutput::Update()
{
}

void LoggerOutput::Draw()
{
    //ImGui::ShowDemoWindow();

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

    ImGuiTableFlags flags = ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
    if (ImGui::BeginTable("table1", 2, flags))
    {
        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 2; column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::TextUnformatted("Col");
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void LoggerOutput::TearDown()
{
}
