#pragma once

#include "FEventArguments.h"

namespace StandardCLibrary
{
    /// <summary>
    /// The action portion of the event.
    /// </summary>
    class FEventAction
    {
        /// <summary>
        /// Invoke the event on all observers.
        /// </summary>
        /// <param name="arguments">Arguments to send to all observers. </param>
        virtual void Invoke(FEventArguments* arguments) = 0;
    };
}