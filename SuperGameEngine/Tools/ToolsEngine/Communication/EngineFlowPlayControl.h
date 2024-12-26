#pragma once
#include "EngineFlowControl.h"
#include "EnginePlayControl.h"

namespace SuperGameTools
{
    /// <summary>
    /// Complete control over how and when the engine runs.
    /// </summary>
    class EngineFlowPlayControl : public EnginePlayControl, public EngineFlowControl
    {
    };
}
