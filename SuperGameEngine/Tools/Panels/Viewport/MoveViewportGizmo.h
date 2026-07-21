#pragma once
#include <array>
#include <memory>

#include "ViewportGizmo.h"
#include "Engine/Graphics/Texture/TextureTransformationDetails.h"
#include "Panels/ViewportTools/ViewportDebugOption.h"
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

        /// <summary>
        /// Called when whatever button is bound to select the gizmo has changed at this location.
        /// </summary>
        /// <param name="x">Location of the change. </param>
        /// <param name="y">Location of the change. </param>
        /// <param name="state">Change which occured. </param>
        virtual void UpdateMouseSelectionInput(int x, int y, SuperGameInput::KeyOrButtonState state) override;

        /// <summary>
        /// Called when mouse is outside the viewport.
        /// Handle anything needed.
        /// </summary>
        virtual void UpdateOnMouseIsOutsideOfViewport() override;

        /// <summary>
        /// Called when an interaction from the outside (from say a mouse interaction) now should be actioned
        /// by the owning engine to perform gizmo actions.
        /// For the move gizmo this will be a <see cref="MoveInteractionChangedEvent"/>
        /// </summary>
        /// <returns>Called when an interaction from the outside. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnInteractionChanged() const override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

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
            /// The colour for the gizmo when inactive.
            /// </summary>
            FatedQuestLibraries::FColour InactiveColour;

            /// <summary>
            /// The colour for the gizmo when hovered.
            /// </summary>
            FatedQuestLibraries::FColour HoverColour;

            /// <summary>
            /// The colour for the gizmo when selected.
            /// </summary>
            FatedQuestLibraries::FColour SelectedColour;

            /// <summary>
            /// True when this element is hovered.
            /// </summary>
            bool Hovered = false;

            /// <summary>
            /// True when this element is selected.
            /// </summary>
            bool Selected = false;

            /// <summary>
            /// Used mainly for debugging on this struct and defines what this struct is describing.
            /// </summary>
            GizmoElementName ElementName;
        };

        /// <summary>
        /// The number of arrow elements.
        /// </summary>
        constexpr static size_t m_numberOfArrowElements = 3;

        /// <summary>
        /// The elements which are arrows or clickable elements to move the gizmo around.
        /// Note this is on the stack intentionally.
        /// </summary>
        GizmoElement m_arrowElements[m_numberOfArrowElements];

        /// <summary>
        /// The index of the selected gizmo.
        /// Set to -1 if none are selected.
        /// </summary>
        int m_selectedGizmo;

        /// <summary>
        /// Set to the mouse location when mouse is pressed on a gizmo.
        /// Then used to calculate the distance when moving the gizmo.
        /// </summary>
        FPoint m_originalLocation;

        /// <summary>
        /// The arrow texture used as a handle.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_arrowAsset;

        /// <summary>
        /// The move asset for the corner
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_moveAsset;

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
        /// Colour when no interaction is taking place.
        /// </summary>
        FatedQuestLibraries::FColour m_inactiveColour;

        /// <summary>
        /// Colour when hover is occuring.
        /// </summary>
        FatedQuestLibraries::FColour m_hoverColour;

        /// <summary>
        /// Colour when selected is occuring.
        /// </summary>
        FatedQuestLibraries::FColour m_selectedColour;

        /// <summary>
        /// Called when an interaction from the outside (from say a mouse interaction) now should be actioned
        /// by the owning engine to perform gizmo actions.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onInteractionChanged;

        /// <summary>
        /// The option selected to view debug helpers in the viewport.
        /// </summary>
        ViewportDebugOption m_debugOption;

        /// <summary>
        /// On movement, this will update the look of the Gizmo.
        /// </summary>
        void UpdateInteractionStateOfGizmo();

        /// <summary>
        /// React to a mouse button press (first frame of down)
        /// </summary>
        /// <param name="x">X mouse position. </param>
        /// <param name="y">Y mouse position. </param>
        void SetupInteractionWhenMouseHasJustBeenPressed(int x, int y);

        /// <summary>
        /// React to a mouse button release (first frame up)
        /// </summary>
        /// <param name="x">X mouse position. </param>
        /// <param name="y">Y mouse position. </param>
        void SetupInteractionWhenMouseHasJustBeenReleased(int x, int y);

        /// <summary>
        /// React to the mouse being down.
        /// </summary>
        /// <param name="x">X mouse position. </param>
        /// <param name="y">Y mouse position. </param>
        void SetupInteractionWhenMouseIsDown(int x, int y);
    };  
}
