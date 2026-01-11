#pragma once
#include <string>

#include "UniversalObjectDataFileType.h"
#include "Engine/Structural/UniversalObjectData/Template/UniversalTemplate.h"

namespace SuperGameTools
{
    /// <summary>
    /// Contains a template and the ability to detect whether using the template is correct.
    /// Templates also contain the ability to create fresh versions of the Asset file.
    /// </summary>
    class UniversalObjectDataTemplate : public virtual UniversalTemplate
    {
    public:
        /// <summary>
        /// Determines if this template is the one to use.
        /// </summary>
        /// <param name="filepath">Filepath to test. </param>
        /// <returns>True means this template is correct. </returns>
        virtual bool ShouldUseTemplate(const std::string& filepath) const = 0;

        /// <summary>
        /// Gets the file type to create when creating a <see cref="UniversalObjectData"/> file type.
        /// <see cref="UniversalObjectDataFileType::Unknown"/> means there is none set and the default should be used.
        /// This is very general and there tend to be more specific types at higher levels.
        /// </summary>
        /// <returns>The file type to be created. </returns>
        virtual UniversalObjectDataFileType GetUniversalObjectDataFileType() const = 0;
    };
}
