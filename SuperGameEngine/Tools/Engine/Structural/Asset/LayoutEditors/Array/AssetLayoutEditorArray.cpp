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

            if (DoesObjectContain(universalObjectData, i))
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

std::string AssetLayoutEditorArray::GetFullEntryName(const std::string& map, size_t index) const
{
    return map + std::to_string(index);
}
