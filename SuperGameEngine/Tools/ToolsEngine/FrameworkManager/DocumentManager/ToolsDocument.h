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
        /// <param name="filepath">Filepath from game package. </param>
        /// <param name="windowsPackage">Everything needed to load and save. </param>
        virtual void Setup(const std::string& filepath, const std::weak_ptr<WindowPackage>& windowsPackage) override;

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
        /// Everything needed to load and save.
        /// </summary>
        std::weak_ptr<WindowPackage> m_windowsPackage;
    };
}

