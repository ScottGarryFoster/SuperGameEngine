#pragma once
#include <memory>

#include "EnginePlayControl.h"

namespace SuperGameTools
{
    /// <summary>
    /// Communication with the Engine Entry.
    /// </summary>
    class EngineEntryCommunication
    {
    public:
        virtual ~EngineEntryCommunication() = default;

        /// <summary>
        /// Allows you to control the flow of the engine.
        /// </summary>
        /// <returns>Allows you to control the flow of the engine. </returns>
        virtual std::shared_ptr<EnginePlayControl> GetPlayControls() const = 0;
    };
}
