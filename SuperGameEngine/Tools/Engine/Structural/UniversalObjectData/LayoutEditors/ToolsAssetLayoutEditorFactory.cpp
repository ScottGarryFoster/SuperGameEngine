#include "ToolsAssetLayoutEditorFactory.h"

#include "../../UniversalObjectData/LayoutEditors/LayoutEditorFilteredDropdown.h"
#include "../../UniversalObjectData/LayoutEditors/LayoutEditorTextInput.h"
#include "../../UniversalObjectData/LayoutEditors/Array/LayoutEditorTextInputArray.h"
#include "../../UniversalObjectData/LayoutEditors/LayoutEditorVector4I.h"
#include "FatedQuestLibraries.h"
#include "../../../../../../FatedQuest.Libraries/SharedEnums/Objects/EnumFilterFactory.h"
#include "../../UniversalObjectData/LayoutEditors/Array/LayoutEditorFilteredDropdownArray.h"
#include "../../UniversalObjectData/LayoutEditors/Array/LayoutEditorVector4IArray.h"
#include "../../UniversalObjectData/Template/LayoutTemplateLayoutMapType.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

std::shared_ptr<LayoutEditor> ToolsAssetLayoutEditorFactory::Create(
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

    LayoutTemplateLayoutMapType maptype = ExtractMapType(node);
    if (maptype == LayoutTemplateLayoutMapType::Unknown)
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
                case LayoutTemplateLayoutMapType::Single:
                    if (enumFilters.empty())
                    {
                        return std::make_shared<LayoutEditorTextInput>(map);
                    }
                    else
                    {
                        return std::make_shared<LayoutEditorFilteredDropdown>(map, enumFilters);
                    }
                case LayoutTemplateLayoutMapType::Array:
                    if (enumFilters.empty())
                    {
                        return std::make_shared<LayoutEditorTextInputArray>(map);
                    }
                    else
                    {
                        return std::make_shared<LayoutEditorFilteredDropdownArray>(map, enumFilters);
                    }
            }
            break;
        case UniversalStorableType::Vector4I:
            switch (maptype)
            {
            case LayoutTemplateLayoutMapType::Single:
                return std::make_shared<LayoutEditorVector4I>(map);
            case LayoutTemplateLayoutMapType::Array:
                return std::make_shared<LayoutEditorVector4IArray>(map);
            }
            break;

            
    }

    Log::Error("Could not create layout for the following combination: " +
        EUniversalStorableType::ToString(type) + " / " + ELayoutTemplateLayoutMapType::ToString(maptype),
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

LayoutTemplateLayoutMapType ToolsAssetLayoutEditorFactory::ExtractMapType(
    const std::shared_ptr<const StoredDocumentNode>& node) const
{
    auto mapType = LayoutTemplateLayoutMapType::Unknown;
    if (auto mapAttribute = node->Attribute("maptype", CaseSensitivity::IgnoreCase))
    {
        mapType = ELayoutTemplateLayoutMapType::FromString(mapAttribute->Value(), false);
        if (mapType == LayoutTemplateLayoutMapType::Unknown)
        {
            // Do not set unknown map types to single as this suggests corruption.
            return LayoutTemplateLayoutMapType::Unknown;
        }
    }

    if (mapType == LayoutTemplateLayoutMapType::Unknown)
    {
        mapType = LayoutTemplateLayoutMapType::Single;
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
