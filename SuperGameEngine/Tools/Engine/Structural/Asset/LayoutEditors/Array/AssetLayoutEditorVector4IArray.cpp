#include "AssetLayoutEditorVector4IArray.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../../ImGuiIncludes.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorVector4IArray::AssetLayoutEditorVector4IArray(
    const std::string& map)
{
    m_map = map;
}

AssetLayoutEditorVector4IArray::~AssetLayoutEditorVector4IArray()
{

}

void AssetLayoutEditorVector4IArray::Update(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorVector4IArray::Draw(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void AssetLayoutEditorVector4IArray::DrawLabel(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Label_" + m_map;
    ImGui::PushID(id.c_str());

    // Label
    ImGui::Text(m_map.c_str());

    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorVector4IArray::DrawValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawValueInTable(universalObjectData, m_map);
}

void AssetLayoutEditorVector4IArray::OnSave(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    // No clean up needed
}

void AssetLayoutEditorVector4IArray::DrawSingleValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + map;
    ImGui::PushID(id.c_str());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 4));



    if (ImGui::BeginTable("##four_cols", 4, ImGuiTableFlags_SizingFixedFit))
    {
        bool newValue = false;
        int x = 0, y = 0, z = 0, w = 0;
        if (std::shared_ptr<FVector4I> value = universalObjectData->GetVector4I(map))
        {
            x = value->GetX();
            y = value->GetY();
            z = value->GetZ();
            w = value->GetW();
        }

        ImGui::TableNextColumn();
        ImGui::PushID("##xCol");

        std::string xString = std::to_string(x);
        if (TextInput("x", xString))
        {
            int attemptedParse = -1;
            if (IntHelpers::TryParse(xString, attemptedParse))
            {
                x = attemptedParse;
                newValue = true;
            }
        }

        ImGui::PopID();
        ImGui::TableNextColumn();
        ImGui::PushID("##yCol");

        std::string yString = std::to_string(y);
        if (TextInput("y", yString))
        {
            int attemptedParse = -1;
            if (IntHelpers::TryParse(yString, attemptedParse))
            {
                y = attemptedParse;
                newValue = true;
            }
        }

        ImGui::PopID();
        ImGui::TableNextColumn();
        ImGui::PushID("##zCol");

        std::string zString = std::to_string(z);
        if (TextInput("z", zString))
        {
            int attemptedParse = -1;
            if (IntHelpers::TryParse(zString, attemptedParse))
            {
                z = attemptedParse;
                newValue = true;
            }
        }

        ImGui::PopID();
        ImGui::TableNextColumn();
        ImGui::PushID("##wCol");

        std::string wString = std::to_string(w);
        if (TextInput("w", wString))
        {
            int attemptedParse = -1;
            if (IntHelpers::TryParse(wString, attemptedParse))
            {
                w = attemptedParse;
                newValue = true;
            }
        }

        ImGui::PopID();
        ImGui::EndTable();

        if (newValue)
        {
            universalObjectData->SetVector4I(map, x, y, z, w);
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopID();
    ImGui::EndGroup();
}

void AssetLayoutEditorVector4IArray::AddEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->SetVector4I(GetFullEntryName(map, arrayIndex), {});
}

void AssetLayoutEditorVector4IArray::RemoveEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->UnsetVector4I(GetFullEntryName(map, arrayIndex));

    size_t i = arrayIndex + 1;
    while (true)
    {
        std::string entryName = GetFullEntryName(map, i);
        if (universalObjectData->IsVector4ILoaded(entryName))
        {
            universalObjectData->SetVector4I(
                GetFullEntryName(map, i - 1),
                *universalObjectData->GetVector4I(entryName));
            universalObjectData->UnsetVector4I(entryName);
        }
        else
        {
            break;
        }

        ++i;
    }
}

bool AssetLayoutEditorVector4IArray::DoesObjectContain(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    return universalObjectData->IsVector4ILoaded(GetFullEntryName(m_map, arrayIndex));
}

bool AssetLayoutEditorVector4IArray::TextInput(const std::string& label, std::string& value) const
{
    const std::string before = value;
    char* charValue = new char[m_defaultTextCapacity];
    size_t written = std::snprintf(charValue, m_defaultTextCapacity, "%s", value.c_str());

    ImGui::PushItemWidth(50);

    const std::string textLabel = "##labelName_" + label;
    ImGui::InputText(textLabel.c_str(), charValue, m_defaultTextCapacity, ImGuiInputTextFlags_CharsDecimal);
    const std::string& after = charValue;

    ImGui::PopItemWidth();

    delete[] charValue;

    value = after;
    return before != after;
}
