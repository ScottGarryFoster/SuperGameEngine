#pragma once
#include <unordered_map>

#include "GameObject.h"
#include "../../FatedQuestReferences.h"
#include "../../Engine/Basic/ExtremelyWeakWrapper.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    class SuperComponentLoadPackage;

    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class SuperGameObject : public GameObject
    {
    public:
        SuperGameObject();
        virtual ~SuperGameObject();

        /// <summary>
        /// A unique identifier.
        /// </summary>
        virtual std::shared_ptr<Guid> GetGuid() const override;

        /// <summary>
        /// Sets the Guid on the GameObject.
        /// </summary>
        /// <param name="guid">New Guid. </param>
        virtual void SetGuid(const std::shared_ptr<Guid>& guid);

        /// <summary>
        /// A unique identifier.
        /// </summary>
        /// <returns>Guid of the Scene. </returns>
        virtual std::shared_ptr<Guid> GetSceneGuid() const override;

        /// <summary>
        /// Sets scene.
        /// </summary>
        /// <param name="guid">Guid of the Scene. </param>
        virtual void SetScene(std::shared_ptr<Guid> guid) override;

        /// <summary>
        /// Sets up the GameObject.
        /// </summary>
        /// <param name="loadPackage">Contains all the objects a GameObject needs to operate. </param>
        /// <param name="sceneToGameObjectPackage">Contains gameObject specific loading items.</param>
        virtual void Setup(std::shared_ptr<GameObjectLoadPackage> loadPackage) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="gameTime">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual void Update(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Update which occurs at a set time.
        /// </summary>
        /// <param name="gameTime">Ticks since last frame. </param>
        virtual void FixedUpdate(const std::shared_ptr<GameTime> gameTime) override;

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw() const override;

        /// <summary>
        /// Adds the GameComponent to the GameObject.
        /// Will run Setup on the GameComponent and add it to any
        /// services such as the Collision.
        /// Ensured the component is registered see 'ComponentFactory.h'.
        /// </summary>
        /// <param name="type">Type to find. </param>
        /// <returns>The new component. </returns>
        virtual std::shared_ptr<GameComponent> AddComponent(const std::string& type) override;

        /// <summary>
        /// Gets the component.
        /// </summary>
        /// <param name="type">Type to find. </param>
        /// <returns>The component as a Game Component. </returns>
        virtual std::shared_ptr<GameComponent> GetComponent(const std::string& type) const override;

        /// <summary>
        /// Gets all components on the GameObject.
        /// </summary>
        /// <returns>All components. Could be an empty vector. </returns>
        virtual std::vector<std::pair<std::string, std::shared_ptr<GameComponent>>> GetAllComponents() const override;

        /// <summary>
        /// Destroys the game object.
        /// </summary>
        virtual void Destroy() override;

        /// <summary>
        /// Is this GameObject marks for destruction.
        /// </summary>
        /// <returns>True means is marked for Destroyed. </returns>
        virtual bool IsDestroyed() const override;

        /// <summary>
        /// Destroys the gameObject immediately, calling all the code
        /// to destroy the gameObject and all it owns.
        /// </summary>
        virtual void DestroyImmediately() override;

        /// <summary>
        /// Any further cleanup after being destroyed by the parent
        /// should take place here. This is called after the parent
        /// has classed you as removed.
        /// </summary>
        virtual void OnDestroyed() override;


    private:
        /// <summary>
        /// Unique identifier.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// Scene Guid.
        /// </summary>
        std::shared_ptr<Guid> m_sceneGuid;

        /// <summary>
        /// Everything passed down from the scene.
        /// </summary>
        std::shared_ptr<GameObjectLoadPackage> m_loadPackage;

        /// <summary>
        /// Everything a component needs to operate.
        /// </summary>
        std::shared_ptr<SuperComponentLoadPackage> m_componentPackage;

        /// <summary>
        /// All components currently loaded.
        /// </summary>
        std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>> m_gameComponents;

        /// <summary>
        /// Game components which have been added but not updated yet.
        /// All components must be updated then drawn.
        /// You can still get a component not yet updated.
        /// </summary>
        std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>> m_pendingGameComponents;

        /// <summary>
        /// True means that there are components sat in pending waiting to move.
        /// </summary>
        bool m_componentsAwaitUpdate;

        /// <summary>
        /// True means destroyed.
        /// </summary>
        bool m_isDestroyed;

        /// <summary>
        /// An extremely weak pointer to give to the component children.
        /// We should clean this up and manage it.
        /// </summary>
        std::shared_ptr<ExtremelyWeakWrapper<GameObject>> m_pointerToSelf;

        /// <summary>
        /// Adds the actual component.
        /// </summary>
        /// <param name="type">Type of the component as a string. Used for organisation. </param>
        /// <param name="reference">Reference to the component to save. </param>
        /// <returns>True means added. </returns>
        bool AddActualComponent(const std::string& type, const std::shared_ptr<GameComponent>& reference);

        /// <summary>
        /// Adds component to actual dictionary
        /// </summary>
        /// <param name="type">Type as string. </param>
        /// <param name="reference">Component reference. </param>
        /// <param name="dictionaryToWriteTo">Dictionary to add to. </param>
        void AddComponentToDictionary(
            const std::string& type, std::shared_ptr<GameComponent> reference,
            std::unordered_map<std::string, std::vector<std::shared_ptr<GameComponent>>>& dictionaryToWriteTo);

        /// <summary>
        /// Removes destroyed components.
        /// To be called outside of any loops.
        /// </summary>
        void RemoveDestroyedComponents();

        /// <summary>
        /// Moves any pending components into the main loop.
        /// </summary>
        void MovePendingToMain();
    };

    REGISTER_CLASS(SuperGameObject)
}

