#pragma once
#include "SuperTexture.h"
#include "../../Structural/Spatial/Area/Rectangle.h"

namespace SuperGameEngine
{
    /// <summary>
    /// A texture capable of providing segements of itself to render.
    /// </summary>
    class SplitTexture
    {
    public:
        SplitTexture();
        virtual ~SplitTexture();
        // Untested will uncomment when tested.
        //SplitTexture(std::shared_ptr<SuperTexture> superTexture);
        //virtual ~SplitTexture();

        /// <summary>
        /// Get all the segments of the texture.
        /// </summary>
        /// <returns>All the places on the texture to render. </returns>
        virtual std::vector<Rectangle> GetSplits();

        //virtual void AddSplit(Rectangle newLocation); Untested will uncomment when tested.
    };
}