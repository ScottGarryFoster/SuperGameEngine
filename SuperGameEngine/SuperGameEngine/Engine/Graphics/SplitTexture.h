#pragma once
#include "SplitTextureAsset.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture capable of providing segements of itself to render.
    /// </summary>
    class SplitTexture : public SplitTextureAsset, public Object
    {
    public:
        SplitTexture(std::shared_ptr<SuperTexture> superTexture);
        virtual ~SplitTexture();

        /// <summary>
        /// Get all the segments of the texture.
        /// </summary>
        /// <returns>All the places on the texture to render. </returns>
        virtual std::vector<RectangleInt> GetSplits() override;

        /// <summary>
        /// Add a split to the list of splits.
        /// </summary>
        /// <param name="newLocation">New location for split. </param>
        virtual void AddSplit(const RectangleInt& newLocation) override;

        /// <summary>
        /// Draws the given part of the texture at the location.
        /// </summary>
        /// <param name="split">Split to draw, defines the location on the texture. </param>
        /// <param name="location">Locaiton on the screen to draw. </param>
        /// <remark>
        /// Keep in mind Camera is not involved in this method this is screenspace.
        /// </remark>
        virtual void Draw(int split, FPoint& location);
    private:
        /// <summary>
        /// The segments on the shape to render.
        /// </summary>
        std::vector<RectangleInt> m_splits;

        /// <summary>
        /// Super texture for this texture.
        /// </summary>
        std::shared_ptr<SuperTexture> m_superTexture;
    };
}