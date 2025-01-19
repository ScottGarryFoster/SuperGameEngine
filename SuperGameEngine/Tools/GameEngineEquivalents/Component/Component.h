#pragma once
#include <memory>
#include <string>

#include "../../../../FatedQuest.Libraries/Observer/FEventSubscriptions.h"


namespace SuperGameEngine
{
    class SerializableProperty;
}

namespace FatedQuestLibraries
{
    class StoredDocumentNode;
    class ModifiableNode;
    class Guid;
}

using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

namespace SuperGameTools
{
    class ToolsSerializableProperty;

    /// <summary>
    /// A component which represents the data of a game component.
    /// </summary>
    class Component
    {
    public:
        virtual ~Component() = default;

        /// <summary>
        /// Event called when this objects dirty flag has changed.
        /// </summary>
        /// <returns>Event called when this objects dirty flag has changed. </returns>
        virtual std::shared_ptr<FEventSubscriptions> OnDirtyFlagChanged() const = 0;

        /// <summary>
        /// The type of the component.
        /// </summary>
        /// <returns>The type of the component. </returns>
        virtual std::string GetType() const = 0;

        /// <summary>
        /// Set new type.
        /// </summary>
        /// <param name="type">New type. </param>
        virtual void SetType(const std::string& type) = 0;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<SerializableProperty>> GetProperties() const = 0;

        /// <summary>
        /// Properties exposed and serialised in the Tools.
        /// </summary>
        /// <returns>Properties exposed and serialised in the Tools. </returns>
        virtual std::vector<std::shared_ptr<ToolsSerializableProperty>> GetToolsProperties() const = 0;

        /// <summary>
        /// Load the component from stored data.
        /// </summary>
        /// <param name="node">Node for this component. </param>
        virtual void Load(const std::shared_ptr<StoredDocumentNode>& node) = 0;

        /// <summary>
        /// Save this component.
        /// </summary>
        /// <returns>A node which contains the data, this is the component node. </returns>
        virtual std::shared_ptr<ModifiableNode> Save() const = 0;
    };
}
