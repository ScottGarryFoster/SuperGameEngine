#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class StoredDocument;
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

        /// <summary>
        /// Will search for project properties to find the file.
        /// If it finds a file it could in theory load, returns true.
        /// </summary>
        /// <param name="gamePackage">All the files loaded for the product. </param>
        /// <returns>True means there is a valid project properties file to load. </returns>
        bool CanLoadProjectProperties(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) const;

        /// <summary>
        /// Gets the path of a project properties file.
        /// Will return empty is file does not exist.
        /// </summary>
        /// <param name="gamePackage">All the files loaded for the product. </param>
        /// <returns>The path of the project properties file or empty if none exists. </returns>
        std::string GetProjectPropertiesPath(const std::shared_ptr<FatedQuestLibraries::GamePackage>& gamePackage) const;

    private:

        /// <summary>
        /// The file name to look for in the file system for a project properties file.
        /// </summary>
        const char* m_projectPropertiesFileName = "ProjectProperties.uod";

        /// <summary>
        /// Creates the actual project properties file.
        /// </summary>
        /// <param name="storedDocument">The information for the actual properties. </param>
        /// <returns>The created project properties. </returns>
        /// <remarks>This is virtual to allow the Tools to create an edited </remarks>
        virtual std::shared_ptr<ProjectProperties> CreateProjectProperties(
            const std::shared_ptr<FatedQuestLibraries::StoredDocument>& storedDocument) const;
    };
}
