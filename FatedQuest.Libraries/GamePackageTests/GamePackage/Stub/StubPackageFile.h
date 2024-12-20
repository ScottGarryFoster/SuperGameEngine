#pragma once
#include <string>
#include <vector>

#include "../../../GamePackage/GamePackage/PackageFile.h"

using namespace FatedQuestLibraries;

namespace FatedQuestLibraries_GamePackage
{
    /// <summary>
    /// A file within a game package.
    /// </summary>
    class StubPackageFile : public PackageFile
    {
    public:
        /// <summary>
        /// Returns file path.
        /// </summary>
        /// <returns>File path of the file. </returns>
        virtual std::string Path() const { return m_path; }
        std::string m_path = {};

        /// <summary>
        /// File path with all directories split into elements of a vector.
        /// </summary>
        /// <returns>File path with all directories split into elements of a vector. </returns>
        virtual std::vector<std::string> PathByDirectory() const { return m_pathByDirectory; }
        std::vector<std::string> m_pathByDirectory = {};

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::string ReadFileContents() { return m_fileContents; }
        std::string m_fileContents = {};

        /// <summary>
        /// Reads file contents.
        /// </summary>
        /// <returns>File contents. </returns>
        virtual std::vector<std::string> ReadFileContentsByLine() { return m_fileContentsByLine; }
        std::vector<std::string> m_fileContentsByLine = {};

        /// <summary>
        /// Looks for the given suffix on the filepath.
        /// </summary>
        /// <param name="extension">Extension to look for. </param>
        /// <returns>True means has extension. </returns>
        virtual bool EndInExtension(const std::string& extension) const { return m_endInExtension; }
        bool m_endInExtension = false;

        /// <summary>
        /// Gets the filename with extension.
        /// </summary>
        /// <returns>Filename with extension. </returns>
        virtual std::string FileName() const { return m_fileName; }
        std::string m_fileName = {};

        /// <summary>
        /// Gets the filename extension, in this case anything after the first
        /// period counts as the extension.
        /// </summary>
        /// <returns></returns>
        virtual std::string Extension() const { return m_fileName; }
        std::string m_extension = {};
    };
}
