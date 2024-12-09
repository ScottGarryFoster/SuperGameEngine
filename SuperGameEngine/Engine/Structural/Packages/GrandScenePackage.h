#pragma once
#include <memory>

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Everything a grand scene needs to run.
    /// This contains services run by the engine.
    /// </summary>
    class GrandScenePackage
    {
    public:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const = 0;
    };
}


