#include "LayoutEditorAssetLink.h"

#include "LayoutRequirements.h"
#include "../../../../ImGuiIncludes.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects//AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/StandardOperations/AllReferences.h"
#include "../../../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

LayoutEditorAssetLink::LayoutEditorAssetLink(const std::string& map,
    const std::shared_ptr<LayoutRequirements>& layoutRequirements)
{
    m_map = map;
    m_layoutRequirements = layoutRequirements;
}

LayoutEditorAssetLink::~LayoutEditorAssetLink()
{
}

void LayoutEditorAssetLink::Update(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
}

void LayoutEditorAssetLink::Draw(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    DrawLabel(universalObjectData);
    ImGui::SameLine();
    DrawValue(universalObjectData);
}

void LayoutEditorAssetLink::DrawLabel(
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

void LayoutEditorAssetLink::DrawValue(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    ImGui::BeginGroup();
    ImVec2 beforePosition = ImGui::GetCursorScreenPos();
    
    std::string id = universalObjectData->GetGuid()->ToString() + "_Value_" + m_map;
    ImGui::PushID(id.c_str());

    std::string value = universalObjectData->GetString(m_map);
    if (value.size() + 1 > m_defaultTextCapacity)
    {
        // TODO: Revisit the array resizing but ensure that we do not create separate object.
        Log::Error("String within an Asset is bigger than the text size. "
            "Consider raising it. Limit: " + std::to_string(m_defaultTextCapacity),
            "LayoutEditorTextInput::Draw(const std::shared_ptr<ModifiableUniversalObjectData>&)");
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
    
    ImVec2 afterPosition = ImGui::GetCursorScreenPos();
    EnableDropTarget(beforePosition.x, beforePosition.y, 
        afterPosition.x, afterPosition.y, 
        universalObjectData);
    
    ImGui::PopID();
    ImGui::EndGroup();
}

bool LayoutEditorAssetLink::ShouldShow(
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    if (!m_layoutRequirements)
    {
        return true;
    }

    return m_layoutRequirements->ShouldShow(universalObjectData);
}

void LayoutEditorAssetLink::EnableDropTarget(float xTop, float yTop, float xBottom, float yBottom,
    const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const
{
    // Try to make a box which encapsulates the element.
    // We use the 'before' 'after' and window (before width can be weird)
    // To align a drag area.
    auto before = ImVec2(xTop, yTop);
    auto after = ImVec2(xBottom, yBottom);
    ImVec2 windowSize = ImGui::GetWindowSize();
    auto size = ImVec2(windowSize.x - 16, after.y - before.y - 7);
    auto position = ImVec2(before.x, before.y + 2);
    ImGui::SetCursorScreenPos(position);

    // Create drag behaviour over the area. Set this to button if you think the area is wrong (to see the area)
    ImGui::InvisibleButton("##drag_area", size);
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AssetPackagePath"))
        {
            std::string originalValue = universalObjectData->GetString(m_map);
            const char* droppedData = static_cast<const char*>(payload->Data);
            if (strlen(droppedData) > m_defaultTextCapacity)
            {
                Log::Error("Dragged and drop variable name too long. "
                           "Cannot be longer than: " + std::to_string(m_defaultTextCapacity),
                    "TextureAssetSerializableProperty");
            }
            
            if (!StringHelpers::Equals(originalValue,droppedData, CaseSensitivity::IgnoreCase))
            {
                universalObjectData->SetString(m_map, droppedData);
            }
        }
        
        ImGui::EndDragDropTarget();
    }
}
