#pragma once
#include <memory>

namespace SuperGameEngine
{
    class SerializableParser;
    class GameObjectLoadPackage;
}

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Everything a component needs to run.
    /// </summary>
    class SceneLoadPackage
    {
    public:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const = 0;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        /// <returns>Helps to parse serializable objects. </returns>
        virtual std::shared_ptr<SerializableParser> GetParser() const = 0;

        /// <summary>
        /// Create a scene load package based on the Grand Scene Package.
        /// </summary>
        /// <returns>
        /// A scene load package based on the Grand Scene Package.
        /// Returns empty if cannot create.
        /// </returns>
        virtual std::shared_ptr<GameObjectLoadPackage> GetGameObjectLoadPackage() const = 0;
    };
}

