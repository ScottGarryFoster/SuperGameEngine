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

    m_folderTexture = texture->GetTexture(R"(Tools\Icons\Folder\Folder-256.png)");
    m_upFolderTexture = texture->GetTexture(R"(Tools\Icons\FolderUp\FolderUp-256.png)");
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

    auto startColumn = [](int i)
        {
            ImGui::PushID(("AssetBrowser-" + std::to_string(i)).c_str());
        };

    auto endColumn = [](int& i)
        {
            ++i;

            ImGui::NextColumn();
            ImGui::PopID();
        };

    if (m_currentFolder != m_rootFolder)
    {
        if (std::shared_ptr<AssetFolder> folder = m_currentFolder->GetParent().lock())
        {
            startColumn(i);
            if (DrawReturnFolder(m_currentFolder, thumbSize, padding))
            {
                newCurrentFolder = folder;
            }

            endColumn(i);
        }
    }

    for (const std::shared_ptr<AssetFolder>& folder : m_currentFolder->GetContainingFolders())
    {
        startColumn(i);
        if (std::shared_ptr<AssetFolder> newFolder = DrawFolder(folder, thumbSize, padding))
        {
            newCurrentFolder = newFolder;
        }

        endColumn(i);
    }

    for (const std::shared_ptr<AssetFile>& asset : m_currentFolder->GetContainingFiles())
    {
        startColumn(i);

        if (std::shared_ptr<AssetFile> fileSelected = DrawFile(asset, thumbSize, padding))
        {
            // Do something with fileSelected in a future commit.
        }

        endColumn(i);
    }

    if (newCurrentFolder)
    {
        m_currentFolder = newCurrentFolder;

    }
}

std::shared_ptr<AssetFolder> AssetTileRender::DrawFolder(
    const std::shared_ptr<AssetFolder>& folder, 
    int size,
    int padding) const
{
    ImGui::BeginGroup();
    ImVec2 groupMin = ImGui::GetCursorScreenPos();

    RectangleInt uv = RectangleInt(0, 0, m_folderTexture->Size().GetX(), m_folderTexture->Size().GetY());
    RectangleInt screen = RectangleInt(0, 0, size, size);
    m_folderTexture->Draw(uv, screen);

    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        position.x,
        position.y + static_cast<float>(size) + static_cast<float>(padding)));

    ImGui::PushTextWrapPos(position.x + static_cast<float>(size));
    ImGui::TextWrapped("%s", folder->GetDisplayName().c_str());
    ImGui::PopTextWrapPos();

    ImGui::EndGroup();

    ImVec2 groupMax = ImGui::GetCursorScreenPos();

    groupMax.x = groupMin.x + static_cast<float>(size);

    std::shared_ptr<AssetFolder> returnFolder = {};
    if (ImGui::IsMouseHoveringRect(groupMin, groupMax) &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        Log::Info("Clicked " + folder->GetPackagePath());
        returnFolder = folder;
    }

    return returnFolder;
}

bool AssetTileRender::DrawReturnFolder(
    const std::shared_ptr<AssetFolder>& previousFolder, 
    int size, 
    int padding) const
{
    ImGui::BeginGroup();
    ImVec2 groupMin = ImGui::GetCursorScreenPos();

    RectangleInt uv = RectangleInt(0, 0, m_folderTexture->Size().GetX(), m_folderTexture->Size().GetY());
    RectangleInt screen = RectangleInt(0, 0, size, size);
    m_upFolderTexture->Draw(uv, screen);

    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        position.x,
        position.y + static_cast<float>(size) + static_cast<float>(padding)));

    ImGui::PushTextWrapPos(position.x + static_cast<float>(size));
    ImGui::TextWrapped("%s", previousFolder->GetDisplayName().c_str());
    ImGui::PopTextWrapPos();

    ImGui::EndGroup();

    ImVec2 groupMax = ImGui::GetCursorScreenPos();

    groupMax.x = groupMin.x + static_cast<float>(size);

    bool doReturn = false;
    if (ImGui::IsMouseHoveringRect(groupMin, groupMax) &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        // Remove this and move the bool.
        Log::Info("Returning to " + previousFolder->GetPackagePath());
        doReturn = true;
    }

    return doReturn;
}

std::shared_ptr<AssetFile> AssetTileRender::DrawFile(
    const std::shared_ptr<AssetFile>& file,
    int size,
    int padding) const
{
    ImGui::BeginGroup();
    ImVec2 groupMin = ImGui::GetCursorScreenPos();

    RectangleInt screen = RectangleInt(0, 0, size, size);
    file->DrawLargeTile(screen);

    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        position.x,
        position.y + static_cast<float>(size) + static_cast<float>(padding)));

    ImGui::PushTextWrapPos(position.x + static_cast<float>(size));
    ImGui::TextWrapped("%s", file->GetDisplayName().c_str());
    ImGui::PopTextWrapPos();

    ImGui::EndGroup();

    ImVec2 groupMax = ImGui::GetCursorScreenPos();

    groupMax.x = groupMin.x + static_cast<float>(size);

    std::shared_ptr<AssetFile> returnFile = {};
    if (ImGui::IsMouseHoveringRect(groupMin, groupMax) &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        Log::Info("Clicked " + file->GetPackagePath());
        returnFile = file;
    }

    return returnFile;
}
