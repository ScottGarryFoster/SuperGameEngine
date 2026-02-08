#pragma once
#include "SceneUpdateAction.h"
#include "../../FatedQuestLibraries.h"

namespace SuperGameTools
{
    /// <summary>
    /// Event true
    /// </summary>
    class OnSceneUpdatedEventArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        OnSceneUpdatedEventArguments(SceneUpdateAction updateAction)
        {
            m_sceneUpdateAction = updateAction;
        }

        /// <summary>
        /// The
        /// </summary>
        /// <returns></returns>
        SceneUpdateAction GetUpdateAction() const
        {
            return m_sceneUpdateAction;
        }

    private:

        /// <summary>
        /// Describes what updated (or how) when the scene updates.
        /// </summary>
        SceneUpdateAction m_sceneUpdateAction;
    };

}