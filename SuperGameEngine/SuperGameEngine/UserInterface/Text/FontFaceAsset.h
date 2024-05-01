#pragma once
#include "../../LibraryIncludes.h"
#include "../../Engine/Graphics/SplitTextureAsset.h"
#include "../../Structural/Spatial/Positional/Transform.h"

namespace SuperGameEngine_UserInterface
{
    using namespace SuperGameEngine;
    using namespace StandardCLibrary;

    class FontFaceAsset : public SplitTextureAsset
    {
    public:
        /// <summary>
        /// Adds a single letter to the Font.
        /// </summary>
        /// <param name="character">Character to add. </param>
        /// <param name="location">Location on the texture the letter is. </param>
        /// <returns>True means letter was added successfully. </returns>
        virtual bool AddCharacter(wchar_t character, RectangleInt location) = 0;

        /// <summary>
        /// Draws the text at the given location.
        /// </summary>
        /// <param name="text">Text to draw. </param>
        /// <param name="transform">Location to draw the text. </param>
        /// <remark>
        /// Note this transform location uses 0,0 to mean the top left of the screen.
        /// This does not mean you cannot use it as world location but there are better
        /// draws using Camera for this which would adjust with the camera world space.
        /// </remark>
        virtual void DrawText(std::shared_ptr<FText> text, std::shared_ptr<Transform> transform) = 0;
    };
}