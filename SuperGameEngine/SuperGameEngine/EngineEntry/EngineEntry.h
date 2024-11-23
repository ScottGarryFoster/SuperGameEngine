#pragma once
#include "Engine.h"
#include <memory>

namespace SuperGameEngine
{
    /// <summary>
    /// The entry point for the engine and the top most level before main.
    /// </summary>
    class EngineEntry
    {
    public:
        /// <summary>
        /// The entry to the engine.
        /// </summary>
        /// <param name="engine">Engine to run. </param>
        /// <returns>
        /// 0 means no errors occured when 
        /// attempting to start the application.
        /// </returns>
        int RunApplication(std::shared_ptr<Engine> engine);
    };
}