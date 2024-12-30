#pragma once
#include <memory>

namespace SuperGameEngine
{
    class SceneLoadPackage;
}

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

        /// <summary>
        /// Create a scene load package based on the Grand Scene Package.
        /// </summary>
        /// <returns>
        /// A scene load package based on the Grand Scene Package.
        /// Returns empty if cannot create.
        /// </returns>
        virtual std::shared_ptr<SceneLoadPackage> GetSceneLoadPackage() const = 0;
    };
}


