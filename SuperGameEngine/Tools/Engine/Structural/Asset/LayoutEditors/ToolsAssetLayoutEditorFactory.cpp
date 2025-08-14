#include "ToolsAssetLayoutEditorFactory.h"

#include "AssetLayoutEditorFilteredDropdown.h"
#include "AssetLayoutEditorTextInput.h"
#include "AssetLayoutEditorVector4I.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/SharedEnums/Objects/EnumFilterFactory.h"
#include "Engine/Structural/Asset/Template/AssetTemplateLayoutMapType.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

std::shared_ptr<AssetLayoutEditor> ToolsAssetLayoutEditorFactory::Create(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    if (!node)
    {
        return {};
    }

    UniversalStorableType type = ExtractType(node);
    if (type == UniversalStorableType::Unknown)
    {
        Log::Error("Unknown parameter type value in template.",
            "ToolsAssetLayoutEditorFactory::Create(const std::shared_ptr<const StoredDocumentNode>&)");
        return {};
    }

    AssetTemplateLayoutMapType maptype = ExtractMapType(node);
    if (maptype == AssetTemplateLayoutMapType::Unknown)
    {
        Log::Error("Unknown map type value in template.",
            "ToolsAssetLayoutEditorFactory::Create(const std::shared_ptr<const StoredDocumentNode>&)");
        return {};
    }

    std::string map = ExtractMap(node);
    std::vector<std::string> enumFilters = ExtractEnumFilter(node);

    switch (type)
    {
        case UniversalStorableType::String:
            switch (maptype)
            {
                case AssetTemplateLayoutMapType::Single:
                    if (enumFilters.size() == 0)
                    {
                        return std::make_shared<AssetLayoutEditorTextInput>(map);
                    }
                    else
                    {
                        return std::make_shared<AssetLayoutEditorFilteredDropdown>(map, enumFilters);
                    }
            }
            break;
        case UniversalStorableType::Vector4I:
            return std::make_shared<AssetLayoutEditorVector4I>(map);
    }

    Log::Error("Could not create layout for the following combination: " +
        EUniversalStorableType::ToString(type) + " / " + EAssetTemplateLayoutMapType::ToString(maptype),
        "ToolsAssetLayoutEditorFactory::Create(const std::shared_ptr<const StoredDocumentNode>&)");

    return {};
}

UniversalStorableType ToolsAssetLayoutEditorFactory::ExtractType(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    auto universalStorableType = UniversalStorableType::Unknown;
    if (auto mapAttribute = node->Attribute("type", CaseSensitivity::IgnoreCase))
    {
        universalStorableType = EUniversalStorableType::FromString(mapAttribute->Value(), false);
    }

    return universalStorableType;
}

AssetTemplateLayoutMapType ToolsAssetLayoutEditorFactory::ExtractMapType(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    auto mapType = AssetTemplateLayoutMapType::Unknown;
    if (auto mapAttribute = node->Attribute("maptype", CaseSensitivity::IgnoreCase))
    {
        mapType = EAssetTemplateLayoutMapType::FromString(mapAttribute->Value(), false);
        if (mapType == AssetTemplateLayoutMapType::Unknown)
        {
            // Do not set unknown map types to single as this suggests corruption.
            return AssetTemplateLayoutMapType::Unknown;
        }
    }

    if (mapType == AssetTemplateLayoutMapType::Unknown)
    {
        mapType = AssetTemplateLayoutMapType::Single;
    }

    return mapType;
}

std::string ToolsAssetLayoutEditorFactory::ExtractMap(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    std::string map = {};
    if (auto mapAttribute = node->Attribute("map", CaseSensitivity::IgnoreCase))
    {
        map = mapAttribute->Value();
    }

    return map;
}

std::vector<std::string> ToolsAssetLayoutEditorFactory::ExtractEnumFilter(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    std::string enumFilter = {};
    if (auto enumFilterAttribute = node->Attribute("enumfilter", CaseSensitivity::IgnoreCase))
    {
        enumFilter = enumFilterAttribute->Value();
    }

    if (enumFilter.empty())
    {
        return {};
    }

    return EnumFilterFactory::GetValues(enumFilter);
}
