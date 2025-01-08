#pragma once
#include <unordered_set>

#include "SelectionGroup.h"

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
    };

}

