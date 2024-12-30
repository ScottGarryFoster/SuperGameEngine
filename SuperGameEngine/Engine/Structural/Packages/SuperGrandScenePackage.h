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
        virtual void SetContentManager(std::shared_ptr<ContentManager> contentManager);

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
        /// Attempts to create a scene load package.
        /// Called when setting up the Grand Scene.
        /// </summary>
        void AttemptToCreateASceneLoadPackage();
    };
}


