#pragma once
#include "GameObject.h"
#include "../../../../FatedQuest.Libraries/Observer/FEventObserver.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameEngine
{
    class SerializableParser;
}

namespace SuperGameTools
{
    /// <summary>
    /// A game object with the things which Tools are concerned with.
    /// </summary>
    class ToolsGameObject : public GameObject, public FEventObserver
    {
    public:
        virtual ~ToolsGameObject() override = default;
        ToolsGameObject(const std::shared_ptr<SuperGameEngine::SerializableParser>& parser);

        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDirtyFlagChanged() const override;

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

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FEventArguments> arguments) override;
    private:
        /// <summary>
        /// Called when dirtied.
        /// </summary>
        std::shared_ptr<FEvent> m_onDirtyFlagChanged;

        /// <summary>
        /// True when there is unsaved data.
        /// </summary>
        std::shared_ptr<bool> m_dirty;

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

        /// <summary>
        /// Call to update the dirty flag.
        /// </summary>
        /// <param name="newValue">New value for dirty. </param>
        void UpdateDirtyFlag(bool newValue) const;
    };
}
