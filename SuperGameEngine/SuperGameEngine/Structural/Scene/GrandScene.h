#pragma once
#include <SDL.h>
#include "SceneLoadPackage.h"
#include "Scene.h"
#include "../../Engine/Input/DirectInput.h"
#include "../../Engine/Graphics/Technique/TechniqueRenderer.h"
#include "SceneToGameObjectPackage.h"

namespace SuperGameEngine
{
    class CollisionDectection;

    /// <summary>
    /// Holds everything in the entire game.
    /// </summary>
    class GrandScene
    {
    public:
        GrandScene(SDL_Renderer* renderer);
        ~GrandScene();

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        bool Update(Uint64 tick);

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        void Draw();

        /// <summary>
        /// Updates all the objects which require knowleadge from an SDL level.
        /// This would be Key Input for instance.
        /// This is sent directly before the GrandScene Update.
        /// </summary>
        /// <param name="e">Event last sent from the update loop.</param>
        void EventUpdate(SDL_Event& e);

        /// <summary>
        /// Creates new Game Object in the scene.
        /// </summary>
        /// <param name="caller">
        /// GameObject which called the Method. Used to create a GameObject in the same scene.
        /// </param>
        /// <returns>New Game Object in the Scene.</returns>
        std::shared_ptr<GameObject> CreateNewGameObject(GameObject* caller);

    private:
        /// <summary>
        /// Contains all the objects a GameObject needs to opperate.
        /// Can be given to other GameObjets freely.
        /// </summary>
        SceneLoadPackage* m_sceneLoadPackage;

        /// <summary>
        /// Objects for the GameObject to operate which GameComponents do not need
        /// to worry about. Things like Collision which the GameObject should help
        /// manage but the Components should feel like are 'managed' by the GameObject.
        /// </summary>
        SceneToGameObjectPackage* m_sceneToGameObjectPackage;

        /// <summary>
        /// All the Scenes loaded.
        /// </summary>
        std::vector<Scene*> m_scenes;

        /// <summary>
        /// Manages user input directly.
        /// </summary>
        DirectInput* m_directInput;

        /// <summary>
        /// Renders techniques which for the most part are primitives.
        /// </summary>
        TechniqueRenderer* m_techniqueRenderer;

        /// <summary>
        /// Controls when Loops occur.
        /// </summary>
        FrameTiming* m_frameTimings;

        /// <summary>
        /// Handles Collision Detection on a high level.
        /// </summary>
        CollisionDectection* m_collisionDectection;

        /// <summary>
        /// Keeps a record of the current fixed update timing.
        /// </summary>
        Uint64 m_currentFixedUpdateTicks;

        /// <summary>
        /// Used to run code once a second.
        /// </summary>
        /// <remark>
        /// This is only here to testing. Will remove when we create proper yeilds.
        /// </remark>
        Uint64 m_singleSecondCountdown;
    };
}