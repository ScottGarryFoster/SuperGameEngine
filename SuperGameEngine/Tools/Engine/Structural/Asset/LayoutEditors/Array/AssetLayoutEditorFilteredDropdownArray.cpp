#include "AssetLayoutEditorFilteredDropdownArray.h"
#include "../../../../../ImGuiIncludes.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorFilteredDropdownArray::AssetLayoutEditorFilteredDropdownArray(const std::string& map,
    const std::vector<std::string>& values)
{
    m_map = map;
    m_values = values;
    if (values.empty())
    {
        return;
    }

    int i = 0;
    m_valuesChars.reserve(m_values.size());
    for (const std::string& value : m_values)
    {
        m_valuesChars.push_back(value.c_str());
        m_valuesValueByIndex.insert_or_assign(value, i);
        ++i;
    }
}

AssetLayoutEditorFilteredDropdownArray::~AssetLayoutEditorFilteredDropdownArray()
{
}

void AssetLayoutEditorFilteredDropdownArray::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorFilteredDropdownArray::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_" + m_map;
    ImGui::PushID(id.c_str());

    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorFilteredDropdownArray::DrawLabel(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Label_" + m_map;
    ImGui::PushID(id.c_str());

    ImGui::Text(m_map.c_str());

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorFilteredDropdownArray::DrawValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawValueInTable(universalObjectData, m_map);
}

void AssetLayoutEditorFilteredDropdownArray::OnSave(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    // Ensure there is a value for anything in the list.
    // Should never occur but just in case.

    size_t i = 0;
    while (true)
    {
        std::string entryName = GetFullEntryName(m_map, i);
        if (universalObjectData->IsStringLoaded(entryName))
        {
            if (universalObjectData->GetString(entryName).empty())
            {
                universalObjectData->SetString(entryName, m_values.at(0));
            }
        }
        else
        {
            break;
        }

        ++i;
    }
}

void AssetLayoutEditorFilteredDropdownArray::DrawSingleValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + map;
    ImGui::PushID(id.c_str());
    ImGui::PushItemWidth(-1);

    std::string currentValue = universalObjectData->GetString(map);
    int selectedItem = -1;
    if (m_valuesValueByIndex.contains(currentValue))
    {
        selectedItem = m_valuesValueByIndex.at(currentValue);
    }
    else
    {
        selectedItem = 0;
    }

    if (ImGui::Combo(
        "##combo",
        &selectedItem,
        m_valuesChars.data(),
        static_cast<int>(m_values.size())
    ))
    {
        if (m_values.size() <= selectedItem)
        {
            Log::Error("Selected item is outside of the range of this enum, setting nothing. Map: " + map + " Selected Item Index: " + std::to_string(selectedItem),
                "AssetLayoutEditorFilteredDropdown::Draw(const std::shared_ptr<ModifiableUniversalObjectData>&) const");

        }
        else
        {
            std::string newValue = m_values.at(selectedItem);
            universalObjectData->SetString(map, newValue);
        }
    }

    ImGui::PopItemWidth();
    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorFilteredDropdownArray::AddEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->SetString(GetFullEntryName(map, arrayIndex), m_values.at(0));
}

void AssetLayoutEditorFilteredDropdownArray::RemoveEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex,
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

bool AssetLayoutEditorFilteredDropdownArray::DoesObjectContain(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    return universalObjectData->IsStringLoaded(GetFullEntryName(m_map, arrayIndex));
}
