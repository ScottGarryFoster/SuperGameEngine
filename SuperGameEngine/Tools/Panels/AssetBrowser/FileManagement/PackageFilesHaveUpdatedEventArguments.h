#pragma once
#include <memory>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    class AssetFolder;

    /// <summary>
    /// Provides important information about how to display Files in the event the
    /// package has updated.
    /// </summary>
    class PackageFilesHaveUpdatedEventArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        PackageFilesHaveUpdatedEventArguments(const std::shared_ptr<AssetFolder>& root);

        /// <summary>
        /// Gets the new root from the loaded version.
        /// </summary>
        /// <returns>Gets the new root folder. </returns>
        std::shared_ptr<AssetFolder> GetNewRoot();

    private:

        /// <summary>
        /// The new root.
        /// </summary>
        std::shared_ptr<AssetFolder> m_rootFolder;
    };
}
