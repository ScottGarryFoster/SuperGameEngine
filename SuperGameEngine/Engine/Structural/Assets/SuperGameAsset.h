#pragma once
#include <memory>

#include "GameAsset.h"
#include "../../FatedQuestReferences.h"

namespace FatedQuestLibraries
{
    class StoredDocument;
}

namespace SuperGameEngine
{
    /// <summary>
    /// Base class for all Assets and provides the base data for assets.
    /// Assets in this context are data provided for the game and the data
    /// is contextual setup such as how to split a texture or how to use a
    /// piece of music.
    /// </summary>
    class SuperGameAsset : public GameAsset
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="metaDataDocument">
        /// Meta data document to load.
        /// </param>
        SuperGameAsset(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& metaDataDocument);

        /// <summary>
        /// The name of the asset.
        /// </summary>
        /// <returns>The name to display for tooling. </returns>
        /// <remarks>This can be used in games but should be avoided. </remarks>
        virtual std::string GetName() const override;

    protected:
        // This should only contain the raw data loaded from file
        // to give to the derivative types.

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) override;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) override;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) override;

    private:
        /// <summary>
        /// The name of the asset.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// Loaded string values from file.
        /// </summary>
        std::unordered_map<std::string, std::string> m_stringValues;

        /// <summary>
        /// Loaded int values from file.
        /// </summary>
        std::unordered_map<std::string, int> m_intValues;

        void ParseStoredDocumentGameAssetMetadata(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& gameAssetNode);
        void ParseStoredDocumentStrings(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringsNode);
        void ParseStoredDocumentSingleString(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& stringNode);
        void ParseStoredDocumentInts(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intsNode);
        void ParseStoredDocumentSingleInt(const std::shared_ptr<FatedQuestLibraries::StoredDocumentNode>& intNode);
    };
}
