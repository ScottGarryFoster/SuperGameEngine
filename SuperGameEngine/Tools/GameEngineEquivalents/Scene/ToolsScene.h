#pragma once
#include <memory>

#include "Scene.h"
#include "../../Engine/Graphics/ImGuiSuperTexture.h"

namespace SuperGameEngine
{
    class SerializableParser;
}

namespace SuperGameTools
{
    class SceneDocument;

    /// <summary>
    /// Holds game objects.
    /// </summary>
    class ToolsScene : public Scene, public FEventObserver
    {
    public:
        ToolsScene(
            const std::shared_ptr<SuperGameEngine::SerializableParser>& parser, 
            const std::shared_ptr<SceneDocument>& document);

        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDirtyFlagChanged() const override;

        /// <summary>
        /// Saves Scene.
        /// </summary>
        /// <returns></returns>
        virtual bool Save() const override;

        /// <summary>
        /// Loads scene.
        /// </summary>
        virtual bool Load() override;

        /// <summary>
        /// Gets all game objects in scene.
        /// </summary>
        /// <returns>All game objects in scene. </returns>
        virtual std::vector<std::shared_ptr<GameObject>> GetGameObjects() const override;

        /// <summary>
        /// True when there is unsaved data.
        /// </summary>
        /// <returns>True when there is unsaved data. </returns>
        virtual bool GetDirty() const override;

        /// <summary>
        /// Mark Scene Dirty.
        /// </summary>
        virtual void MarkDirty() override;

        /// <summary>
        /// Adds a game object to the scene.
        /// </summary>
        /// <param name="gameObject">New game object. </param>
        virtual void AddGameObject(const std::shared_ptr<GameObject>& gameObject) override;

        /// <summary>
        /// Deletes GameObject.
        /// </summary>
        /// <param name="gameObject">Game Object to erase. </param>
        virtual void RemoveGameObject(const std::shared_ptr<GameObject>& gameObject) override;

        /// <summary>
        /// Deletes Component.
        /// </summary>
        /// <param name="gameObject">Game Object component is on. </param>
        /// <param name="component">Component to erase. </param>
        virtual void RemoveComponentFromGameObject(
            const std::shared_ptr<GameObject>& gameObject,
            const std::shared_ptr<Component>& component) override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;

    private:
        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        std::shared_ptr<FEvent> m_onDirtyFlagChanged;

        /// <summary>
        /// Helps parse the data in and out of stored documents.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_parser;

        /// <summary>
        /// Input and output to the file source.
        /// </summary>
        std::shared_ptr<SceneDocument> m_sceneDocument;

        /// <summary>
        /// Scene guid.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// All game objects at the top level.
        /// </summary>
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;

        /// <summary>
        /// True when there is unsaved data.
        /// </summary>
        std::shared_ptr<bool> m_dirtyFlag;

        /// <summary>
        /// Call to update the dirty flag.
        /// </summary>
        /// <param name="newValue">New value for dirty. </param>
        void UpdateDirtyFlag(bool newValue) const;
    };
}
