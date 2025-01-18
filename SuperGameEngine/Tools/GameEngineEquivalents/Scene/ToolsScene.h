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
    class ToolsScene : public Scene
    {
    public:
        ToolsScene(
            const std::shared_ptr<SuperGameEngine::SerializableParser>& parser, 
            const std::shared_ptr<SceneDocument>& document);

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

    private:
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
    };
}
