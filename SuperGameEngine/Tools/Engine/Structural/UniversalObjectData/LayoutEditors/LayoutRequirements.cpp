#include "LayoutRequirements.h"
#include "../../../../../../FatedQuest.Libraries/Logger/AllReferences.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

LayoutRequirements::LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& layoutdocument)
{
    m_mapToLookAt = {};
    m_stringMatch = {};
    m_mapType = UniversalStorableType::Unknown;
    m_match = LayoutRequirementMatch::Match;

    if (auto dataMap = layoutdocument->Attribute("DataMap"))
    {
        if (!dataMap->Value().empty())
        {
            m_mapToLookAt = dataMap->Value();
        }
    }

    if (auto attribute = layoutdocument->Attribute("MapType"))
    {
        if (!attribute->Value().empty())
        {

            m_mapType = EUniversalStorableType::FromString(attribute->Value());
        }
    }

    if (m_mapType == UniversalStorableType::Unknown)
    {
        Log::Error("No map type defined in requirements for a layout. Please set this up."
            , "LayoutRequirements::LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>&)");
        return;
    }

    if (auto attribute = layoutdocument->Attribute("Value"))
    {
        if (!attribute->Value().empty())
        {
            switch (m_mapType)
            {
            case UniversalStorableType::String:
                m_stringMatch = attribute->Value();
                break;
            default:
                Log::Error("Match type: " + EUniversalStorableType::ToString(m_mapType) +
                    " not provided a way to create layout requirements from.",
                    "LayoutRequirements::LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>&)");
                return;
            }
        }
    }

    if (auto attribute = layoutdocument->Attribute("When"))
    {
        if (!attribute->Value().empty())
        {
            m_match = ELayoutRequirementMatch::FromString(attribute->Value());
        }
    }

    if (m_match == LayoutRequirementMatch::Unknown)
    {
        Log::Error("No match type defined in requirements for a layout. Please set this up."
            , "LayoutRequirements::LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>&)");
        return;
    }

    if (m_match != LayoutRequirementMatch::Match)
    {
        Log::Error("Only match has been setup as a type in layouts. Please change this in the data."
            , "LayoutRequirements::LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>&)");
        return;
    }
}

bool LayoutRequirements::ShouldShow(const std::shared_ptr<ModifiableUniversalObjectData>& universalObjectData) const
{
    if (m_match != LayoutRequirementMatch::Match || m_mapType != UniversalStorableType::String)
    {
        return true;
    }

    if (!universalObjectData->IsStringLoaded(m_mapToLookAt))
    {
        return false;
    }

    return universalObjectData->GetString(m_mapToLookAt) == m_stringMatch;
}
