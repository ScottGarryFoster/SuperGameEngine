#pragma once
#include <memory>

namespace SuperGameTools
{
    class PropertyChangedObserver;

    class PropertyChangedSubscriptions
    {
    public:
        virtual ~PropertyChangedSubscriptions() = default;

        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(std::weak_ptr<PropertyChangedObserver> observer) = 0;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(std::weak_ptr<PropertyChangedObserver> observer) = 0;
    };
}

