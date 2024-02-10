#pragma once
#include <type_traits>

#include "../../Engine/Basic/GameTime.h"
#include <vector>
#include "../Scene/SceneLoadPackage.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class GameComponent;
    class TransformComponent;

    /// <summary>
    /// Core object in the Engine holding Components with Logic and
    /// managing how these components move around and collide.
    /// </summary>
    class GameObject : public Object
    {
    public:
        GameObject();
        virtual ~GameObject();

        /// <summary>
        /// Sets up the GameObject.
        /// </summary>
        /// <param name="loadPackage">Everything a GameObject needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage);

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(GameTime gameTime);

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
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, T*>::type
        AddComponent()
        {
            T* newComponent = new T();
            Object* componentPtr = static_cast<Object*>(newComponent);
            AddActualComponentFromObject(componentPtr);
            return newComponent;
        }

        /// <summary>
        /// Gets the first component it finds of the given type.
        /// Is not particualarly efficient at the moment,
        /// use when needed and cache results! 
        /// </summary>
        /// <returns>GameComponent of the type. </returns>
        template<typename T>
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, T*>::type
        GetGameComponent()
        {
            for (auto component : m_gameComponents)
            {
                if (typeid(component) == typeid(T))
                {
                    return dynamic_cast<T*>(component);
                }
            }

            return nullptr;
        }

        TransformComponent* GetTransform();
        
    private:

        /// <summary>
        /// Everything passed down from the scene.
        /// </summary>
        SceneLoadPackage* m_loadPackage;

        /// <summary>
        /// All components currently loaded.
        /// </summary>
        FList<GameComponent*> m_gameComponents;

        /// <summary>
        /// Cached Transform component.
        /// </summary>
        TransformComponent* m_transform;

        /// <summary>
        /// Introduction into the system from the outside world.
        /// Because GameObject does not know about GameComponent from a top level
        /// we need to use the parent of all objects, Object to add a Component.
        /// This is not a massive deal as we only ever AddComponents occasionally 
        /// and it is not a common frame by frame thing.
        /// </summary>
        /// <param name="newObject">New Component as an object. </param>
        /// <return>True means Object was the correct type and added component. </return>
        bool AddActualComponentFromObject(Object* newObject);

        /// <summary>
        /// Adds the given Component to the GameObject.
        /// Internal Method to add and setup the Component.
        /// </summary>
        /// <param name="newComponent">The new component.</param>
        void AddActualComponent(GameComponent* newComponent);

        /// <summary>
        /// Ensures Transform is on the GameObject.
        /// This is apart of the setup.
        /// </summary>
        void EnsureTransformIsOnGameObject();
    };
}