#pragma once
#include <memory>
#include <string>

#include "LayoutRequirementMatch.h"
#include "../../../../../../FatedQuest.Libraries/StandardObjects/AllReferences.h"

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class ModifiableUniversalObjectData;
}

namespace SuperGameTools
{
    /// <summary>
    /// Resolves requirements for layout editors.
    /// </summary>
    class LayoutRequirements
    {
    public:

        LayoutRequirements(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& layoutdocument);

        /// <summary>
        /// Is true when this layout is required and therefore should be shown.
        /// </summary>
        /// <param name="universalObjectData">A pointer to the asset. </param>
        /// <returns>Is true when this layout is required and therefore should be shown. </returns>
        virtual bool ShouldShow(const std::shared_ptr<FatedQuestLibraries::ModifiableUniversalObjectData>& universalObjectData) const;

    private:

        /// <summary>
        /// The map to look for a value within.
        /// </summary>
        std::string m_mapToLookAt;

        /// <summary>
        /// If we are matching to a string, this is the value to look for.
        /// </summary>
        std::string m_stringMatch;

        /// <summary>
        /// The type of the map we would be looking for.
        /// </summary>
        FatedQuestLibraries::UniversalStorableType m_mapType;

        /// <summary>
        /// The type of matching we would be doing with the value.
        /// </summary>
        LayoutRequirementMatch m_match;
    };
}
