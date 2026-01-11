#pragma once
#include <string>

#include "Engine/Structural/Asset/AssetFiles/AssetFileType.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalObjectDataTemplate.h"

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// Templates also contain the ability to create fresh versions of the Asset file.
    /// </summary>
    class AssetTemplate : public virtual UniversalObjectDataTemplate
    {
    public:
        /// <summary>
        /// Gets the file type to create when creating a <see cref="AssetFile"/>.
        /// <see cref="AssetFileType::Unknown"/> means there is none set and the default should be used.
        /// </summary>
        /// <returns>The file type to be created. </returns>
        virtual AssetFileType GetAssetFileType() const = 0;
    };
}
