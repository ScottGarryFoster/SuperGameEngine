#include "LayoutEditorUserButtonInput.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../ImGuiIncludes.h"
#include "../../../../../Input/InputManagement/Engine/KeyCode.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

LayoutEditorUserButtonInput::LayoutEditorUserButtonInput(const std::string& map)
{
    m_map = map;
}

LayoutEditorUserButtonInput::~LayoutEditorUserButtonInput()
{
}

void LayoutEditorUserButtonInput::Update(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{

}

void LayoutEditorUserButtonInput::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void LayoutEditorUserButtonInput::DrawLabel(
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

void LayoutEditorUserButtonInput::DrawValue(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
    ImGui::PushID(id.c_str());

    // Button and doing stuff here
    std::string value = universalObjectData->GetString(m_map);
    const std::vector<std::string>& items = SuperGameInput::EKeyCode::ToVectorValues();

    int selectedIndex = 0;
    if (auto it = std::find(items.begin(), items.end(), value); it != items.end())
    {
        selectedIndex = static_cast<int>(it - items.begin());
    }

    bool isSelectedChanged = false;
    std::string idCombo = universalObjectData->GetGuid()->ToString() + "_ValueCombo_" + m_map;
    if (ImGui::BeginCombo(idCombo.c_str(), SuperGameInput::EKeyCode::ToVectorValues().at(selectedIndex).c_str()))
    {
        for (int i = 0; i < SuperGameInput::EKeyCode::ToVectorValues().size(); ++i)
        {
            bool isSelected = (selectedIndex == i);

            if (ImGui::Selectable(SuperGameInput::EKeyCode::ToVectorValues().at(i).c_str(), isSelected))
            {
                selectedIndex = i;
                isSelectedChanged = true;
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    if (isSelectedChanged)
    {
        universalObjectData->SetString(m_map, SuperGameInput::EKeyCode::ToVectorValues().at(selectedIndex));
    }

    ImGui::PopID();
    ImGui::EndGroup();
}
