#pragma once
#include <memory>
#include <unordered_map>

#include "UniversalObjectData.h"
#include "../../StoredDocument/AllReferences.h"

namespace FatedQuestLibraries
{
    /// <summary>
    /// A universal object which comes from a document.
    /// </summary>
    class DocumentUniversalObjectData : public virtual UniversalObjectData
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="metaDataDocument">
        /// Meta data document to load.
        /// </param>
        DocumentUniversalObjectData(const std::shared_ptr<StoredDocument>& metaDataDocument);

    protected:
        /// <summary>
        /// Lists all the strings in the object.
        /// </summary>
        /// <returns>All the String keys. </returns>
        virtual std::vector<std::string> ListStrings() const override;

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) const override;

        /// <summary>
        /// Lists all the Ints in the object.
        /// </summary>
        /// <returns>All the Int keys. </returns>
        virtual std::vector<std::string> ListInts() const override;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) const override;

        /// <summary>
        /// List vector4is in the object.
        /// </summary>
        /// <returns>All the keys for any Vector4Is. </returns>
        virtual std::vector<std::string> ListVector4Is() const override;

        /// <summary>
        /// Get a loaded Vector4I value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if not found. </returns>
        virtual std::shared_ptr<FVector4I> GetVector4I(const std::string& key) const override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsVector4ILoaded(const std::string& key) const override;

    private:
        /// <summary>
        /// Loaded string values from file.
        /// </summary>
        std::unordered_map<std::string, std::string> m_stringValues;

        /// <summary>
        /// Loaded int values from file.
        /// </summary>
        std::unordered_map<std::string, int> m_intValues;

        /// <summary>
        /// Loaded FVector4I values from file.
        /// </summary>
        std::unordered_map<std::string, std::shared_ptr<FVector4I>> m_vector4IValues;

        void ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringsNode);
        void ParseStoredDocumentSingleString(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringNode);
        void ParseStoredDocumentInts(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intsNode);
        void ParseStoredDocumentSingleInt(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intNode);

        void ParseStoredDocumentVector4I(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node);
        void ParseStoredDocumentSingleVector4I(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& node);
    };

}