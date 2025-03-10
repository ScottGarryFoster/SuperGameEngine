#pragma once
#include <memory>

namespace SuperGameEngine
{
    class SerializableParser;
    class SceneLoadPackage;
}

namespace SuperGameInput
{
    class InputHandler;
}

using namespace SuperGameInput;

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
        virtual std::shared_ptr<SceneLoadPackage> GetSceneLoadPackage() const = 0;

        /// <summary>
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        /// <returns>Given to Tools and Engine to provide Input. </returns>
        virtual std::shared_ptr<InputHandler> GetInput() const = 0;
    };
}


