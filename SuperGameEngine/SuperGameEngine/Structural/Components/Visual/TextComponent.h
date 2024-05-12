#pragma once
#include "../../GameObject/GameComponent.h"
#include "../../Scene/SceneLoadPackage.h"
#include "../../../UserInterface/Text/FontFaceAsset.h"

namespace SuperGameEngine
{
    class RenderPacket;

    /// <summary>
    /// Renders text.
    /// </summary>
    class TextComponent : public GameComponent
    {
    public:
        TextComponent();
        virtual ~TextComponent();

        /// <summary>
        /// Sets up the Component.
        /// </summary>
        /// <param name="loadPackage">Everything a Component needs to be a game object. </param>
        virtual void Setup(SceneLoadPackage* loadPackage, GameObject* parent) override;

        /// <summary>
        /// Entry point for the entire game.
        /// </summary>
        /// <param name="tick">Ticks since last frame. </param>
        /// <returns>True means continue. False means close. </returns>
        virtual bool Update(const GameTime gameTime) override;

        /// <summary>
        /// Draw everything in the game.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Set the text to display.
        /// </summary>
        /// <param name="newValue">New value to set. </param>
        void SetText(const FText& newValue);

        /// <summary>
        /// Get the current text set.
        /// </summary>
        /// <returns>Current text. </returns>
        const FText GetText();
    private:

        /// <summary>
        /// The font used for the Text.
        /// </summary>
        std::shared_ptr<FontFaceAsset> m_fontFace;

        /// <summary>
        /// The text for the component.
        /// </summary>
        std::shared_ptr<FText> m_componentText;

        /// <summary>
        /// Cached Render information - how to render the text.
        /// </summary>
        std::shared_ptr<RenderPacket> m_textRenderPacket;
    };
}