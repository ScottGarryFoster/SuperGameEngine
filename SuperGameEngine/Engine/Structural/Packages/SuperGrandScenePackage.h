#pragma once
#include <memory>

#include "GrandScenePackage.h"

namespace SuperGameEngine
{
    class ContentManager;

    /// <summary>
    /// Everything a grand scene needs to run.
    /// This contains services run by the engine.
    /// </summary>
    class SuperGrandScenePackage : public GrandScenePackage
    {
    public:
        SuperGrandScenePackage();

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
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        /// <returns>Given to Tools and Engine to provide Input. </returns>
        virtual std::shared_ptr<InputHandler> GetInput() const override;

        /// <summary>
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        /// <param name="inputHandler">Given to Tools and Engine to provide Input. </param>
        virtual void SetInputHandler(const std::shared_ptr<InputHandler>& inputHandler);

        /// <summary>
        /// Gets a scene load package based on the Grand Scene Package.
        /// </summary>
        /// <returns>
        /// A scene load package based on the Grand Scene Package.
        /// Returns empty if could not create.
        /// </returns>
        virtual std::shared_ptr<SceneLoadPackage> GetSceneLoadPackage() const override;

    private:
        /// <summary>
        /// Provides and manages all shared resources.
        /// </summary>
        std::shared_ptr<ContentManager> m_contentManager;

        /// <summary>
        /// True means a scene load package is created.
        /// </summary>
        bool m_createdSceneLoadPackage;

        /// <summary>
        /// The scene load package version of this if successfully created.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_sceneLoadPackage;

        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SerializableParser> m_serializableParser;

        /// <summary>
        /// Given to Tools and Engine to provide Input.
        /// </summary>
        std::shared_ptr<InputHandler> m_inputHandler;

        /// <summary>
        /// Attempts to create a scene load package.
        /// Called when setting up the Grand Scene.
        /// </summary>
        void AttemptToCreateAGameObjectLoadPackage();
    };
}


