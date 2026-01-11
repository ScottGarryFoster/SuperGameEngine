#pragma once
#include "../../../../FatedQuest.Libraries/StandardObjects/UniversalObjectData/UniversalObjectData.h"

namespace SuperGameEngine
{
    /// <summary>
    /// The foundational properties for setting up the project for the product.
    /// </summary>
    class ProjectProperties : public virtual FatedQuestLibraries::UniversalObjectData
    {
    public:
        /// <summary>
        /// Get the first scene to load.
        /// </summary>
        /// <returns>The first scene to load as defined by the Project Properties. </returns>
        virtual std::string GetStartScene() const = 0;

        /// <summary>
        /// Get the title text for the window.
        /// </summary>
        /// <returns>The title for the window. </returns>
        virtual std::string GetWindowTitle() const = 0;
    };
}