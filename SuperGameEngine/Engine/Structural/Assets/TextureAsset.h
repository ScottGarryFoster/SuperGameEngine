#pragma once
#include "GameAsset.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Describes a texture asset loaded from file.
    /// This has more information than simply the texture itself, it also contains the intended use
    /// of the file such as how to split up the file and how best to render the image to screen.
    /// </summary>
    class TextureAsset : public GameAsset
    {
    public:
        /// <summary>
        /// The name of the asset.
        /// </summary>
        /// <returns>The name to display for tooling. </returns>
        /// <remarks>This can be used in games but should be avoided. </remarks>
    };
}

