#pragma once
#include "ProjectProperties.h"
#include "../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/DocumentUniversalObjectData.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The foundational properties for setting up the project for the product.
    /// </summary>
    class SuperProjectProperties : public virtual ProjectProperties, public FatedQuestLibraries::DocumentUniversalObjectData
    {
    public:

        /// <summary>
        /// Load the project properties from file.
        /// </summary>
        /// <param name="universalObject">Stored document in the format of a universal data object. </param>
        SuperProjectProperties(const std::shared_ptr<FatedQuestLibraries::StoredDocument>& universalObject);

        /// <summary>
        /// Get the first scene to load.
        /// </summary>
        /// <returns>The first scene to load as defined by the Project Properties. </returns>
        virtual std::string GetStartScene() const override;

        /// <summary>
        /// Get the title text for the window.
        /// </summary>
        /// <returns>The title for the window. </returns>
        virtual std::string GetWindowTitle() const override;
    };
}
