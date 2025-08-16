#include "AssetLayoutEditorArray.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../../ImGuiIncludes.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

void AssetLayoutEditorArray::DrawValueInTable(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + map;
    ImGui::PushID(id.c_str());

    size_t deleteIndex = 0;
    bool userWouldLikeToDeleteEntry = false;
    size_t i = 0;

    if (ImGui::BeginTable("##table", 3,
        ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings
    ))
    {
        ImVec2 table_size = ImGui::GetItemRectSize();

        ImGui::TableSetupColumn("##Column0", ImGuiTableColumnFlags_WidthFixed,
            35);

        ImGui::TableSetupColumn("##Column1",
            ImGuiTableColumnFlags_WidthStretch
        );

        ImGui::TableSetupColumn("##Column2",
            ImGuiTableColumnFlags_WidthFixed,
            20
        );

        while (true)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();

            if (universalObjectData->IsStringLoaded(GetFullEntryName(map, i)))
            {
                if (!DrawASingleRow(universalObjectData, i, map))
                {
                    userWouldLikeToDeleteEntry = true;
                    deleteIndex = i;
                }
            }
            else
            {
                break;
            }

            ++i;
        }

        ImGui::EndTable();
    }

    if (ImGui::Button("Add"))
    {
        AddEntry(universalObjectData, i, map);
    }

    if (userWouldLikeToDeleteEntry)
    {
        RemoveEntry(universalObjectData, deleteIndex, map);
    }

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorArray::OnSaveCleanUpArray(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
    // Blank string are not saved. Jumps in the indexes are not recognised.
    // We must therefore remove blanks and shift values to clean the data.

    bool foundBlankEntry = false;
    do
    {
        foundBlankEntry = false;
        size_t i = 0;
        while (true)
        {
            std::string currentName = GetFullEntryName(map, i);
            if (universalObjectData->IsStringLoaded(currentName))
            {
                if (universalObjectData->GetString(currentName).empty())
                {
                    foundBlankEntry = true;
                    break;
                }
            }
            else
            {
                break;
            }

            ++i;
        }

        if (foundBlankEntry)
        {
            RemoveEntry(universalObjectData, i, map);
        }

    } while (foundBlankEntry);
}

bool AssetLayoutEditorArray::DrawASingleRow(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData, 
    size_t arrayIndex,
    const std::string& map) const
{
    ImGui::BeginGroup();

    std::string fullMap = GetFullEntryName(map, arrayIndex);
    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + fullMap;
    ImGui::PushID(id.c_str());

    // Label
    const std::string arrayElementLabel = std::to_string(arrayIndex);
    ImGui::Text(arrayElementLabel.c_str());
    ImGui::TableNextColumn();

    // Draws the Text Box, or Vector or Dropdown... the actual input.
    DrawSingleValue(universalObjectData, fullMap);

    // Now the extra controls
    ImGui::TableNextColumn();
    bool deleteEntry = ImGui::Button("-");

    ImGui::PopID();
    ImGui::EndGroup();

    return !deleteEntry;
}

void AssetLayoutEditorArray::AddEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->SetString(GetFullEntryName(map, arrayIndex), {});
}

void AssetLayoutEditorArray::RemoveEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->UnsetString(GetFullEntryName(map, arrayIndex));

    size_t i = arrayIndex + 1;
    while (true)
    {
        std::string entryName = GetFullEntryName(map, i);
        if (universalObjectData->IsStringLoaded(entryName))
        {
            universalObjectData->SetString(
                GetFullEntryName(map, i - 1),
                universalObjectData->GetString(entryName));
            universalObjectData->UnsetString(entryName);
        }
        else
        {
            break;
        }

        ++i;
    }
}

std::string AssetLayoutEditorArray::GetFullEntryName(const std::string& map, size_t index) const
{
    return map + std::to_string(index);
}
