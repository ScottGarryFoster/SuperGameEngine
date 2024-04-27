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
        virtual std::vector<RectangleInt> GetSplits() = 0;

        /// <summary>
        /// Add a split to the list of splits.
        /// </summary>
        /// <param name="newLocation">New location for split. </param>
        virtual void AddSplit(const RectangleInt& newLocation) = 0;

        /// <summary>
        /// Draws the given part of the texture at the location.
        /// </summary>
        /// <param name="split">Split to draw, defines the location on the texture. </param>
        /// <param name="location">Locaiton on the screen to draw. </param>
        /// <remark>
        /// Keep in mind Camera is not involved in this method this is screenspace.
        /// </remark>
        virtual void Draw(int split, FPoint& location) = 0;
    };
}