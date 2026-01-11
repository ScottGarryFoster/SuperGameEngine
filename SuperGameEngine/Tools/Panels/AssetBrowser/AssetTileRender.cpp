#include "AssetTileRender.h"

#include "FileManagement/AssetFile.h"
#include "ToolsEngine/ViewElements/ColoursAndStyles/ToolsColoursAndStyles.h"
#include "../../FatedQuestLibraries.h"
#include "../../Engine/Graphics/ImGuiSuperTexture.h"
#include "Engine/Content/ContentManager.h"
#include "FileManagement/AssetFile.h"
#include "FileManagement/AssetFolder.h"
#include "FileManagement/PackageFilesHaveUpdatedEventArguments.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/SelectionChangedEventArguments.h"
#include "ToolsEngine/FrameworkManager/SelectionManager/SelectionManager.h"

using namespace SuperGameTools;
using namespace SuperGameEngine;

AssetTileRender::AssetTileRender(
    const std::shared_ptr<AssetFolder>& rootFolder,
    const std::shared_ptr<SuperGameEngine::TextureManager>& texture,
    const std::shared_ptr<SelectionManager>& selectionManager)
{

    m_folderTexture = texture->GetTexture(R"(Tools\Icons\Folder\Folder-256.png)");
    m_upFolderTexture = texture->GetTexture(R"(Tools\Icons\FolderUp\FolderUp-256.png)");
    m_currentFolder = rootFolder;
    m_rootFolder = rootFolder;
    m_selectionManager = selectionManager;
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
    int cols = max(1, int(pw / (static_cast<float>(thumbSize) + static_cast<float>(padding) * 3)));

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
            m_selectionManager->SetSelection(fileSelected);
        }

        endColumn(i);
    }

    if (newCurrentFolder)
    {
        m_currentFolder = newCurrentFolder;

    }
}

void AssetTileRender::Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments)
{
    if (auto packageFileUpdate = std::dynamic_pointer_cast<PackageFilesHaveUpdatedEventArguments>(arguments))
    {
        std::string cachedCurrentPath = m_currentFolder->GetPackagePath();

        // Ensure we keep the selection from the current files and folders we are rendering.
        //std::vector<std::shared_ptr<AssetFile>> selectedFiles;
        std::unordered_set<std::string> packagePaths;
        for (const std::shared_ptr<AssetFile>& file : m_currentFolder->GetContainingFiles())
        {
            if (file->IsSelected())
            {
                packagePaths.insert(file->GetPackagePath());
            }
        }

        // Note that from this point we should consider the files and folders from the previous
        // load gone...
        m_rootFolder = packageFileUpdate->GetNewRoot();
        if (cachedCurrentPath.empty())
        {
            m_currentFolder = m_rootFolder;
            return;
        }

        // If the current folder is not root attempt to remain where we were.
        std::vector<std::string> directories = StringHelpers::Split(cachedCurrentPath, "\\");
        std::string currentPath = {};
        std::shared_ptr<AssetFolder> currentFolder = m_rootFolder;
        for (const std::string& currentDirectoryName : directories)
        {
            bool foundFolder = false;
            std::string testPath = Directory::CombinePath(currentPath, currentDirectoryName);
            for (const std::shared_ptr<AssetFolder>& folder : currentFolder->GetContainingFolders())
            {
                if (folder->GetPackagePath() == testPath)
                {
                    foundFolder = true;
                    currentFolder = folder;
                }
            }

            // Folder must no longer exist. End here
            if (!foundFolder)
            {
                break;
            }

            currentPath = testPath;
        }

        m_currentFolder = currentFolder;

        if (cachedCurrentPath == m_currentFolder->GetPackagePath())
        {
            std::vector<std::weak_ptr<Selectable>> currentVersionOfSelectedFiles;
            for (const std::shared_ptr<AssetFile>& file : m_currentFolder->GetContainingFiles())
            {
                if (packagePaths.contains(file->GetPackagePath()))
                {
                    currentVersionOfSelectedFiles.emplace_back(file);
                }
            }

            m_selectionManager->SetSelection(currentVersionOfSelectedFiles);
        }
    }
    else if (auto selectionArguments = std::dynamic_pointer_cast<SelectionChangedEventArguments>(arguments))
    {
        std::unordered_set<std::shared_ptr<const Guid>> guids = selectionArguments->GetAllSelectableGuids();
        for (const std::shared_ptr<AssetFile>& asset : m_currentFolder->GetContainingFiles())
        {
            if (guids.contains(asset->GetGuid()))
            {
                asset->SelectFile();
            }
            else
            {
                asset->UnselectFile();
            }
        }
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
    float paddingFloat = static_cast<float>(padding);
    float halfPadding = paddingFloat / 2;

    ImVec2 beforeEverything = ImGui::GetCursorScreenPos();
    ImGui::BeginGroup();

    // We need to draw the selection rectangle now but we do not know
    // how big it is going to be. So we split the draw list, and then
    // come back and merge later. 
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->ChannelsSplit(3);
    drawList->ChannelsSetCurrent(2);

    // The exact top left of the tile.
    ImVec2 topLeft = ImGui::GetCursorScreenPos();

    RectangleInt screen = RectangleInt(halfPadding, halfPadding, size, size);
    file->DrawLargeTile(screen);

    // Set the position for the text
    ImVec2 position = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(
        topLeft.x + halfPadding,
        position.y + static_cast<float>(size) + static_cast<float>(padding)));

    // Draw the actual text.
    ImGui::PushTextWrapPos(position.x + static_cast<float>(size) + static_cast<float>(padding));
    ImGui::TextWrapped("%s", file->GetDisplayName().c_str());
    ImGui::PopTextWrapPos();

    ImGui::EndGroup();

    // The main content end (as this is after the text)
    ImVec2 groupMax = ImGui::GetCursorScreenPos();
    groupMax.x = topLeft.x + static_cast<float>(size);

    // Bottom right is the actual bottom right including any padding.
    auto bottomRight = ImVec2(topLeft.x + static_cast<float>(size) + static_cast<float>(padding) + static_cast<float>(halfPadding),
        groupMax.y + static_cast<float>(halfPadding));
    if (file->IsSelected())
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


    // Drag and Drop behaviour
    {
        ImVec2 before = ImGui::GetCursorScreenPos();
        float ySize = bottomRight.y - topLeft.y;
        auto topLeftAsset = ImVec2(before.x, before.y - ySize);

        auto bottom = ImVec2(topLeftAsset.x + static_cast<float>(size) + static_cast<float>(padding) + static_cast<float>(halfPadding),
            topLeftAsset.y + (bottomRight.y - topLeft.y));
        EnableDropTarget(file->GetPackagePath(), topLeftAsset.x, topLeftAsset.y, bottom.x, bottom.y);
        ImGui::SetCursorScreenPos(before);
    }

    UpdateInteractionStateForFileTile(file, ImGui::IsMouseHoveringRect(topLeft, bottomRight));

    AssetTileInteractionRawState currentState = file->GetAssetTileInteractionRawState();
    auto haveState = [currentState](AssetTileInteractionRawState state)
        { return EAssetTileInteractionRawState::HasFlag(currentState, state); };

    std::shared_ptr<AssetFile> returnFile = {};
    if (haveState(AssetTileInteractionRawState::Hover))
    {
        if (haveState(AssetTileInteractionRawState::LeftClickReleased))
        {
            Log::Info("Clicked " + file->GetPackagePath());
            returnFile = file;

            // Note: Do not attempt to draw a frame here, it will just flash
            // probably not a good idea.
        }
        else if (haveState(AssetTileInteractionRawState::LeftClickDown))
        {
            // Draw on mouse down but not click complete
            drawList->ChannelsSetCurrent(1);

            // Fill
            drawList->AddRectFilled(
                topLeft,
                bottomRight,
                IM_COL32(44, 0, 74, 255),
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
        else
        {
            // Draw a for mouse over
            drawList->ChannelsSetCurrent(1);

            // Border
            drawList->AddRect(
                topLeft,
                bottomRight,
                IM_COL32(62, 184, 0, 255),
                5.0f,
                ImDrawFlags_None,
                2.0f);
        }
    }

    drawList->ChannelsMerge();
    return returnFile;
}

void AssetTileRender::EnableDropTarget(
    const std::string& packagePath, 
    float xTop, 
    float yTop, 
    float xBottom,
    float yBottom) const
{
    auto top = ImVec2(xTop, xTop);
    auto bottom = ImVec2(xBottom, yBottom);
    auto size = ImVec2(bottom.x - top.x, bottom.y - top.y);
    ImGui::SetCursorScreenPos(top);

    ImGui::InvisibleButton("##drag_area", size);
    if (ImGui::BeginDragDropSource())
    {
        const std::string payload = File::RemoveLastExtension(packagePath);

        ImGui::SetDragDropPayload("AssetPackagePath",
            payload.c_str(),
            strlen(payload.c_str()) + 1);

        ImGui::TextUnformatted(payload.c_str());

        ImGui::EndDragDropSource();
    }
}

void AssetTileRender::UpdateInteractionStateForFileTile(const std::shared_ptr<AssetFile>& file, bool areHovering) const
{
    AssetTileInteractionRawState currentState = file->GetAssetTileInteractionRawState();
    auto stateContainsHover = [currentState]()
        { return EAssetTileInteractionRawState::HasFlag(currentState, AssetTileInteractionRawState::Hover); };
    auto stateContainsClick = [currentState]()
        { return EAssetTileInteractionRawState::HasFlag(currentState, AssetTileInteractionRawState::LeftClickDown); };

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !stateContainsHover())
    {
        file->SetAssetTileInteractionRawState(AssetTileInteractionRawState::NoInteraction);
    }
    else if (areHovering)
    {
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            file->SetAssetTileInteractionRawState(AssetTileInteractionRawState::Hover | AssetTileInteractionRawState::LeftClickDown);
        }
        else
        {
            if (stateContainsClick())
            {
                file->SetAssetTileInteractionRawState(
                    AssetTileInteractionRawState::Hover | AssetTileInteractionRawState::LeftClickReleased);
            }
            else
            {
                file->SetAssetTileInteractionRawState(
                    AssetTileInteractionRawState::Hover);
            }

        }
    }
    else
    {
        file->SetAssetTileInteractionRawState(AssetTileInteractionRawState::NoInteraction);
    }
}
