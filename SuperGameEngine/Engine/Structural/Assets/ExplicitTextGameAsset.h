#pragma once
#include "SuperGameAsset.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A test game asset which explicitly exposes the file contents.
    /// This is used for debugging as it is not particularly useful outside of reading a
    /// game asset file.
    /// </summary>
    class ExplicitTextGameAsset : public SuperGameAsset
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="metaDataDocument">
        /// Meta data document to load.
        /// </param>
        ExplicitTextGameAsset(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& metaDataDocument);

        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        std::string GetString(const std::string& key) override;

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        bool IsStringLoaded(const std::string& key) override;

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        int GetInt(const std::string& key) override;

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        bool IsIntLoaded(const std::string& key) override;
    };
}

