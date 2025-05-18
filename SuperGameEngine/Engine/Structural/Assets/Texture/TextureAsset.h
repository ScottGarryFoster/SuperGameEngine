#pragma once
#include "../GameAsset.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a texture asset loaded from file.
    /// This has more information than simply the texture itself, it also contains the intended use
    /// of the file such as how to split up the file and how best to render the image to screen.
    /// </summary>
    class TextureAsset : public virtual GameAsset
    {
    public:

        /// <summary>
        /// Draws to screen at the default position and size.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Draws the tile as defined by the asset meta file.
        /// </summary>
        /// <param name="tile">
        /// The texture tile to render.
        /// </param>
        virtual void Draw(int tile) const = 0;
    };
}

