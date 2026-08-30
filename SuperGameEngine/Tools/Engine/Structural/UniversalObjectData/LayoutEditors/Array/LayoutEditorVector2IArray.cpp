#include "LayoutEditorVector2IArray.h"
#include "../../../../../ImGuiIncludes.h"
#include "../../../../../../../FatedQuest.Libraries/StandardObjects//AllReferences.h"
#include "../../../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "Engine/Structural/UniversalObjectData/LayoutEditors/LayoutRequirements.h"


using namespace SuperGameTools;
using namespace FatedQuestLibraries;

LayoutEditorVector2IArray::LayoutEditorVector2IArray(const std::string& map, const std::shared_ptr<LayoutRequirements>& layoutRequirements)
{
    m_map = map;
    m_layoutRequirements = layoutRequirements;
}

LayoutEditorVector2IArray::~LayoutEditorVector2IArray()
{
}

void LayoutEditorVector2IArray::Update(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
}

void LayoutEditorVector2IArray::Draw(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void LayoutEditorVector2IArray::DrawLabel(
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

void LayoutEditorVector2IArray::DrawValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawValueInTable(universalObjectData, m_map);
}

void LayoutEditorVector2IArray::OnSave(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    // No clean up needed
}

bool LayoutEditorVector2IArray::ShouldShow(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    if (!m_layoutRequirements)
    {
        return true;
    }

    return m_layoutRequirements->ShouldShow(universalObjectData);
}

void LayoutEditorVector2IArray::DrawSingleValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + map;
    ImGui::PushID(id.c_str());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 4));



    if (ImGui::BeginTable("##two_cols", 2, ImGuiTableFlags_SizingFixedFit))
    {
        bool newValue = false;
        int x = 0, y = 0;
        if (std::shared_ptr<FVector2I> value = universalObjectData->GetVector2I(map))
        {
            x = value->GetX();
            y = value->GetY();
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
        ImGui::EndTable();

        if (newValue)
        {
            universalObjectData->SetVector2I(map, x, y);
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopID();
    ImGui::EndGroup();
}

void LayoutEditorVector2IArray::AddEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->SetVector2I(GetFullEntryName(map, arrayIndex), {});
}

void LayoutEditorVector2IArray::RemoveEntry(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->UnsetVector2I(GetFullEntryName(map, arrayIndex));

    size_t i = arrayIndex + 1;
    while (true)
    {
        std::string entryName = GetFullEntryName(map, i);
        if (universalObjectData->IsVector2ILoaded(entryName))
        {
            universalObjectData->SetVector2I(
                GetFullEntryName(map, i - 1),
                *universalObjectData->GetVector2I(entryName));
            universalObjectData->UnsetVector2I(entryName);
        }
        else
        {
            break;
        }

        ++i;
    }
}

bool LayoutEditorVector2IArray::DoesObjectContain(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData,
    size_t arrayIndex) const
{
    return universalObjectData->IsVector2ILoaded(GetFullEntryName(m_map, arrayIndex));
}

bool LayoutEditorVector2IArray::TextInput(const std::string& label, std::string& value) const
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
