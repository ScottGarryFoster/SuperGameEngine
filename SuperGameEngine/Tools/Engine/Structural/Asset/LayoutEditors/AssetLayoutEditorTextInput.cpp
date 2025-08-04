#include "AssetLayoutEditorTextInput.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../ImGuiIncludes.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorTextInput::AssetLayoutEditorTextInput(const std::string& map)
{
    Log::Info("Create AssetLayoutEditorTextInput");
    m_map = map;
}

AssetLayoutEditorTextInput::~AssetLayoutEditorTextInput()
{
}

void AssetLayoutEditorTextInput::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorTextInput::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();

    std::string id = universalObjectData->GetGuid()->ToString() + "_" + m_map;
    ImGui::PushID(id.c_str());

    // Label
    ImGui::Text(m_map.c_str());
    ImGui::SameLine();

    std::string value = universalObjectData->GetString(m_map);
    if (value.size() + 1 > m_defaultTextCapacity)
    {
        // TODO: Revisit the array resizing but ensure that we do not create separate object.
        Log::Error("String within an Asset is bigger than the text size. "
                   "Consider raising it. Limit: " + std::to_string(m_defaultTextCapacity),
            "AssetLayoutEditorTextInput::Draw(const std::shared_ptr<ModifiableUniversalObjectData>&)");
    }

    char* charValue = new char[m_defaultTextCapacity];
    size_t written = std::snprintf(charValue, m_defaultTextCapacity, "%s", value.c_str());

    std::string before = charValue;
    ImGui::InputText("##labelName", charValue, m_defaultTextCapacity);
    std::string after = charValue;

    delete[] charValue;

    if (before != after)
    {
        universalObjectData->SetString(m_map, after);
    }

    ImGui::PopID();
    ImGui::EndGroup();
}