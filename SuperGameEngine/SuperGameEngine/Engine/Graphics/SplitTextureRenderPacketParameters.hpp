#pragma once

namespace SuperGameEngine
{
    /// <summary>
    /// Parameters required to create a render packet from a Split Texture.
    /// </summary>
    class SplitTextureRenderPacketParameters
    {
    public:
        /// <summary>
        /// The split of the Texture to render.
        /// Default to 0 if not found and render nothing if nothing found.
        /// </summary>
        int Split = 0;
    };
}