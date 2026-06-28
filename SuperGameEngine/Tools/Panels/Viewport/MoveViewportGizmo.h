#pragma once
#include <array>
#include <memory>

#include "ViewportGizmo.h"
#include "Engine/Graphics/Texture/TextureTransformationDetails.h"
#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameEngine
{
    class SuperTexture;
    class PrimitiveRectangle;
    class PrimitiveShapeProvider;
    class TextureManager;
}

namespace SuperGameTools
{
    /// <summary>
    /// Handles specifically the movement viewport gizmo.
    /// </summary>
    class MoveViewportGizmo : public ViewportGizmo
    {
    public:

        MoveViewportGizmo(
            const std::shared_ptr<SuperGameEngine::TextureManager>& textureManager,
            const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider);
        virtual ~MoveViewportGizmo() = default;

        /// <summary>
        /// Draws the gizmo using the cords as the center point.
        /// </summary>
        void Draw() const override;

        /// <summary>
        /// Moves the gizmo to this location.
        /// </summary>
        /// <param name="x">X location of the drawing viewport. </param>
        /// <param name="y">Y location of the drawing viewport. </param>
        void UpdateGizmoLocation(int x, int y) override;

        /// <summary>
        /// Update where the mouse is relative to the drawing viewport.
        /// </summary>
        /// <param name="x">X location of the mouse. </param>
        /// <param name="y">Y location of the mouse. </param>
        void UpdateMouseLocation(int x, int y) override;

    private:

        /// <summary>
        /// Defines the elements which can be selected.
        /// Avoids many booleans where a single variable could define what is to be selected.
        /// </summary>
        enum GizmoElementName : uint8_t
        {
            None,
            LowerLeftArrow,
            UpperRightArrow,
            MoveAnywhereSquare,
        };

        /// <summary>
        /// Describes a single element of the Gizmo.
        /// </summary>
        struct GizmoElement
        {
        public:
            /// <summary>
            /// Texture to render.
            /// </summary>
            std::shared_ptr<SuperGameEngine::SuperTexture> Texture;

            /// <summary>
            /// Where to render the texture.
            /// </summary>
            FatedQuestLibraries::FPoint Location;

            /// <summary>
            /// Rotation of the texture.
            /// </summary>
            int Rotation = 0;

            /// <summary>
            /// If true then check both FirstCollisionRectangle and SecondCollisionRectangle.
            /// This is used instead of an array to avoid the heap.
            /// </summary>
            bool UsingBothCollisionRectangles = false;

            /// <summary>
            /// Mouse over collision shape.
            /// </summary>
            SuperGameEngine::RectangleInt FirstCollisionRectangle;

            /// <summary>
            /// Mouse over collision shape. Optional.
            /// </summary>
            SuperGameEngine::RectangleInt SecondCollisionRectangle;

            /// <summary>
            /// How to offset the location from the given asset we are attached to.
            /// </summary>
            FatedQuestLibraries::FPoint LocationOffset;

            /// <summary>
            /// How the first collision Rectangle should offset its location from the location.
            /// </summary>
            FatedQuestLibraries::FPoint FirstCollisionOffset;

            /// <summary>
            /// How the second collision Rectangle should offset its location from the location.
            /// </summary>
            FatedQuestLibraries::FPoint SecondCollisionOffset;

            /// <summary>
            /// Defines the rotation of a given texture.
            /// This is used when giving the rotation to a texture directly.
            /// </summary>
            SuperGameEngine::TextureTransformationDetails TransformationDetails;

            /// <summary>
            /// Used mainly for debugging on this struct and defines what this struct is describing.
            /// </summary>
            GizmoElementName ElementName;
        };

        /// <summary>
        /// The number of arrow elements.
        /// </summary>
        constexpr static size_t m_numberOfArrowElements = 2;

        /// <summary>
        /// The elements which are arrows or clickable elements to move the gizmo around.
        /// Note this is on the stack intentionally.
        /// </summary>
        GizmoElement m_arrowElements[m_numberOfArrowElements];

        /// <summary>
        /// The arrow texture used as a handle.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_arrowAsset;

        /// <summary>
        /// X location of the gizmo.
        /// </summary>
        int m_locationX;

        /// <summary>
        /// Y location of the gizmo.
        /// </summary>
        int m_locationY;

        /// <summary>
        /// X location of the mouse relative to the drawing viewport.
        /// </summary>
        int m_mouseX;

        /// <summary>
        /// Y location of the mouse relative to the drawing viewport.
        /// </summary>
        int m_mouseY;

        /// <summary>
        /// A rectangle for debug drawing.
        /// </summary>
        std::shared_ptr<SuperGameEngine::PrimitiveRectangle> m_debugRectangle;

        /// <summary>
        /// The element currently hovered.
        /// </summary>
        GizmoElementName m_elementHovered;

        /// <summary>
        /// Colour when no interaction is taking place.
        /// </summary>
        FatedQuestLibraries::FColour m_inactiveColour;

        /// <summary>
        /// Colour when hover is occuring.
        /// </summary>
        FatedQuestLibraries::FColour m_hoverColour;

        void UpdateInteractionStateOfGizmo();
    };  
}
