#pragma once

#include "FEventObserver.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Allows an object to subscribe to an event.
    /// This should be all that is required to give out to create an event instead of a delegate
    /// the object could invoke.
    /// </summary>
    class FEventSubscriptions
    {
    public:
        virtual ~FEventSubscriptions() = default;

        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(std::weak_ptr<FEventObserver> observer) = 0;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(std::weak_ptr<FEventObserver> observer) = 0;
    };
}

