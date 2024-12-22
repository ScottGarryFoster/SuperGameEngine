#pragma once
#include <memory>
#include <vector>

namespace FatedQuestLibraries
{
    class PackageFile;

    /// <summary>
    /// The files which the file systems use.
    /// </summary>
    class PackageFiles
    {
    public:
        /// <summary>
        /// All the files in the package.
        /// </summary>
        /// <returns>All the files in the package. </returns>
        std::vector<std::shared_ptr<PackageFile>> GetFiles() const;

        /// <summary>
        /// Sets the files in the package.
        /// </summary>
        /// <param name="files">New files to set. </param>
        void SetFiles(const std::vector<std::shared_ptr<PackageFile>>& files);

    private:
        /// <summary>
        /// Saved package files.
        /// </summary>
        std::vector<std::shared_ptr<PackageFile>> m_packageFile;
    };
}
