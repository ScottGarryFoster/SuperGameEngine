#pragma once
#include "Observer.h"
#include <vector>

namespace StandardCLibrary
{
    /// <summary>
    /// Notifies Observers based on events.
    /// </summary>
    class Subject
    {
    public:
        Subject();
        virtual ~Subject();

        /// <summary>
        /// Add new observer.
        /// </summary>
        /// <param name="observer">New Observer. </param>
        virtual void AddObserver(Observer* observer);

        /// <summary>
        /// Remove new observer.
        /// </summary>
        /// <param name="observer">Observer to remove. </param>
        virtual void RemoveObserver(Observer* observer);

        /// <summary>
        /// Notify observers.
        /// </summary>
        virtual void Notify();

    private:

        /// <summary>
        /// List of observers.
        /// </summary>
        /// <remark>Consider linked list. </remark>
        std::vector<Observer*> m_observers;
    };
}