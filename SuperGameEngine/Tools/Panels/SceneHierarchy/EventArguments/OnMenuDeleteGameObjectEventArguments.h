#pragma once
#include <memory>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"
#include "../../../FatedQuestLibraries.h"

namespace SuperGameTools
{
    class GameObject;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// Arguments for when the user requests to delete a Game Object.
    /// </summary>
    class OnMenuDeleteGameObjectEventArguments : public FEventArguments
    {
    public:
        OnMenuDeleteGameObjectEventArguments(
            const std::shared_ptr<Guid>& guid, 
            const std::shared_ptr<GameObject>& gameObject)
        {
            m_guid = guid;
            m_gameObject = gameObject;
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
        inline std::shared_ptr<GameObject> GetGameObject()
        {
            return m_gameObject;
        }

    private:
        /// <summary>
        /// The ID of the Tree view item requested to delete.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// The Game Object requested for deletion.
        /// </summary>
        std::shared_ptr<GameObject> m_gameObject;
    };
}