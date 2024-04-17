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
        virtual std::vector<Rectangle> GetSplits() override;

        /// <summary>
        /// Add a split to the list of splits.
        /// </summary>
        /// <param name="newLocation">New location for split. </param>
        virtual void AddSplit(const Rectangle& newLocation) override;

    private:
        /// <summary>
        /// The segments on the shape to render.
        /// </summary>
        std::vector<Rectangle> m_splits;
    };
}