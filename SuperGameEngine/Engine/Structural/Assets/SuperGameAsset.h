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
        SuperGameAsset(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject);

        /// <summary>
        /// The name of the asset.
        /// </summary>
        /// <returns>The name to display for tooling. </returns>
        /// <remarks>This can be used in games but should be avoided. </remarks>
        virtual std::string GetName() const override;

    private:
        /// <summary>
        /// The name of the asset.
        /// </summary>
        std::string m_name;
    };
}
