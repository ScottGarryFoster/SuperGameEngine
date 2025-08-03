#include "AssetLayoutEditorTextInput.h"
#include "FatedQuestLibraries.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

AssetLayoutEditorTextInput::AssetLayoutEditorTextInput(const std::string& map)
{
    Log::Info("Create AssetLayoutEditorTextInput");
    m_map = map;
}

void AssetLayoutEditorTextInput::Update(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
}

void AssetLayoutEditorTextInput::Draw(
    const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    if (1 == 1)
    {
        
    }
}