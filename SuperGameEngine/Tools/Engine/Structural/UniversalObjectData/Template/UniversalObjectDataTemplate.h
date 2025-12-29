#pragma once
#include <string>
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
    };
}
