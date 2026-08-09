#pragma once
#include <memory>

#include "../../../../FatedQuest.Libraries/Observer/FEventSubscriptions.h"

namespace SuperGameTools
{
    /// <summary>
    /// Holds and links together events from the scene and inspector which contain core concepts
    /// such as 'oncomponentadded' which are in the main engine but affect behaviour in other engines.
    /// </summary>
    class SharedSceneChangedEvents
    {
    public:

        /// <summary>
        /// Event is called when a component is added.
        /// Uses OnMenuAddComponentEventArguments.
        /// </summary>
        /// <returns>Event is called when a component is added. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnComponentAdded() const = 0;

        /// <summary>
        /// Event is called when a component is deleted.
        /// Uses OnMenuDeleteComponentEventArguments.
        /// </summary>
        /// <returns>Event is called when a component is deleted. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnComponentDeleted() const = 0;

        /// <summary>
        /// Event is called when a new game object is added.
        /// Uses OnMenuNewGameObjectEventArguments.
        /// This is not implemented.
        /// </summary>
        /// <returns>Event is called when a new game object is added. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnGameObjectAdded() const = 0;

        /// <summary>
        /// Event is called when a new game object is deleted.
        /// Uses OnMenuDeleteGameObjectEventArguments.
        /// </summary>
        /// <returns>Event is called when a new game object is deleted. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnGameObjectDeleted() const = 0;

        /// <summary>
        /// Event is called when a scene is loaded or re-loaded.
        /// Uses OnSceneUpdatedEventArguments.
        /// </summary>
        /// <returns>Event is called when a scene is loaded or re-loaded. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSceneLoaded() const = 0;
    };  
}
