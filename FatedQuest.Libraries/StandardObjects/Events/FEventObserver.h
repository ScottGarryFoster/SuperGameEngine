#pragma once

#include "FEventArguments.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Any class which is able to observe events.
    /// </summary>
    class FEventObserver
    {
    public:
        virtual ~FEventObserver() = default;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        /// <remarks>
        /// This requires us to use dynamic casting. Okay for now but long term
        /// we should consider a larger solution.
        /// </remarks>
        virtual void Invoke(FEventArguments* arguments) = 0;
    };
}