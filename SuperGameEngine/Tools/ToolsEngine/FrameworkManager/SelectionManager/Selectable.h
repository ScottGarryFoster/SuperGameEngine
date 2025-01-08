#pragma once
#include <unordered_set>

#include "SelectionGroup.h"

namespace FatedQuestLibraries
{
    class Guid;
}

namespace SuperGameTools
{
    /// <summary>
    /// An object that may be selected in the editor.
    /// </summary>
    class Selectable
    {
    public:

        /// <summary>
        /// Describes the group for the selectable which helps to decide the
        /// buckets that the selectable will be added to.
        /// </summary>
        /// <returns>The group or groups for this selectable. </returns>
        virtual std::unordered_set<SelectionGroup> GetSelectionGroup() const = 0;

        /// <summary>
        /// The Guid for this Selectable.
        /// It should be unique among selectables.
        /// </summary>
        /// <returns>A unique Guid. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::Guid> GetGuid() const = 0;
    };

}

