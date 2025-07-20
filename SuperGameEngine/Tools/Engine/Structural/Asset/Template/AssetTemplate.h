#pragma once
#include <string>

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// Templates also contain the ability to create fresh versions of the Asset file.
    /// </summary>
    class AssetTemplate
    {
    public:
        virtual ~AssetTemplate() = default;

        /// <summary>
        /// Determines if this template is the one to use.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means this template is correct. </returns>
        virtual bool ShouldUseTemplate(const std::string& filepath) const = 0;

        /// <summary>
        /// Create an asset file based on the file path.
        /// </summary>
        /// <param name="filepath">Filepath to use as a base. </param>
        /// <returns>An asset file </returns>
        virtual std::string CreateAssetFile(const std::string& filepath) const = 0;
    };
}