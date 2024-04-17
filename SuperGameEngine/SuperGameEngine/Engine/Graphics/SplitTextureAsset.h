#pragma once
#include "SuperTexture.h"
#include "../../Structural/Spatial/Area/Rectangle.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture capable of providing segements of itself to render.
    /// </summary>
    class SplitTextureAsset
    {
    public:
        /// <summary>
        /// Get all the segments of the texture.
        /// </summary>
        /// <returns>All the places on the texture to render. </returns>
        virtual std::vector<Rectangle> GetSplits() = 0;

        /// <summary>
        /// Add a split to the list of splits.
        /// </summary>
        /// <param name="newLocation">New location for split. </param>
        virtual void AddSplit(const Rectangle& newLocation) = 0;
    };
}