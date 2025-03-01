#pragma once
#include <memory>

namespace SuperGameInput
{
    class InputHandler;
}

using namespace SuperGameInput;

namespace SuperGameEngine
{
    class ComponentLoadPackage;
    class SerializableParser;
    class ContentManager;

    /// <summary>
    /// Everything a game object needs to run.
    /// </summary>
    class GameObjectLoadPackage
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
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        /// <returns>Given to Tools and Engine to provide Input. </returns>
        virtual std::shared_ptr<InputHandler> GetInput() const = 0;

        /// <summary>
        /// Create a scene load package based on the Grand Scene Package.
        /// </summary>
        /// <returns>
        /// A scene load package based on the Grand Scene Package.
        /// Returns empty if cannot create.
        /// </returns>
        virtual std::shared_ptr<ComponentLoadPackage> GetComponentLoadPackage() const = 0;
    };
}

