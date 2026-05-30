#pragma once
#include <memory>
#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameEngine
{
    class PrimitiveShapeProvider;
    class PrimitiveRectangle;
    class SuperTexture;
    class TextureManager;
}

namespace SuperGameTools
{
    /// <summary>
    /// Renders and handles interactions for the gizmo in the viewport.
    /// This is the behaviours directly on game objects like move.
    /// </summary>
    class ViewportGizmo
    {
    public:

        ViewportGizmo(
            const std::shared_ptr<SuperGameEngine::TextureManager>& textureManager, 
            const std::shared_ptr<SuperGameEngine::PrimitiveShapeProvider>& primitiveShapeProvider);

        /// <summary>
        /// Draws the gizmo using the cords as the center point.
        /// </summary>
        void Draw() const;

        /// <summary>
        /// Moves the gizmo to this location.
        /// </summary>
        /// <param name="x">X location of the drawing viewport. </param>
        /// <param name="y">Y location of the drawing viewport. </param>
        void UpdateGizmoLocation(int x, int y);

        /// <summary>
        /// Update where the mouse is relative to the drawing viewport.
        /// </summary>
        /// <param name="x">X location of the mouse. </param>
        /// <param name="y">Y location of the mouse. </param>
        void UpdateMouseLocation(int x, int y);

    private:

        /// <summary>
        /// Defines the elements which can be selected.
        /// Avoids many booleans where a single variable could define what is to be selected.
        /// </summary>
        enum GizmoElement : uint8_t
        {
            None,
            LowerRightArrow,
        };

        /// <summary>
        /// The arrow used as a handle.
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
        /// The arrow which moves left to right X position.
        /// This is precalculated on update.
        /// </summary>
        int m_bottomRightArrowX;

        /// <summary>
        /// The arrow which moves left to right Y position.
        /// This is precalculated on update.
        /// </summary>
        int m_bottomRightArrowY;

        /// <summary>
        /// The mouse collision position for the lower right arrow.
        /// </summary>
        SuperGameEngine::RectangleInt m_lowerRightArrowCollision;

        /// <summary>
        /// A rectangle for debug drawing.
        /// </summary>
        std::shared_ptr<SuperGameEngine::PrimitiveRectangle> m_debugRectangle;

        /// <summary>
        /// The element currently hovered.
        /// </summary>
        GizmoElement m_elementHovered;

        /// <summary>
        /// Colour when no interaction is taking place.
        /// </summary>
        FatedQuestLibraries::FColour m_inactiveColour;

        /// <summary>
        /// Colour when hover is occuring.
        /// </summary>
        FatedQuestLibraries::FColour m_hoverColour;
    };
}
