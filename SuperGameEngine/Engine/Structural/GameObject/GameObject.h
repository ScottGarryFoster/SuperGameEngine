#pragma once
#include "../../FatedQuestReferences.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class GameComponent;
    class GameTime;
    class SceneLoadPackage;

    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class GameObject
    {
    public:
        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<Guid> GetGuid() const = 0;

        /// <summary>
        /// A unique identifier.
        /// </summary>
        /// <returns>Guid of the Scene. </returns>
        virtual std::shared_ptr<Guid> GetSceneGuid() const = 0;

        /// <summary>
        /// Sets scene.
        /// </summary>
        /// <param name="guid">Guid of the Scene. </param>
        virtual void SetScene(std::shared_ptr<FatedQuestLibraries::Guid> guid) = 0;

        /// <summary>
        /// Sets up the GameObject.
        /// </summary>
        /// <param name="sceneLoadPackage">Contains all the objects a GameObject needs to operate. </param>
        /// <param name="sceneToGameObjectPackage">Contains gameObject specific loading items.</param>
        virtual void Setup(std::shared_ptr<SceneLoadPackage> loadPackage) = 0;
        //TODO: Add this SceneToGameObjectPackage* gameObjectPackage

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Update which occurs at a set time.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) = 0;

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Adds the GameComponent to the GameObject.
        /// Will run Setup on the GameComponent and add it to any
        /// services such as the Collision.
        /// Ensured the component is registered see 'ComponentFactory.h'.
        /// </summary>
        /// <param name="type">Type to find. </param>
        /// <returns>The new component. </returns>
        virtual std::shared_ptr<GameComponent> AddComponent(const std::string& type) = 0;

        /// <summary>
        /// Gets the component.
        /// </summary>
        /// <param name="type">Type to find. </param>
        /// <returns>The component as a Game Component. </returns>
        virtual std::shared_ptr<GameComponent> GetComponent(const std::string& type) const = 0;
    };
}

