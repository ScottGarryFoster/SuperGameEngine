#pragma once
#include <memory>

namespace FatedQuestLibraries
{
    class PackagePaths;
    class GamePackage;
}

namespace SuperGameEngine
{
    class ProjectProperties;

    /// <summary>
    /// Loads and Project Property file and provides the results.
    /// </summary>
    class ProjectPropertiesProvider
    {
    public:

        /// <summary>
        /// Loads project properties from file if possible.
        /// </summary>
        /// <param name="gamePackage">All the files loaded for the product. </param>
        /// <returns>The loaded project properties or empty pointer if it could not be loaded.</returns>
        std::shared_ptr<ProjectProperties> LoadProjectProperties(
            const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) const;

    private:

        /// <summary>
        /// The file name to look for in the file system for a project properties file.
        /// </summary>
        const char* m_prjectPropertiesFileName = "ProjectProperties.uod";
    };
}
