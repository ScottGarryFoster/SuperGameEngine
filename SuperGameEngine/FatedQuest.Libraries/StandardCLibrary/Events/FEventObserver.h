#pragma once
class FEventArguments;

namespace StandardCLibrary
{
    /// <summary>
    /// Any class which is able to observe events.
    /// </summary>
    class FEventObserver
    {
    public:

        /// <summary>
        /// Inform the observer an event has taken place.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        /// <remarks>
        /// This requires us to use dynamic casting. Okay for now but long term
        /// we should consider a larger solution.
        /// </remarks>
        virtual void Invoke(FEventArguments arguments) = 0;
    };
}