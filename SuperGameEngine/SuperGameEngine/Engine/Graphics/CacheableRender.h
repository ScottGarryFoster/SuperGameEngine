#pragma once
#include "RenderPacket.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Offers the ability to capture the state of an objects draw loop
    /// such that you can draw it at a later date.
    /// </summary>
    class CacheableRender
    {
    public:
        /// <summary>
        /// Gets the Objects state as a render packet.
        /// </summary>
        /// <returns>The render state as a packet for drawing. </returns>
        virtual std::shared_ptr<RenderPacket> GetObjectRenderPacket() = 0;

        /// <summary>
        /// Draws the Object using the Render Packet.
        /// </summary>
        /// <param name="renderPacket">
        /// The state of this object as a Render Packet.
        /// </param>
        /// <param name="transform">
        /// Current transform. Used to move the draw without a complete
        /// recalculation.
        /// </param>
        virtual void DrawPacket(
            std::shared_ptr<RenderPacket> renderPacket, 
            std::shared_ptr<Transform> transform) = 0;
    };
}