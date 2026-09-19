#include "LayoutEditorVector2I.h"

#include "LayoutRequirements.h"
#include "../../../../ImGuiIncludes.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects//AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"


using namespace SuperGameTools;
using namespace FatedQuestLibraries;

LayoutEditorVector2I::LayoutEditorVector2I(const std::string& map, const std::shared_ptr<LayoutRequirements>& layoutRequirements)
{
    m_map = map;
    m_layoutRequirements = layoutRequirements;
}

LayoutEditorVector2I::~LayoutEditorVector2I()
{
}

void LayoutEditorVector2I::Update(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void LayoutEditorVector2I::Draw(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void LayoutEditorVector2I::DrawLabel(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Label_" + m_map;
    ImGui::PushID(id.c_str());

    // Label
    ImGui::Text(m_map.c_str());

    ImGui::PopID();
    ImGui::EndGroup();
}

void LayoutEditorVector2I::DrawValue(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
    ImGui::PushID(id.c_str());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 4));



    if (ImGui::BeginTable("##two_cols", 2, ImGuiTableFlags_SizingFixedFit))
    {
        bool newValue = false;
        int x = 0, y = 0, z = 0, w = 0;
        if (std::shared_ptr<FVector2I> value = universalObjectData->GetVector2I(m_map))
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
            universalObjectData->SetVector2I(m_map, x, y);
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopID();
    ImGui::EndGroup();
}

bool LayoutEditorVector2I::ShouldShow(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    if (!m_layoutRequirements)
    {
        return true;
    }

    return m_layoutRequirements->ShouldShow(universalObjectData);
}

bool LayoutEditorVector2I::TextInput(const std::string& label, std::string& value) const
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
