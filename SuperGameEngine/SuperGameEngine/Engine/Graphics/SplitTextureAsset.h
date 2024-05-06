#pragma once
#include "SuperTexture.h"
#include "../../Structural/Spatial/Area/RectangleInt.h"
#include "../../Engine/Loaders/AssetLoader.h"
#include "../../Engine/Graphics/CacheableRender.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture capable of providing segements of itself to render.
    /// </summary>
    class SplitTextureAsset : public Object, public CacheableRender
    {
    public:
        SplitTextureAsset() {}
        virtual ~SplitTextureAsset() {}

        /// <summary>
        /// Get all the segments of the texture.
        /// </summary>
        /// <returns>All the places on the texture to render. </returns>
        virtual std::vector<RectangleInt> GetSplits() const = 0;

        /// <summary>
        /// Add a split to the list of splits.
        /// </summary>
        /// <param name="newLocation">New location for split. </param>
        /// <returns>
        /// True means split was valid and added to list.
        /// False means that the Split overlapped the edge of the texture.
        /// </returns>
        virtual bool AddSplit(const RectangleInt& newLocation) = 0;

        /// <summary>
        /// Draws the given part of the texture at the location.
        /// </summary>
        /// <param name="split">Split to draw, defines the location on the texture. </param>
        /// <param name="screenLocation">Locaiton and Size on the screen to draw. </param>
        /// <remark>
        /// Keep in mind Camera is not involved in this method this is screenspace.
        /// </remark>
        virtual void Draw(int split, const RectangleInt& screenLocation) const = 0;
        
        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(std::shared_ptr<AssetLoader> assetLoader, FString key) = 0;
    };
}