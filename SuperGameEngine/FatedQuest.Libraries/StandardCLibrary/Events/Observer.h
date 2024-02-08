#pragma once

namespace StandardCLibrary
{
    /// <summary>
    /// Receives a message from a subject notifying it.
    /// </summary>
    class Observer
    {
    public:
        /// <summary>
        /// Subject has notified.
        /// </summary>
        virtual void Notify() = 0;
    };
}