#include "AssetTileRender.h"

#include "FileManagement/AssetFile.h"
#include "ToolsEngine/ViewElements/ColoursAndStyles/ToolsColoursAndStyles.h"
#include "../../FatedQuestLibraries.h"
#include "../../Engine/Graphics/ImGuiSuperTexture.h"
#include "Engine/Content/ContentManager.h"
#include "FileManagement/AssetFile.h"
#include "FileManagement/AssetFolder.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

AssetTileRender::AssetTileRender(
    const std::shared_ptr<AssetFolder>& rootFolder,
    const std::shared_ptr<SuperGameEngine::TextureManager>& texture)
{

    m_folderTexture = texture->GetTexture(R"(Tools\Icons\Info\Info-25.png)");
    m_currentFolder = rootFolder;
    m_rootFolder = rootFolder;
}

void AssetTileRender::Update()
{
}

void AssetTileRender::Draw()
{
    std::shared_ptr<AssetFolder> newCurrentFolder = nullptr;

    int thumbSize = 64;
    int padding = 8;
    float pw = ImGui::GetContentRegionAvail().x;
    int cols = max(1, int(pw / (thumbSize + padding)));

    ImGui::Columns(cols, "AssetBrowserArea", false);
    int i = 0;
    for (const std::shared_ptr<AssetFolder>& folder : m_currentFolder->GetContainingFolders())
    {
        ImGui::PushID(("AssetBrowser-" + std::to_string(i)).c_str());


        ImGui::BeginGroup();
        ImVec2 group_min = ImGui::GetCursorScreenPos();

        RectangleInt uv = RectangleInt(0, 0, m_folderTexture->Size().GetX(), m_folderTexture->Size().GetY());
        RectangleInt screen = RectangleInt(0, 0, thumbSize, thumbSize);
        m_folderTexture->Draw(uv, screen);

        ImVec2 position = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(
            position.x,
            position.y + thumbSize + padding));

        ImGui::PushTextWrapPos(position.x + thumbSize);
        ImGui::TextWrapped("%s", folder->GetDisplayName().c_str());
        ImGui::PopTextWrapPos();

        ImGui::EndGroup();

        ImVec2 group_max = ImGui::GetCursorScreenPos();

        group_max.x = group_min.x + thumbSize;

        if (ImGui::IsMouseHoveringRect(group_min, group_max) &&
            ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            Log::Info("Clicked " + folder->GetPackagePath());
            newCurrentFolder = folder;
        }


        ImGui::NextColumn();
        ImGui::PopID();
        ++i;
    }



    for (const std::shared_ptr<AssetFile>& asset : m_currentFolder->GetContainingFiles())
    {
        ImGui::PushID(("AssetBrowser-" + std::to_string(i)).c_str());


        ImGui::BeginGroup();
        ImVec2 group_min = ImGui::GetCursorScreenPos();

        RectangleInt screen = RectangleInt(0, 0, thumbSize, thumbSize);
        asset->DrawLargeTile(screen);

        ImVec2 position = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(
            position.x,
            position.y + thumbSize + padding));

        ImGui::PushTextWrapPos(position.x + thumbSize);
        ImGui::TextWrapped("%s", asset->GetDisplayName().c_str());
        ImGui::PopTextWrapPos();

        ImGui::EndGroup();

        ImVec2 group_max = ImGui::GetCursorScreenPos();

        group_max.x = group_min.x + thumbSize;

        if (ImGui::IsMouseHoveringRect(group_min, group_max) &&
            ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            Log::Info("Clicked " + asset->GetPackagePath());
        }


        ImGui::NextColumn();
        ImGui::PopID();
        ++i;
    }

    ImGui::Columns(1);

    if (newCurrentFolder)
    {
        m_currentFolder = newCurrentFolder;

    }
}
