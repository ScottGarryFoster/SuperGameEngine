#include "AssetLayoutEditorTextInputArray.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/ModifiableUniversalObjectData.h"
#include "../../../../../ImGuiIncludes.h"

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
    DrawValueInTable(universalObjectData, m_map);
}

void AssetLayoutEditorTextInputArray::OnSave(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    OnSaveCleanUpArray(universalObjectData, m_map);
}

void AssetLayoutEditorTextInputArray::DrawSingleValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData,
    const std::string& map) const
{
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
}

void AssetLayoutEditorTextInputArray::AddEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
    const std::string& map) const
{
    universalObjectData->SetString(GetFullEntryName(map, arrayIndex), {});
}

void AssetLayoutEditorTextInputArray::RemoveEntry(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData, size_t arrayIndex,
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
