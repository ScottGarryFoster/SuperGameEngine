#pragma once
#include "../../../../../FatedQuest.Libraries/StandardObjects/Object/GUID/GUIDHelpers.h"
#include "../../../../Tools/ToolsEngine/FrameworkManager/SelectionManager/Selectable.h"

using namespace SuperGameTools;
using namespace FatedQuestLibraries;

namespace SuperGameToolsTests
{

    class SelectableStub : public Selectable
    {
    public:
        SelectableStub(SelectionGroup group)
        {
            m_selectionGroups.insert(group);
            GUIDHelpers::CreateGUID();
        }

        /// <summary>
        /// Describes the group for the selectable which helps to decide the
        /// buckets that the selectable will be added to.
        /// </summary>
        /// <returns>The group or groups for this selectable. </returns>
        virtual std::unordered_set<SelectionGroup> GetSelectionGroup() const override
        {
            return m_selectionGroups;
        }

        std::unordered_set<SelectionGroup> m_selectionGroups;

        /// <summary>
        /// The Guid for this Selectable.
        /// It should be unique among selectables.
        /// </summary>
        /// <returns>A unique Guid. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const override
        {
            return m_guid;
        }

        std::shared_ptr<Guid> m_guid;
    };
}
