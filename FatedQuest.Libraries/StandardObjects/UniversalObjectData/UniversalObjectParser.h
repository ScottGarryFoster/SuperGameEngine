#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace FatedQuestLibraries
{
    class FVector4I;
    class StoredDocumentNode;

    /// <summary>
    /// Provides methods to parse in and out of Universal Object Data.
    /// </summary>
    class UniversalObjectParser
    {
    public:

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
