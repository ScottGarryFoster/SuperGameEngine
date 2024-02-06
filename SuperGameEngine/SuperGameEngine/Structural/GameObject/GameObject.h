#pragma once
#include <type_traits>

#include "../../Engine/Basic/GameTime.h"
#include <vector>
#include "../Scene/SceneLoadPackage.h"
using namespace StandardCLibrary;

namespace SuperGameEngine
{
    class GameComponent;

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

        template<typename T>
        typename std::enable_if<std::is_base_of<GameComponent, T>::value, T*>::type
        AddComponent()
        {
            T* newComponent = new T();
            Object* componentPtr = static_cast<Object*>(newComponent);
            AddActualComponentFromObject(componentPtr);
            return newComponent;
        }
        
    private:

        /// <summary>
        /// Everything passed down from the scene.
        /// </summary>
        SceneLoadPackage* m_loadPackage;

        /// <summary>
        /// All components currently loaded.
        /// </summary>
        std::vector<GameComponent*> m_gameComponents;

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
    };
}