#pragma once
#include "PropertyChangedAction.h"
#include "PropertyChangedSubscriptions.h"
#include "../../FatedQuestLibraries.h"

namespace SuperGameTools
{
    /// <summary>
    /// Manages event for properties changed.
    /// </summary>
    class PropertyChangedEvent : public PropertyChangedSubscriptions, public PropertyChangedAction
    {
    public:
        PropertyChangedEvent();
        virtual ~PropertyChangedEvent() override = default;

        /// <summary>
        /// Subscribes to the event.
        /// </summary>
        /// <param name="observer">Observer to subscribe. </param>
        virtual void Subscribe(std::weak_ptr<PropertyChangedObserver> observer) override;

        /// <summary>
        /// Unsubscribes from the event.
        /// </summary>
        /// <param name="observer">Observer to unsubscribe. </param>
        virtual void Unsubscribe(std::weak_ptr<PropertyChangedObserver> observer) override;

        /// <summary>
        /// Property has changed.
        /// </summary>
        /// <param name="name">Property which has changed. </param>
        virtual void PropertyChanged(const std::string& name) override;

    private:

        /// <summary>
        /// List of observers.
        /// </summary>
        /// <remark>Consider linked list. </remark>
        std::vector<std::weak_ptr<PropertyChangedObserver>> m_observers;
    };
}


