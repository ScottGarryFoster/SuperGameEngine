#pragma once
#include "../../../Input/InputManagement/SuperInputManager.h"

namespace SuperGameTools
{
    /// <summary>
    /// Renders and handles interactions for the gizmo in the viewport.
    /// This is the behaviours directly on game objects like move.
    /// </summary>
    class ViewportGizmo : public FatedQuestLibraries::FEventObserver
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

        /// <summary>
        /// Called when whatever button is bound to select the gizmo has changed at this location.
        /// </summary>
        /// <param name="x">Location of the change. </param>
        /// <param name="y">Location of the change. </param>
        /// <param name="state">Change which occured. </param>
        virtual void UpdateMouseSelectionInput(int x, int y, SuperGameInput::KeyOrButtonState state) = 0;

        /// <summary>
        /// Called when mouse is outside the viewport.
        /// Handle anything needed.
        /// </summary>
        virtual void UpdateOnMouseIsOutsideOfViewport() = 0;

        /// <summary>
        /// Called when an interaction from the outside (from say a mouse interaction) now should be actioned
        /// by the owning engine to perform gizmo actions.
        /// </summary>
        /// <returns>Called when an interaction from the outside. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnInteractionChanged() const = 0;
    };
}
