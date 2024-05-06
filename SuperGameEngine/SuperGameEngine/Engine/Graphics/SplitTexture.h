#pragma once
#include "SplitTextureAsset.h"
#include "../../LibraryIncludes.h"
#include "../../Engine/Graphics/RenderPacket.h"

namespace SuperGameEngine
{
    using namespace StandardCLibrary;

    /// <summary>
    /// A texture capable of providing segements of itself to render.
    /// </summary>
    class SplitTexture : public SplitTextureAsset
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
        /// <returns>
        /// True means split was valid and added to list.
        /// False means that the Split overlapped the edge of the texture.
        /// </returns>
        virtual bool AddSplit(const RectangleInt& newLocation) override;

        /// <summary>
        /// Draws the given part of the texture at the location.
        /// </summary>
        /// <param name="split">Split to draw, defines the location on the texture. </param>
        /// <param name="screenLocation">Locaiton and Size on the screen to draw. </param>
        /// <remark>
        /// Keep in mind Camera is not involved in this method this is screenspace.
        /// </remark>
        virtual void Draw(int split, const RectangleInt& screenLocation) const override;

        /// <summary>
        /// Loads an asset from a file, products, from some source of truth about
        /// the asset. The key should remain the same regardless as the asset location.
        /// </summary>
        /// <param name="key">Asset Key which is a location releative from products. </param>
        /// <returns>True means loaded, false means failed to load. </returns>
        virtual bool LoadAsset(std::shared_ptr<AssetLoader> assetLoader, FString key) override;

        /// <summary>
        /// Gets the Objects state as a render packet.
        /// </summary>
        /// <returns>The render state as a packet for drawing. </returns>
        virtual std::shared_ptr<RenderPacket> GetObjectRenderPacket() override;

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
            std::shared_ptr<Transform> transform) override;

    protected:
        /// <summary>
        /// The last render packet to be created.
        /// </summary>
        std::shared_ptr<RenderPacket> cachedRenderPacket;

    private:
        /// <summary>
        /// The segments on the shape to render.
        /// </summary>
        std::vector<RectangleInt> m_splits;

        /// <summary>
        /// Super texture for this texture.
        /// </summary>
        std::shared_ptr<SuperTexture> m_superTexture;

        /// <summary>
        /// A rectangle which represents the area for the rectangle.
        /// </summary>
        std::shared_ptr<RectangleInt> m_textureArea;

        /// <summary>
        /// Returns true if right is completely contained in right.
        /// </summary>
        /// <param name="left">The base. </param>
        /// <param name="right">The compare. </param>
        /// <returns>True means right is complete contained in left. </returns>
        bool Contains(const RectangleInt& left, const RectangleInt& right) const;
    };
}