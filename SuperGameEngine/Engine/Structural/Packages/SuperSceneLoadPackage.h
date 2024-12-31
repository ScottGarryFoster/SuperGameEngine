#pragma once
#include <memory>

#include "SceneLoadPackage.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Everything a component needs to run.
    /// </summary>
    class SuperSceneLoadPackage : public SceneLoadPackage
    {
    public:
        SuperSceneLoadPackage();

        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        /// <returns>Provides and manages all shared resources. </returns>
        [[nodiscard]] virtual std::shared_ptr<ContentManager> GetContentManager() const override;

        /// <summary>
        /// Set the content manager for the package.
        /// </summary>
        /// <param name="contentManager">Provides and manages all shared resources. </param>
        virtual void SetContentManager(const std::shared_ptr<ContentManager>& contentManager);

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        /// <returns>Helps to parse serializable objects. </returns>
        virtual std::shared_ptr<SerializableParser> GetParser() const override;

        /// <summary>
        /// Set the Serializable Parser for the package.
        /// </summary>
        /// <param name="serializableParser">New Serializable Parser. </param>
        virtual void SetSerializableParser(const std::shared_ptr<SerializableParser>& serializableParser);

        /// <summary>
        /// Create a scene load package based on the Grand Scene Package.
        /// </summary>
        /// <returns>
        /// A scene load package based on the Grand Scene Package.
        /// Returns empty if cannot create.
        /// </returns>
        virtual std::shared_ptr<GameObjectLoadPackage> GetGameObjectLoadPackage() const override;

    private:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;

        /// <summary>
        /// The scene load package version of this if successfully created.
        /// </summary>
        std::shared_ptr<GameObjectLoadPackage> m_gameObjectLoadPackage;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SerializableParser> m_serializableParser;

        /// <summary>
        /// Attempts to create a scene load package.
        /// Called when setting up the Grand Scene.
        /// </summary>
        void AttemptToCreateASceneLoadPackage();
    };
}

