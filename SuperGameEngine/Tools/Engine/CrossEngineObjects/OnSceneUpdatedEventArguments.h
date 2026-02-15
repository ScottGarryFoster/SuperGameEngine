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

        OnSceneUpdatedEventArguments(
            SceneUpdateAction updateAction, 
            const std::shared_ptr<Scene>& scene)
        {
            m_sceneUpdateAction = updateAction;
            m_scene = scene;
        }

        /// <summary>
        /// The
        /// </summary>
        /// <returns></returns>
        SceneUpdateAction GetUpdateAction() const
        {
            return m_sceneUpdateAction;
        }

        /// <summary>
        /// The scene being updated.
        /// </summary>
        /// <returns>The scene being updated. </returns>
        std::shared_ptr<Scene> GetScene() const
        {
            return m_scene;
        }

    private:

        /// <summary>
        /// Describes what updated (or how) when the scene updates.
        /// </summary>
        SceneUpdateAction m_sceneUpdateAction;

        /// <summary>
        /// The scene being updated.
        /// </summary>
        std::shared_ptr<Scene> m_scene;
    };

}