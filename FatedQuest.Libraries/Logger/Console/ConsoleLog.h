#pragma once
#include "../Observer/AllReferences.h"
#include "Logger/Log.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// Logs to the console.
    /// </summary>
    class ConsoleLog : public FEventObserver
    {
    public:
        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;
    };
}
