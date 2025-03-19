#pragma once
#include <string>
#include "../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/DocumentUniversalObjectData.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Base class for all Assets and provides the base data for assets.
    /// Assets in this context are data provided for the game and the data
    /// is contextual setup such as how to split a texture or how to use a
    /// piece of music.
    /// </summary>
    class GameAsset : public FatedQuestLibraries::DocumentUniversalObjectData
    {
    public:
        // To inherit constructor.
        using FatedQuestLibraries::DocumentUniversalObjectData::DocumentUniversalObjectData;

        /// <summary>
        /// The name of the asset.
        /// </summary>
        /// <returns>The name to display for tooling. </returns>
        /// <remarks>This can be used in games but should be avoided. </remarks>
        virtual std::string GetName() const = 0;
    };
}
