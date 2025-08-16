#include "AssetLayoutEditorVector4I.h"
#include "../../../../FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../ImGuiIncludes.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorVector4I::AssetLayoutEditorVector4I(const std::string& map)
{
    m_map = map;
}

AssetLayoutEditorVector4I::~AssetLayoutEditorVector4I()
{
}

void AssetLayoutEditorVector4I::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorVector4I::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void AssetLayoutEditorVector4I::DrawLabel(
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

void AssetLayoutEditorVector4I::DrawValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
    ImGui::PushID(id.c_str());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 4));



    if (ImGui::BeginTable("##four_cols", 4, ImGuiTableFlags_SizingFixedFit))
    {
        bool newValue = false;
        int x = 0, y = 0, z = 0, w = 0;
        if (std::shared_ptr<FVector4I> value = universalObjectData->GetVector4I(m_map))
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
            universalObjectData->SetVector4I(m_map, x, y, z, w);
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopID();
    ImGui::EndGroup();
}

bool AssetLayoutEditorVector4I::TextInput(const std::string& label, std::string& value) const
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
