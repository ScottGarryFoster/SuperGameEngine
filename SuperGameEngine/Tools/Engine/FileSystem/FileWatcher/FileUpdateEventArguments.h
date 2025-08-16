#pragma once
#include <string>
#include <vector>

#include "../../../../../FatedQuest.Libraries/Observer/FEventArguments.h"

namespace SuperGameTools
{
    /// <summary>
    /// When files have been updated or added this contains the information on files have been updated.
    /// </summary>
    class FileUpdateEventArguments : public FatedQuestLibraries::FEventArguments
    {
    public:

        FileUpdateEventArguments(
            const std::vector<std::string>& addedFiles, 
            const std::vector<std::string>& updatedFiles,
            const std::vector<std::string>& deletedFiles);

        /// <summary>
        /// Returns all the files added.
        /// </summary>
        /// <returns>All the new files, relative to the game package. </returns>
        std::vector<std::string> GetFilesAdded() const;

        /// <summary>
        /// Returns all the files updated.
        /// </summary>
        /// <returns>All the files which have updated, relative to the game package.</returns>
        std::vector<std::string> GetFilesUpdated() const;

        /// <summary>
        /// Returns all the files deleted.
        /// </summary>
        /// <returns>All the files which have deleted, relative to the game package.</returns>
        std::vector<std::string> GetFilesDeleted() const;

    private:

        /// <summary>
        /// All the new files, relative to the game package.
        /// </summary>
        std::vector<std::string> m_filesAdded;

        /// <summary>
        /// All the files which have updated, relative to the game package.
        /// </summary>
        std::vector<std::string> m_filesUpdated;

        /// <summary>
        /// All the files which have deleted, relative to the game package.
        /// </summary>
        std::vector<std::string> m_filesDeleted;
    };
}
