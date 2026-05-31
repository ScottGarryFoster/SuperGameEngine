#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// Renders and handles interactions for the gizmo in the viewport.
    /// This is the behaviours directly on game objects like move.
    /// </summary>
    class ViewportGizmo
    {
    public:
        /// <summary>
        /// Draws the gizmo using the cords as the center point.
        /// </summary>
        virtual void Draw() const = 0;

        /// <summary>
        /// Moves the gizmo to this location.
        /// </summary>
        /// <param name="x">X location of the drawing viewport. </param>
        /// <param name="y">Y location of the drawing viewport. </param>
        virtual void UpdateGizmoLocation(int x, int y) = 0;

        /// <summary>
        /// Update where the mouse is relative to the drawing viewport.
        /// </summary>
        /// <param name="x">X location of the mouse. </param>
        /// <param name="y">Y location of the mouse. </param>
        virtual void UpdateMouseLocation(int x, int y) = 0;
    };
}
