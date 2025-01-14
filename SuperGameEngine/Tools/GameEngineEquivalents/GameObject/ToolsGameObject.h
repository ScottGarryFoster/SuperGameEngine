#pragma once
#include "GameObject.h"

namespace SuperGameEngine
{
    class SerializableParser;
}

namespace SuperGameTools
{
    /// <summary>
    /// A game object with the things which Tools are concerned with.
    /// </summary>
    class ToolsGameObject : public GameObject
    {
    public:
        virtual ~ToolsGameObject() override = default;
        ToolsGameObject(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser);

        /// <summary>
        /// Guid for the game object.
        /// </summary>
        /// <returns>Guid for the game object. </returns>
        virtual std::shared_ptr<Guid> GetGuid() const override;

        /// <summary>
        /// Describes the group for the selectable which helps to decide the
        /// buckets that the selectable will be added to.
        /// </summary>
        /// <returns>The group or groups for this selectable. </returns>
        virtual std::unordered_set<SelectionGroup> GetSelectionGroup() const override;

        /// <summary>
        /// Set guid for the game object.
        /// </summary>
        /// <param name="guid">New guid. </param>
        virtual void SetGuid(const std::shared_ptr<Guid>& guid) override;

        /// <summary>
        /// Get components.
        /// </summary>
        /// <returns>Components on game object. </returns>
        virtual std::shared_ptr<std::vector<std::shared_ptr<Component>>> GetComponents() const override;

        /// <summary>
        /// Load the game object from stored data.
        /// </summary>
        /// <param name="node">Node for this game object. </param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& node) override;

        /// <summary>
        /// Save this game object.
        /// </summary>
        /// <returns>A node which contains the data, this is the game object node. </returns>
        virtual std::shared_ptr<ModifiableNode> Save() const override;

    private:
        /// <summary>
        /// Helps to parse serializable objects.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SerializableParser> m_serializableParser;

        /// <summary>
        /// Components on the game object.
        /// </summary>
        std::shared_ptr<std::vector<std::shared_ptr<Component>>> m_components;

        /// <summary>
        /// Guid for the game object.
        /// </summary>
        std::shared_ptr<Guid> m_guid;

        /// <summary>
        /// The groups for this selectable.
        /// </summary>
        std::unordered_set<SelectionGroup> m_selectionGroups;
    };
}
