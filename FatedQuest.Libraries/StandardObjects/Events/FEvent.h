#pragma once

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
    class FEvent : public FEventSubscriptions, FEventAction
    {
    public:
        FEvent();
        virtual ~FEvent() override = default;

        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(FEventObserver* observer) override;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(FEventObserver* observer) override;

        /// <summary>
        /// Invoke the event on all observers.
        /// </summary>
        /// <param name="arguments">Arguments to send to all observers. </param>
        virtual void Invoke(FEventArguments* arguments) override;

    private:

        /// <summary>
        /// List of observers.
        /// </summary>
        /// <remark>Consider linked list. </remark>
        std::vector<FEventObserver*> m_observers;
    };
}