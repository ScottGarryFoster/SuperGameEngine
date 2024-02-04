#pragma once
#include "FEventObserver.h"

namespace StandardCLibrary
{
    class FEventSubscriptions
    {
    public:
        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(FEventObserver* observer) = 0;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(FEventObserver* observer) = 0;
    };
}

