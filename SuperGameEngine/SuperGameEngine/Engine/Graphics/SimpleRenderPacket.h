#pragma once
#include "../../Structural/Spatial/Area/RectangleInt.h"
#include "../../Structural/Spatial/Positional/Transform.h"
#include "SuperTexture.h"
#include "RenderPacket.h"

namespace SuperGameEngine
{
    /// <summary>
    /// Implements Render packet in the simplict way posible.
    /// </summary>
    class SimpleRenderPacket : public RenderPacket
    {
    public:
        SimpleRenderPacket();
        virtual ~SimpleRenderPacket();

        /// <summary>
        /// Empty all the information in the Packet.
        /// </summary>
        virtual void Clear() override;

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
            (const RectangleInt textureRectangle, const RectangleInt screenRectangle) override;

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
            GetRenderPacket(const FVector2D& offsetLocation) const override;

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
            (std::shared_ptr<SuperTexture> texture, const FVector2D& offsetLocation) const override;

        /// <summary>
        /// Draws the contents of the packet.
        /// </summary>
        /// <param name="texture">
        /// Texture to use when drawing.
        /// </param>
        /// <param name="transform">
        /// Offset the Rectangles by the location given, scale and rotation.
        /// This means that you can use 0,0 as the releative location for the 
        /// Draw and then use this location to not recreate the packet everytrime.
        /// </param>
        /// <remarks>
        /// Rotation is currently not implemented.
        /// </remarks>
        virtual void DrawPacket
            (std::shared_ptr<SuperTexture> texture, const std::shared_ptr<Transform> transform) const override;

    private:

        /// <summary>
        /// All the rectangles to draw.
        /// </summary>
        std::shared_ptr<FList<std::pair<RectangleInt, RectangleInt>>> renderPackets;
    };
}


