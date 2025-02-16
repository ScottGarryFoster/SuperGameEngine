#pragma once
#include <memory>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"
#include "../../../FatedQuestLibraries.h"

namespace SuperGameTools
{
    class Component;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Arguments for when the user requests to delete a Component.
    /// </summary>
    class OnMenuDeleteComponentEventArguments : public FEventArguments
    {
    public:
        OnMenuDeleteComponentEventArguments(
            const std::shared_ptr<Guid>& guid,
            const std::shared_ptr<Component>& component)
        {
            m_guid = guid;
            m_component = component;
        }

        /// <summary>
        /// The ID of the Tree view item requested to delete.
        /// </summary>
        /// <returns>Guid of the tree view Item. </returns>
        inline std::shared_ptr<Guid> GetUniqueId()
        {
            return m_guid;
        }

        /// <summary>
        /// The Game Object requested for deletion.
        /// </summary>
        /// <returns>The Game Object requested for deletion. </returns>
        inline std::shared_ptr<Component> GetComponent()
        {
            return m_component;
        }

    private:
        /// <summary>
        /// The ID of the Tree view item requested to delete.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// The Component requested for deletion.
        /// </summary>
        std::shared_ptr<Component> m_component;
    };
}