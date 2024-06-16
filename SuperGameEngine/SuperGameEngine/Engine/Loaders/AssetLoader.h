#pragma once
#include "../../LibraryIncludes.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Loads an asset from product contents.
    /// </summary>
    class AssetLoader
    {
    public:
        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(std::shared_ptr<Object>& subject, FString key) = 0;

        /// <summary>
        /// Loads the asset from raw data.
        /// </summary>
        /// <param name="subject">The output. </param>
        /// <param name="subject">The data. </param>
        /// <returns>True means loaded. </returns>
        virtual bool LoadAssetFromData(std::shared_ptr<Object>& subject, std::vector<unsigned char>& data) = 0;

        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(Object* subject, FString key) = 0;
    };
}