#pragma once
#include "ViewportButtonInfo.h"
#include "ViewportToolsButton.h"
#include "ViewportToolsType.h"
#include "Engine/Graphics/ImGuiSuperTexture.h"

namespace FatedQuestLibraries
{
    class FEvent;
}

namespace SuperGameTools
{
    class WindowPackage;
}

namespace SuperGameTools
{
    /// <summary>
    /// Renders and controls a single viewport tools button.
    /// </summary>
    class SuperViewportToolsButton : public ViewportToolsButton
    {
    public:

        SuperViewportToolsButton(
            const std::shared_ptr<WindowPackage>& windowPackage, 
            ViewportToolsType buttonType, 
            const ViewportButtonInfo& buttonInfo);

        /// <summary>
        /// Draw the button.
        /// </summary>
        virtual void Draw() override;

        /// <summary>
        /// Called when this button is selected.
        /// </summary>
        /// <returns>Called when this button is selected. </returns>
        virtual std::shared_ptr<FatedQuestLibraries::FEventSubscriptions> OnSelected() const override;

        /// <summary>
        /// Inform the observer an event has taken place.
        /// Do not store this pointer it is intended as a point for dynamic casting
        /// and not as long term storage. Directly after invocation it will be deleted.
        /// </summary>
        /// <param name="arguments">Arguments describing the event. </param>
        virtual void Invoke(std::shared_ptr<FatedQuestLibraries::FEventArguments> arguments) override;

        /// <summary>
        /// Select this button.
        /// </summary>
        virtual void Select() override;

    private:

        /// <summary>
        /// Called when this button is selected.
        /// </summary>
        std::shared_ptr<FatedQuestLibraries::FEvent> m_onSelected;

        /// <summary>
        /// The tools type this button represents.
        /// </summary>
        ViewportToolsType m_toolType;

        /// <summary>
        /// The texture we render.
        /// </summary>
        std::shared_ptr<SuperGameEngine::SuperTexture> m_texture;

        /// <summary>
        /// True means is selected.
        /// </summary>
        bool m_isSelected;

        /// <summary>
        /// The width and height of the texture.
        /// </summary>
        float m_textureWidthHeight;

        /// <summary>
        /// The amount of padding to give to the button to make it easier to hit.
        /// </summary>
        const float m_buttonPadding = 3;
    };
}
