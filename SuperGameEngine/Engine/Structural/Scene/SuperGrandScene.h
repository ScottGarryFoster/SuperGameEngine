#pragma once
#include "GrandScene.h"
#include <memory>

namespace SuperGameEngine
{
    class SceneLoadPackage;
    class GrandScenePackage;

    /// <summary>
    /// Holds everything in the entire game and manages the objects.
    /// </summary>
    class SuperGrandScene : public GrandScene
    {
    public:
        /// <summary>
        /// Sets up the Grand Scene.
        /// </summary>
        /// <param name="grandScenePackage">Everything a grand scene needs to run. </param>
        virtual void Setup(std::shared_ptr<GrandScenePackage> grandScenePackage) override;

        /// <summary>
        /// True means Setup was run and it is ready to be used.
        /// </summary>
        /// <returns>True means Setup was run and it is ready to be used. </returns>
        virtual bool IsSetup() const override;

        /// <summary>
        /// Updates the grand scene this frame.
        /// </summary>
        /// <param name="gameTime">The current state of time this frame. </param>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draws the grand scene.
        /// For most components this will do nothing.
        /// </summary>
        virtual void Draw() const override;

    private:
        /// <summary>
        /// Everything a grand scene needs to run.
        /// </summary>
        std::shared_ptr<GrandScenePackage> m_grandScenePackage;

        /// <summary>
        /// True means is setup.
        /// </summary>
        bool m_isSetup;

        /// <summary>
        /// Everything a scene needs to load and exist.
        /// </summary>
        std::shared_ptr<SceneLoadPackage> m_sceneLoadPackage;
    };
};