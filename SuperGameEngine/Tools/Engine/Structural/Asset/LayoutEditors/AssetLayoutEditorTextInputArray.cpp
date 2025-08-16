#include "AssetLayoutEditorTextInputArray.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../ImGuiIncludes.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorTextInputArray::AssetLayoutEditorTextInputArray(const std::string& map)
{
    m_map = map;
}

AssetLayoutEditorTextInputArray::~AssetLayoutEditorTextInputArray()
{
}

void AssetLayoutEditorTextInputArray::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorTextInputArray::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorTextInputArray::DrawLabel(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Label_" + m_map;
    ImGui::PushID(id.c_str());

    // Label
    ImGui::Text(m_map.c_str());

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorTextInputArray::DrawValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
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

            if (universalObjectData->IsStringLoaded(GetFullEntryName(i)))
            {
                if (!DrawSingleArrayValue(universalObjectData, i))
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
        AddEntry(universalObjectData, i);
    }

    if (userWouldLikeToDeleteEntry)
    {
        RemoveEntry(universalObjectData, deleteIndex);
    }

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorTextInputArray::OnSave(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
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
            std::string currentName = GetFullEntryName(i);
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
            RemoveEntry(universalObjectData, i);
        }

    } while (foundBlankEntry);
}

bool AssetLayoutEditorTextInputArray::DrawSingleArrayValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    ImGui::BeginGroup();

    std::string map = GetFullEntryName(arrayIndex);
    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + map;
    ImGui::PushID(id.c_str());

    // Label
    const std::string arrayElementLabel = std::to_string(arrayIndex);
    ImGui::Text(arrayElementLabel.c_str());
    ImGui::TableNextColumn();

    std::string value = universalObjectData->GetString(map);
    if (value.size() + 1 > m_defaultTextCapacity)
    {
        // TODO: Revisit the array resizing but ensure that we do not create separate object.
        Log::Error("String within an Asset is bigger than the text size. "
            "Consider raising it. Limit: " + std::to_string(m_defaultTextCapacity),
            "AssetLayoutEditorTextInput::Draw(const std::shared_ptr<ModifiableUniversalObjectData>&)");
    }

    char* charValue = new char[m_defaultTextCapacity];
    size_t written = std::snprintf(charValue, m_defaultTextCapacity, "%s", value.c_str());

    std::string textLabel = "##value_" + map;
    std::string before = charValue;
    ImGui::PushItemWidth(-1);
    ImGui::InputText(textLabel.c_str(), charValue, m_defaultTextCapacity);
    ImGui::PopItemWidth();
    std::string after = charValue;

    delete[] charValue;

    if (before != after)
    {
        universalObjectData->SetString(map, after);
    }

    ImGui::TableNextColumn();
    bool deleteEntry = ImGui::Button("-");

    ImGui::PopID();
    ImGui::EndGroup();

    return !deleteEntry;
}

void AssetLayoutEditorTextInputArray::AddEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    universalObjectData->SetString(GetFullEntryName(arrayIndex), {});
}

void AssetLayoutEditorTextInputArray::RemoveEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    universalObjectData->UnsetString(GetFullEntryName(arrayIndex));

    size_t i = arrayIndex + 1;
    while (true)
    {
        std::string entryName = GetFullEntryName(i);
        if (universalObjectData->IsStringLoaded(entryName))
        {
            universalObjectData->SetString(
                GetFullEntryName(i - 1), 
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

std::string AssetLayoutEditorTextInputArray::GetFullEntryName(size_t index) const
{
    return m_map + std::to_string(index);
}
