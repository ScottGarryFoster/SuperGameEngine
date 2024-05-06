#pragma once
#include "../../Structural/Spatial/Area/RectangleInt.h"
#include "../../Structural/Spatial/Positional/Transform.h"
#include "SuperTexture.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Offers the ability to capture the state of an objects draw loop
    /// such that you can draw it at a later date.
    /// This stores the data and allows this transaction to take place.
    /// </summary>
    class RenderPacket
    {
    public:
        /// <summary>
        /// Empty all the information in the Packet.
        /// </summary>
        virtual void Clear() = 0;

        /// <summary>
        /// Add a render to the packet.
        /// </summary>
        /// <param name="textureRectangle">
        /// Where to render on the texture.
        /// </param>
        /// <param name="screenRectangle">
        /// Where to render on screen.
        /// Relative to 0,0 of the world or screen if using the transform offset,
        /// as the offset means you do not need to recalculate everything just move the
        /// location.
        /// </param>
        virtual void AddDrawPacket
            (const RectangleInt textureRectangle, const RectangleInt screenRectangle) = 0;

        /// <summary>
        /// Returns the Rectangles used in the render.
        /// </summary>
        /// <param name="offsetLocation">
        /// Offset the Rectangles by the location given.
        /// This means that you can use 0,0 as the releative location for the 
        /// Draw and then use this location to not recreate the packet everytrime.
        /// </param>
        /// <returns>
        /// The Draw Rectangles used for the Draw. 
        /// TextureRectangle - Where on the texture to draw.
        /// ScreenRectangle - Where on the screen to draw.
        /// </returns>
        virtual const std::shared_ptr<FList<std::pair<RectangleInt, RectangleInt>>>
            GetRenderPacket(const FVector2D& offsetLocation) const = 0;

        /// <summary>
        /// Draws the contents of the packet.
        /// </summary>
        /// <param name="texture">
        /// Texture to use when drawing.
        /// </param>
        /// <param name="offsetLocation">
        /// Offset the Rectangles by the location given.
        /// This means that you can use 0,0 as the releative location for the 
        /// Draw and then use this location to not recreate the packet everytrime.
        /// </param>
        virtual void DrawPacket
            (std::shared_ptr<SuperTexture> texture, const FVector2D& offsetLocation) const = 0;
    };

}