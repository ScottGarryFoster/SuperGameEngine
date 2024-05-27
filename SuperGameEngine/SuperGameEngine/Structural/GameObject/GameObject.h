#pragma once
#include <type_traits>

#include "../../Engine/Basic/GameTime.h"
#include <vector>
#include "../Scene/SceneLoadPackage.h"
#include "../Scene/SceneToGameObjectPackage.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class GameComponent;
    class TransformComponent;
    class Collision;

    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class GameObject : public Object
    {
    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        GameObject();
        virtual ~GameObject();

        /// <summary>
        /// A unique identifier.
        /// </summary>
        std::shared_ptr<Guid> GetGuid();

        /// <summary>
        /// A unique identifier.
        /// </summary>
        /// <returns>Guid of the Scene. </returns>
        std::shared_ptr<Guid> GetSceneGuid();

        /// <summary>
        /// Sets scene.
        /// </summary>
        /// <param name="guid">Guid of the Scene. </param>
        void SetScene(std::shared_ptr<Guid> guid);

        /// <summary>
        /// Sets up the GameObject.
        /// </summary>
        /// <param name="sceneLoadPackage">Contains all the objects a GameObject needs to opperate. </param>
        /// <param name="sceneToGameObjectPackage">Contains gameObject specfic loading items.</param>
        void Setup(SceneLoadPackage* loadPackage, SceneToGameObjectPackage* gameObjectPackage);

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(const GameTime gameTime);

        /// <summary>
        /// Update which occurs at a set time.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        virtual void FixedUpdate(const GameTime gameTime);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw();

        /// <summary>
        /// Adds the GameComponent to the GameObject.
        /// Will run Setup on the GameComponent and add it to any
        /// services such as the Collision.
        /// </summary>
        /// <typeparam name="T">The type of Component to add. </typeparam>
        /// <returns>The new Component. </returns>
        template<typename T>
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, std::shared_ptr<T>>::type
            AddComponent()
        {
            std::shared_ptr<T> newComponent = std::make_shared<T>();
            std::shared_ptr<Object> componentPtr = std::static_pointer_cast<Object>(newComponent);
            AddActualComponentFromObject(componentPtr);
            return newComponent;
        }

        /// <summary>
        /// Adds the GameComponent to the GameObject.
        /// Will run Setup on the GameComponent and add it to any
        /// services such as the Collision.
        /// Ensured the component is registered see 'ComponentFactory.h'.
        /// </summary>
        /// <param name="type">Name of the type. This must be registed. </param>
        /// <typeparam name="T">The type of Component to add. </typeparam>
        /// <returns>The new Component. </returns>
        template<typename T>
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, std::shared_ptr<T>>::type
        AddComponent(std::string type)
        {
            //std::shared_ptr<T> newComponent = std::make_shared<T>();
            //std::shared_ptr<Object> componentPtr = std::static_pointer_cast<Object>(newComponent);
            //AddActualComponentFromObject(componentPtr);
            //return newComponent;

            auto component = ComponentFactory::CreateComponent(type);
            if (component)
            {
                std::shared_ptr<Object> componentPtr = std::static_pointer_cast<Object>(component);
                AddActualComponentFromObject(componentPtr);
            }

            std::shared_ptr<T> componentOfType = std::static_pointer_cast<T>(component);
            return componentOfType;
        }

        /// <summary>
        /// Adds the GameComponent to the GameObject.
        /// Will run Setup on the GameComponent and add it to any
        /// services such as the Collision.
        /// Ensured the component is registered see 'ComponentFactory.h'.
        /// </summary>
        /// <param name="type">Name of the type. This must be registed. </param>
        /// <returns>GameComponent added. </returns>
        /// <remark>This should be used if the actual type is not used as less casts are used. </remark>
        std::shared_ptr<GameComponent> AddComponent(std::string type)
        {
            auto component = ComponentFactory::CreateComponent(type);
            if (component)
            {
                AddActualComponentFromObject(component);
            }

            return component;
        }

        /// <summary>
        /// Gets the first component it finds of the given type.
        /// Is not particualarly efficient at the moment,
        /// use when needed and cache results! 
        /// </summary>
        /// <returns>GameComponent of the type. </returns>
        template<typename T>
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, std::shared_ptr<T>>::type
        GetGameComponent()
        {
            // This has to be auto because we forward declared GameComponent.
            for (auto component : m_gameComponents)
            {
                std::shared_ptr<T> attempt = std::dynamic_pointer_cast<T>(component);
                if (attempt)
                {
                    return attempt;
                }
                
                // This is the prefered method but was not working with certain configurations.
                // This might start working when we move to proper loaders.
                // The above is not performant but so long as we cache it should be fine for now.
                //if (typeid(component) == typeid(T))
                //{
                //    return std::dynamic_pointer_cast<T>(component);
                //}
            }

            return nullptr;
        }

        /// <summary>
        /// A collision with something else has begin.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionBegin(Collision& collision);

        /// <summary>
        /// A collision is on going with another object.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionOccuring(Collision& collision);

        /// <summary>
        /// A collision has ended with something.
        /// </summary>
        /// <param name="collision">Describes the collision. </param>
        virtual void OnCollisionEnd(Collision& collision);

        /// <summary>
        /// Gets the transform on this GameObject.
        /// MUST CALL DURING/AFTER SETUP not on construction.
        /// Never fails after setup.
        /// Every gameobject has transform.
        /// </summary>
        /// <returns>The location, scale and rotation of the gameobject. </returns>
        std::shared_ptr<TransformComponent> GetTransformComponent();

        /// <summary>
        /// Gets the transform on this GameObject.
        /// MUST CALL DURING/AFTER SETUP not on construction.
        /// Never fails after setup.
        /// Every gameobject has transform.
        /// </summary>
        /// <returns>The location, scale and rotation of the gameobject. </returns>
        std::shared_ptr<Transform> GetTransform();

        /// <summary>
        /// Creates a new game object.
        /// </summary>
        /// <returns>A new game object in the scene. </returns>
        std::shared_ptr<GameObject> CreateNewGameObject();

        /// <summary>
        /// Called when GameObject is destroyed.
        /// Should be used to ensure you do not have a link back to the
        /// GameObject as a SharedPointer.
        /// </summary>
        /// <param name="guid">Guid of the GameObject.</param>
        virtual void OnGameObjectDestroyed(const Guid& guid);

        /// <summary>
        /// Destroys the game object.
        /// </summary>
        void Destroy();

        /// <summary>
        /// Is this GameObject marks for destruction.
        /// </summary>
        /// <returns>True means is marked for Destoryed. </returns>
        bool IsDestroyed() const;
        
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
        SceneLoadPackage* m_loadPackage;

        /// <summary>
        /// Just the GameObject items from Scene.
        /// </summary>
        SceneToGameObjectPackage* m_gameObjectPackage;

        /// <summary>
        /// All components currently loaded.
        /// </summary>
        FList<std::shared_ptr<GameComponent>> m_gameComponents;

        /// <summary>
        /// Cached Transform component.
        /// </summary>
        std::shared_ptr<TransformComponent> m_transform;

        /// <summary>
        /// True means a component needs setting up.
        /// </summary>
        bool m_componentNeedsSetup;

        /// <summary>
        /// True means destroyed.
        /// </summary>
        bool m_isDestroyed;

        /// <summary>
        /// Introduction into the system from the outside world.
        /// Because GameObject does not know about GameComponent from a top level
        /// we need to use the parent of all objects, Object to add a Component.
        /// This is not a massive deal as we only ever AddComponents occasionally 
        /// and it is not a common frame by frame thing.
        /// </summary>
        /// <param name="newObject">New Component as an object. </param>
        /// <return>True means Object was the correct type and added component. </return>
        bool AddActualComponentFromObject(std::shared_ptr<Object> newObject);

        /// <summary>
        /// Adds the given Component to the GameObject.
        /// Internal Method to add and setup the Component.
        /// </summary>
        /// <param name="newComponent">The new component.</param>
        void AddActualComponent(std::shared_ptr<GameComponent> newComponent);

        /// <summary>
        /// Ensures Transform is on the GameObject.
        /// This is apart of the setup.
        /// </summary>
        void EnsureTransformIsOnGameObject();
    };
}