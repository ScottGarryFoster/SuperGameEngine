#pragma once
#include <memory>
#include <string>

namespace FatedQuestLibraries
{
    class PackagePaths;
    class GamePackage;
}

using namespace FatedQuestLibraries;

namespace SuperGameTools
{
    /// <summary>
    /// An asset which can be loaded into the tools.
    /// </summary>
    class Document
    {
    public:
        virtual ~Document() = default;

        /// <summary>
        /// Called directly after construction.
        /// Required as only certain things have certain elements of the setup.
        /// </summary>
        /// <param name="filepath">Holds the content for the game. </param>
        /// <param name="gamePackage">Holds the content for the game. </param>
        /// <param name="packagePaths">Helper class to grab paths. </param>
        virtual void Setup(
            const std::string& filepath, 
            const std::shared_ptr<GamePackage>& gamePackage,
            const std::shared_ptr<PackagePaths>& packagePaths) = 0;

        /// <summary>
        /// Gets the filepath from the game package source.
        /// </summary>
        /// <returns>The filepath from the game package source. </returns>
        virtual std::string GetFilepath() const = 0;

        /// <summary>
        /// Gets the filename with extension.
        /// </summary>
        /// <returns>The file name. </returns>
        virtual std::string GetFilename() const = 0;

        /// <summary>
        /// Loads the document.
        /// </summary>
        /// <returns>True means loaded. </returns>
        virtual bool Load() = 0;

        /// <summary>
        /// Saves the document.
        /// </summary>
        /// <returns>True means saved. </returns>
        virtual bool Save() = 0;

        /// <summary>
        /// Create a new version of this file.
        /// Ideally this should be quite empty however
        /// if anything is required to load the file,
        /// include it.
        /// </summary>
        /// <returns>True means could create. </returns>
        virtual bool Create() = 0;
    };
}

