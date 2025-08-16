#pragma once
#include <memory>
#include <vector>

namespace SuperGameTools
{
    class AssetMetaData;

    /// <summary>
    /// Loads, holds and provides <see cref="AssetMetaData"/> in a single location.
    /// </summary>
    class AssetTemplateProvider
    {
    public:

        /// <summary>
        /// Retrieve all the <see cref="AssetMetaData"/> objects loaded. 
        /// </summary>
        /// <returns>All the <see cref="AssetMetaData"/> objects loaded. </returns>
        virtual std::vector<std::shared_ptr<const AssetMetaData>> GetAssetTemplates() const = 0;
    };
}
