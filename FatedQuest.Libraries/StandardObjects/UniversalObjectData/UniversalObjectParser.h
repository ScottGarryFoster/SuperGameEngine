#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace FatedQuestLibraries
{
    class ModifiableNode;
    class FVector4I;
    class StoredDocumentNode;

    /// <summary>
    /// Provides methods to parse in and out of Universal Object Data.
    /// </summary>
    class UniversalObjectParser
    {
    public:
        /// <summary>
        /// Creates a strings node from the given values.
        /// </summary>
        /// <param name="strings">The <c>Strings</c> values. </param>
        /// <returns>The <c>Strings</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateStringsNode(
            const std::unordered_map<std::string, std::string>& strings) const;

        /// <summary>
        /// Creates a string node from the given values.
        /// </summary>
        /// <param name="key">The string key. </param>
        /// <param name="value">The string value. </param>
        /// <returns>The <c>String</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateStringNode(
            const std::string& key, const std::string& value) const;

        /// <summary>
        /// Parse the <c>Strings</c> node.
        /// </summary>
        /// <param name="stringsNode">The <c>Strings</c> node to parse. </param>
        /// <returns>The parsed result. </returns>
        std::unordered_map<std::string, std::string> ParseStoredDocumentStrings(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringsNode) const;

        /// <summary>
        /// Parse the <c>String</c> node.
        /// </summary>
        /// <param name="stringNode">The <c>String</c> node to parse. </param>
        /// <returns>
        /// The parsed result.
        /// Key is required therefore an empty key means failed to parse.
        /// </returns>
        std::pair<std::string, std::string> ParseStoredDocumentSingleString(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringNode) const;

        /// <summary>
        /// Creates an ints node from the given values.
        /// </summary>
        /// <param name="strings">The <c>Ints</c> values. </param>
        /// <returns>The <c>Ints</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateIntsNode(
            const std::unordered_map<std::string, int>& ints) const;

        /// <summary>
        /// Creates a int node from the given values.
        /// </summary>
        /// <param name="key">The int key. </param>
        /// <param name="value">The int value. </param>
        /// <returns>The <c>Int</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateIntNode(
            const std::string& key, const int& value) const;

        /// <summary>
        /// Parse the <c>Ints</c> node.
        /// </summary>
        /// <param name="intsNode">The <c>Ints</c> node to parse. </param>
        /// <returns>The parsed result. </returns>
        std::unordered_map<std::string, int> ParseStoredDocumentInts(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intsNode) const;

        /// <summary>
        /// Parse the <c>Ints</c> node.
        /// </summary>
        /// <param name="intNode">The <c>Ints</c> node to parse. </param>
        /// <returns>
        /// The parsed result.
        /// Key is required therefore an empty key means failed to parse.
        /// </returns>
        std::pair<std::string, int> ParseStoredDocumentSingleInt(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intNode) const;

        /// <summary>
        /// Creates an Vector4Is node from the given values.
        /// </summary>
        /// <param name="strings">The <c>Vector4Is</c> values. </param>
        /// <returns>The <c>Vector4Is</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateVector4IsNode(
            const std::unordered_map<std::string, std::shared_ptr<FVector4I>>& vector4Is) const;

        /// <summary>
        /// Creates a Vector4I node from the given values.
        /// </summary>
        /// <param name="key">The Vector4I key. </param>
        /// <param name="value">The Vector4I value. </param>
        /// <returns>The <c>Vector4I</c> parsed into a node. </returns>
        std::shared_ptr<FatedQuestLibraries::ModifiableNode> CreateVector4INode(
            const std::string& key, const std::shared_ptr<FVector4I>& value) const;

        /// <summary>
        /// Parse the <c>Vector4Is</c> node.
        /// </summary>
        /// <param name="node">The <c>Ints</c> node to parse. </param>
        /// <returns>The parsed result. </returns>
        std::unordered_map<std::string, std::shared_ptr<FVector4I>> ParseStoredDocumentVector4I(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node) const;

        /// <summary>
        /// Parse the <c>Vector4Is</c> node.
        /// </summary>
        /// <param name="node">The <c>Ints</c> node to parse. </param>
        /// <returns>
        /// The parsed result.
        /// Key is required therefore an empty key means failed to parse.
        /// </returns>
        std::pair<std::string, std::shared_ptr<FVector4I>> ParseStoredDocumentSingleVector4I(
            const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node) const;
    };
}
