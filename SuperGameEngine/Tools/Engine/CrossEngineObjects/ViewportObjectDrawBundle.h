#pragma once
#include "DrawBundleSelectionState.h"
#include "FatedQuestLibraries.h"
#include "Structural/Spatial/Area/RectangleInt.h"

namespace SuperGameEngine
{
    class TextureAsset;
}

namespace SuperGameTools
{
    /// <summary>
    /// Holds information to draw an element.
    /// </summary>
    struct ViewportObjectDrawBundle
    {
    public:

        /// <summary>
        /// True means this draw bundle is complete and able to render.
        /// </summary>
        bool IsValidToRender;

        /// <summary>
        /// The GUID of the game object.
        /// </summary>
        /// <remarks>
        /// This is stored as the string representation because the object is a struct
        /// and GUID is implemented different dependent on platform.
        /// </remarks>
        std::string Guid;

        /// <summary>
        /// The texture to render.
        /// </summary>
        std::shared_ptr<SuperGameEngine::TextureAsset> TextureAsset;

        /// <summary>
        /// The transform position.
        /// </summary>
        FatedQuestLibraries::FVector2F TransformPosition;

        /// <summary>
        /// A rectangle around the shape for collision within the viewport.
        /// </summary>
        SuperGameEngine::RectangleInt FaceRectangle;

        /// <summary>
        /// Describes the selection state of the given draw bundle so that it maybe rendered correctly.
        /// </summary>
        DrawBundleSelectionState SelectionState;
    };
}
