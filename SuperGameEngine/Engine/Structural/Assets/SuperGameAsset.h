#pragma once
#include <memory>

#include "GameAsset.h"
#include "../../FatedQuestReferences.h"
#include "../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/DocumentUniversalObjectData.h"

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
    class SuperGameAsset : public GameAsset, public FatedQuestLibraries::DocumentUniversalObjectData
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="universalObject">
        /// Universal object as a stored document.
        /// </param>
        /// <param>
        /// Path to the file which loaded this actual asset.
        /// </param>
        SuperGameAsset(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject, const std::string& path);

        /// <summary>
        /// The name of the asset.
        /// </summary>
        /// <returns>The name to display for tooling. </returns>
        /// <remarks>This can be used in games but should be avoided. </remarks>
        virtual std::string GetName() const override;

        /// <summary>
        /// The path as provided as load time.
        /// This should be from the package itself.
        /// </summary>
        /// <returns>The path to the loaded file. </returns>
        virtual std::string GetPath() const override;

    protected:
        /// <summary>
        /// Get a loaded string value.
        /// Will return empty if nothing found.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or empty if nothing. </returns>
        virtual std::string GetString(const std::string& key) override
        {
            return FatedQuestLibraries::DocumentUniversalObjectData::GetString(key);
        }

        /// <summary>
        /// True when a key is loaded.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsStringLoaded(const std::string& key) override
        {
            return FatedQuestLibraries::DocumentUniversalObjectData::IsStringLoaded(key);
        }

        /// <summary>
        /// Get a loaded int value.
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>The value found or -1 if nothing. </returns>
        virtual int GetInt(const std::string& key) override
        {
            return FatedQuestLibraries::DocumentUniversalObjectData::GetInt(key);
        }

        /// <summary>
        /// True when a key is loaded. 
        /// </summary>
        /// <param name="key">Key to search for. </param>
        /// <returns>True when a key is loaded. </returns>
        virtual bool IsIntLoaded(const std::string& key) override
        {
            return FatedQuestLibraries::DocumentUniversalObjectData::IsIntLoaded(key);
        }

    private:
        /// <summary>
        /// The name of the asset.
        /// </summary>
        std::string m_name;

        /// <summary>
        /// The path as provided as load time.
        /// This should be from the package itself.
        /// </summary>
        std::string m_path;
    };
}
