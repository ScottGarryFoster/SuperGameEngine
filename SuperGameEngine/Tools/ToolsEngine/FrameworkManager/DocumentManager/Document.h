#pragma once
#include <memory>
#include <string>

namespace SuperGameTools
{
    class WindowPackage;

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
        /// <param name="filepath">Filepath from game package. </param>
        /// <param name="m_windowsPackage">Everything needed to load and save. </param>
        virtual void Setup(const std::string& filepath, const std::weak_ptr<WindowPackage>& m_windowsPackage) = 0;

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
        virtual void Load() = 0;

        /// <summary>
        /// Saves the document.
        /// </summary>
        virtual void Save() = 0;
    };
}

