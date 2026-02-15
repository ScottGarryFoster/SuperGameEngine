#pragma once
#include "SharedSceneChangedEvents.h"

namespace SuperGameTools
{
    class InspectorWindow;
    class SceneHierarchy;
}

namespace SuperGameTools
{
    /// <summary>
    /// Holds and links together events from the scene and inspector which contain core concepts
    /// such as 'oncomponentadded' which are in the main engine but affect behaviour in other engines.
    /// </summary>
    class ToolsSharedSceneChangedEvents : public SharedSceneChangedEvents
    {
    public:

        ToolsSharedSceneChangedEvents(
            const std::shared_ptr<SceneHierarchy>& sceneHierarchy, 
            const std::shared_ptr<InspectorWindow>& inspector);

        /// <summary>
        /// Event is called when a component is added.
        /// Uses OnMenuAddComponentEventArguments.
        /// </summary>
        /// <returns>Event is called when a component is added. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnComponentAdded() const override;

        /// <summary>
        /// Event is called when a component is deleted.
        /// Uses OnMenuDeleteComponentEventArguments.
        /// </summary>
        /// <returns>Event is called when a component is deleted. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnComponentDeleted() const override;

        /// <summary>
        /// Event is called when a new game object is added.
        /// Uses OnMenuNewGameObjectEventArguments.
        /// </summary>
        /// <returns>Event is called when a new game object is added. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnGameObjectAdded() const override;

        /// <summary>
        /// Event is called when a new game object is deleted.
        /// Uses OnMenuDeleteGameObjectEventArguments.
        /// </summary>
        /// <returns>Event is called when a new game object is deleted. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnGameObjectDeleted() const override;

        /// <summary>
        /// Event is called when a scene is loaded or re-loaded.
        /// Uses OnSceneUpdatedEventArguments.
        /// </summary>
        /// <returns>Event is called when a scene is loaded or re-loaded. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSceneLoaded() const override;

    private:

        /// <summary>
         /// Contains the scenes and game objects.
         /// </summary>
        std::shared_ptr<SceneHierarchy> m_sceneHierarchy;

        /// <summary>
        /// Property and metadata inspector window.
        /// </summary>
        std::shared_ptr<InspectorWindow> m_inspector;
    };
}

