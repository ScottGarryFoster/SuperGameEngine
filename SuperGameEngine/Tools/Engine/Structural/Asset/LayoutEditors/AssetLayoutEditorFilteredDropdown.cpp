#include "AssetLayoutEditorFilteredDropdown.h"
#include "../../../../ImGuiIncludes.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "Imgui/External/imgui_internal.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorFilteredDropdown::AssetLayoutEditorFilteredDropdown(
    const std::string& map,
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

AssetLayoutEditorFilteredDropdown::~AssetLayoutEditorFilteredDropdown()
{
}

void AssetLayoutEditorFilteredDropdown::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorFilteredDropdown::Draw(
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

void AssetLayoutEditorFilteredDropdown::DrawLabel(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Label_" + m_map;
    ImGui::PushID(id.c_str());

    ImGui::Text(m_map.c_str());

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorFilteredDropdown::DrawValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
    ImGui::PushID(id.c_str());

    std::string currentValue = universalObjectData->GetString(m_map);
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
            Log::Error("Selected item is outside of the range of this enum, setting nothing. Map: " + m_map + " Selected Item Index: " + std::to_string(selectedItem),
                "AssetLayoutEditorFilteredDropdown::Draw(const std::shared_ptr<ModifiableUniversalObjectData>&) const");

        }
        else
        {
            std::string newValue = m_values.at(selectedItem);
            universalObjectData->SetString(m_map, newValue);
        }
    }

    ImGui::PopID();
    ImGui::EndGroup();
}