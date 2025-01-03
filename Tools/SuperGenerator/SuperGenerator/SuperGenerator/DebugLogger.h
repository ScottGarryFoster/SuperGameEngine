#pragma once
#include <memory>

#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

using namespace FatedQuestLibraries;

class DebugLogger : public FEventObserver
{
public:
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
    virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;
};

