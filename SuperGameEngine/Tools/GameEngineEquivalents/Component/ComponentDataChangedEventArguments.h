#pragma once
#include <memory>

#include "ToolsEngine/SharedEventArguments/DirtiedDataEventArguments.h"

namespace FatedQuestLibraries
{
    class Guid;
}

namespace SuperGameTools
{
    /// <summary>
    /// Used when components change their core data and need to be re-evaluated.
    /// Note that this is used even when the component itself may already be dirty and
    /// something else maybe changed on the component.
    /// </summary>
    class ComponentDataChangedEventArguments : public DirtiedDataEventArguments
    {
    public:

        ComponentDataChangedEventArguments(const std::shared_ptr<Guid>& componentGuid, const std::shared_ptr<Guid>& gameObjectGuid,
            bool dirtyFlag)
            : DirtiedDataEventArguments(dirtyFlag)
        {
            m_componentGuid = componentGuid;
            m_gameObjectGuid = gameObjectGuid;
        }

        /// <summary>
        /// The component Guid.
        /// </summary>
        /// <returns>The component Guid. </returns>
        std::shared_ptr<Guid> GetComponentGuid() const
        {
            return m_componentGuid;
        }

        /// <summary>
        /// The game object Guid.
        /// </summary>
        /// <returns>The game object Guid. </returns>
        std::shared_ptr<Guid> GetGameObjectGuid() const
        {
            return m_gameObjectGuid;
        }

    private:

        /// <summary>
        /// The game object guid.
        /// </summary>
        std::shared_ptr<Guid> m_gameObjectGuid;

        /// <summary>
        /// The component guid.
        /// </summary>
        std::shared_ptr<Guid> m_componentGuid;
    };
}
