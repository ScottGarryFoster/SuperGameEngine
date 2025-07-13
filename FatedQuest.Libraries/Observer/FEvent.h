#pragma once

#include <memory>

#include "FEventSubscriptions.h"
#include "FEventAction.h"
#include "FEventArguments.h"
#include "FEventObserver.h"
#include <vector>

namespace FatedQuestLibraries
{
    /// <summary>
    /// An event which can be subscribed to and can invoke a message to observers.
    /// </summary>
    class FEvent : public FEventSubscriptions, public FEventAction
    {
    public:
        FEvent();
        virtual ~FEvent() override = default;

        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(std::weak_ptr<FEventObserver> observer) override;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(std::weak_ptr<FEventObserver> observer) override;

        /// <summary>
        /// Invoke the event on all observers.
        /// </summary>
        /// <param name="arguments">Arguments to send to all observers. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;
    private:

        /// <summary>
        /// List of observers.
        /// </summary>
        /// <remark>Consider linked list. </remark>
        std::vector<std::weak_ptr<FEventObserver>> m_observers;
    };
}