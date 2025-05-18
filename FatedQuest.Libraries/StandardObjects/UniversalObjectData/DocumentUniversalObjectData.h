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

    private:
        /// <summary>
        /// Loaded string values from file.
        /// </summary>
        std::unordered_map<std::string, std::string> m_stringValues;

        /// <summary>
        /// Loaded int values from file.
        /// </summary>
        std::unordered_map<std::string, int> m_intValues;

        void ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringsNode);
        void ParseStoredDocumentSingleString(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringNode);
        void ParseStoredDocumentInts(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intsNode);
        void ParseStoredDocumentSingleInt(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intNode);
    };

}