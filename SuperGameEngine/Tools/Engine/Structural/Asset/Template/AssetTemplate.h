#pragma once
#include <string>

#include "Engine/Structural/UniversalObjectData/Template/UniversalTemplate.h"

namespace SuperGameTools
{
    enum class AssetFileType : uint8_t;

    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// Templates also contain the ability to create fresh versions of the Asset file.
    /// </summary>
    class AssetTemplate : public virtual UniversalTemplate
    {
    public:
        /// <summary>
        /// Determines if this template is the one to use.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means this template is correct. </returns>
        virtual bool ShouldUseTemplate(const std::string& filepath) const = 0;

        /// <summary>
        /// Gets the file type to create when creating a <see cref="AssetFile"/>.
        /// <see cref="AssetFileType::Unknown"/> means there is none set and the default should be used.
        /// </summary>
        /// <returns>The file type to be created. </returns>
        virtual AssetFileType GetAssetFileType() const = 0;
    };
}
