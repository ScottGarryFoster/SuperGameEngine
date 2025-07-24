#pragma once
#include "../../../FatedQuestLibraries.h"

namespace SuperGameTools
{
    /// <summary>
    /// Contains tools differences to the game package.
    /// </summary>
    /// <remarks>
    /// Note that the game package is always the literal file version within tools.
    /// </remarks>
    class ToolsGamePackageFileSystemDirectory : public FatedQuestLibraries::GamePackageFileSystemDirectory
    {
    public:
        ToolsGamePackageFileSystemDirectory(const std::shared_ptr<FatedQuestLibraries::PackageFiles>& files);

        /// <summary>
        /// Adds the path to the given collection.
        /// </summary>
        /// <param name="collection">Collection, meaning the dictionary of dictionaries. </param>
        /// <param name="directory">The key or directory. </param>
        /// <param name="rawPath">
        /// The raw path to be processed.
        /// </param>
        virtual void AddPathToCollection(
            std::unordered_map<std::string, std::unordered_set<std::string>>& collection,
            const std::string& directory,
            const std::string& rawPath) const override;
    };
}
