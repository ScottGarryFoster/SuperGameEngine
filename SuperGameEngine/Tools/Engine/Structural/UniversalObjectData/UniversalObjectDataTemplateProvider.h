#pragma once
#include <memory>
#include <vector>

namespace SuperGameTools
{
    class SingleLayoutMetaData;

    /// <summary>
    /// Loads, holds and provides <see cref="SingleLayoutMetaData"/> in a single location.
    /// </summary>
    class UniversalObjectDataTemplateProvider
    {
    public:

        /// <summary>
        /// Retrieve all the <see cref="SingleLayoutMetaData"/> objects loaded. 
        /// </summary>
        /// <returns>All the <see cref="SingleLayoutMetaData"/> objects loaded. </returns>
        virtual std::vector<std::shared_ptr<const SingleLayoutMetaData>> GetObjectDataTemplates() const = 0;
    };
}
