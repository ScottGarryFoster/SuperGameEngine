#pragma once
#include "Document.h"

namespace SuperGameTools
{
    /// <summary>
    /// Basic implementation of Document.
    /// </summary>
    class ToolsDocument : public Document
    {
    public:
        virtual ~ToolsDocument() override = default;

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
            const std::shared_ptr<PackagePaths>& packagePaths) override;

        /// <summary>
        /// Gets the filepath from the game package source.
        /// </summary>
        /// <returns>The filepath from the game package source. </returns>
        virtual std::string GetFilepath() const override;

        /// <summary>
        /// Gets the filename with extension.
        /// </summary>
        /// <returns>The file name. </returns>
        virtual std::string GetFilename() const override;

    protected:
        /// <summary>
        /// Filepath from game package.
        /// </summary>
        std::string m_filePath;

        /// <summary>
        /// File name.
        /// </summary>
        std::string m_fileName;

        /// <summary>
        /// Path to the products folder.
        /// </summary>
        std::string m_productsPath;

        /// <summary>
        /// Holds the content for the game.
        /// </summary>
        std::shared_ptr<GamePackage> m_gamePackage;

        /// <summary>
        /// Helper class to grab paths.
        /// </summary>
        std::shared_ptr<PackagePaths> m_packagePaths;
    };
}

