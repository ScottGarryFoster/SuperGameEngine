#pragma once
#include <memory>

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Everything a component needs to run.
    /// </summary>
    class ComponentLoadPackage
    {
    public:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const = 0;
    };
}

