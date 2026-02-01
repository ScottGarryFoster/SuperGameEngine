#pragma once
#include <memory>
#include <unordered_map>

#include "ViewportButtonInfo.h"
#include "ViewportTools.h"

namespace SuperGameTools
{
    struct ViewportButtonInfo;
    class SuperViewportToolsButton;
    class WindowPackage;

    /// <summary>
    /// The tools which accompany the scene viewport.
    /// </summary>
    class SuperViewportTools : public virtual ViewportTools
    {
    public:

        SuperViewportTools(const std::shared_ptr<WindowPackage>& windowPackage);

        /// <summary>
        /// Gets the currently selected tool.
        /// </summary>
        /// <returns>The selected tool. </returns>
        virtual ViewportToolsType GetSelectedTool() const override;

        /// <summary>
        /// Selects a new tool.
        /// </summary>
        /// <param name="newValue">New tool to select. </param>
        virtual void SelectTool(ViewportToolsType newValue) override;

        /// <summary>
        /// Draw the viewport tools bar. 
        /// </summary>
        virtual void Draw() const override;

    private:

        /// <summary>
        /// The currently selected tool.
        /// </summary>
        ViewportToolsType m_selectedTool;

        /// <summary>
        /// The ability to draw and access other systems.
        /// </summary>
        std::shared_ptr<WindowPackage> m_windowPackage;

        /// <summary>
        /// The viewport buttons.
        /// </summary>
        std::unordered_map<ViewportToolsType, std::shared_ptr<SuperViewportToolsButton>> m_toolsButtons;

        /// <summary>
        /// Defines all the viewport button information in a raw format.
        /// </summary>
        ViewportButtonInfo m_viewportButtonInfo;
    };
}
