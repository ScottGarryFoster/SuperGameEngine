#pragma once
#include <memory>
#include <string>

#include "SerializableParser.h"

using namespace FatedQuestLibraries;

namespace SuperGameEngine
{
    /// <summary>
    /// Helps to parse serializable objects.
    /// </summary>
    class SuperSerializableParser : public SerializableParser
    {
    public:
        /// <summary>
        /// Serialises a game component to a document node.
        /// This is only the top level, you must serialise any internal properties.
        /// </summary>
        /// <param name="gameComponent">Value of the game component. </param>
        /// <returns>A node representing the top level of the Game Component. </returns>
        virtual std::shared_ptr<ModifiableNode> Serialize(const std::shared_ptr<GameComponent>& gameComponent) const;

        /// <summary>
        /// Serialises a string to a document node.
        /// </summary>
        /// <param name="name">Name of the property. </param>
        /// <param name="value">Value of the property. </param>
        /// <param name="defaultValue">Value which is default in the class anyway. </param>
        /// <returns>A document node representing the property. </returns>
        virtual std::shared_ptr<ModifiableNode> Serialize(const std::string& name, const std::string& value, const std::string& defaultValue) const override;

        /// <summary>
        /// Parses the given property from the parent which owns the value.
        /// The StoredDocumentNode should have this property as a child (or potentially).
        /// </summary>
        /// <param name="name">Name of the property. </param>
        /// <param name="defaultValue">If not found, the value to return. </param>
        /// <param name="parentOfProperties">Parent of the property. </param>
        /// <returns>The parsed value of the property or the default. </returns>
        virtual std::string ParseFromParent(const std::string& name, const std::string& defaultValue, const std::shared_ptr<StoredDocumentNode>& parentOfProperties) const override;

        /// <summary>
        /// Parses the given property from the node which owns the value.
        /// </summary>
        /// <param name="defaultValue">If not found, the value to return. </param>
        /// <param name="data">Node containing the data. </param>
        /// <returns>The parsed value of the property or the default. </returns>
        virtual std::string Parse(const std::string& defaultValue, const std::shared_ptr<StoredDocumentNode>& data) const override;
    };
}
