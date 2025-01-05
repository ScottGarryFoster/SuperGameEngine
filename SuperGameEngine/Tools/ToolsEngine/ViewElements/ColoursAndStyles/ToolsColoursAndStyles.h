#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "ColourIdentity.h"
#include "ColourPalette.h"
#include "../../../ImGuiIncludes.h"
#include "ColoursAndStyles.h"
#include "EmbeddedFont.h"

namespace FatedQuestLibraries
{
    class PackagePaths;
}

using namespace FatedQuestLibraries;
using namespace SuperGameEngine;

namespace SuperGameTools
{
    /// <summary>
    /// Helps to keep the colours and styles uniform.
    /// </summary>
    class ToolsColoursAndStyles : public ColoursAndStyles
    {
    public:
        ToolsColoursAndStyles(const std::shared_ptr<PackagePaths>& paths);

        /// <summary>
        /// Called at the start of the tool to set global colours.
        /// </summary>
        virtual void SetGlobalColoursAndStyles() const override;

        /// <summary>
        /// Called before the main top menu.
        /// </summary>
        virtual void SetTopMenuColoursAndStyles() const override;

        /// <summary>
        /// Called after the main top menu.
        /// </summary>
        virtual void PopTopMenuColoursAndStyles() const override;

        /// <summary>
        /// Called before each of the top menu items.
        /// </summary>
        /// <param name="isOpen">True means item is open. </param>
        /// <param name="isHovered">True means item is hovered. </param>
        virtual void SetMenuColoursAndStyles(bool isOpen, bool isHovered) const override;

        /// <summary>
        /// Called after <see cref="SetMenuColoursAndStyles()"/>.
        /// </summary>
        virtual void PopMenuColoursAndStyles() const override;

        /// <summary>
        /// Call as a new dockable window is made.
        /// </summary>
        virtual void SetWindowTabColoursAndStyles(const bool isOpen, const bool isHovered) const override;

        /// <summary>
        /// Called after <see cref="SetWindowTabColoursAndStyles()"/>.
        /// </summary>
        virtual void PopWindowTabColoursAndStyles() const override;

    private:
        /// <summary>
        /// Helper class to grab paths.
        /// </summary>
        std::shared_ptr<PackagePaths> m_packagePaths;

        /// <summary>
        /// All colours we can draw from.
        /// </summary>
        std::unordered_map<ColourPalette, std::unordered_map<int, std::unordered_map<ColourIdentity, ImVec4>>> m_colorMap;

        /// <summary>
        /// The colours which are assigned as the global colours.
        /// </summary>
        std::unordered_map<ImGuiCol_, ImVec4> m_globalColours;

        /// <summary>
        /// The current palette set to.
        /// </summary>
        ColourPalette m_currentPalette;

        /// <summary>
        /// All direct paths to fonts.
        /// </summary>
        std::unordered_map<EmbeddedFont, std::string> m_fontPaths;

        /// <summary>
        /// The actual fonts loaded by size.
        /// Must be loaded at the start of the application.
        /// </summary>
        std::unordered_map<EmbeddedFont, std::unordered_map<float, ImFont*>> m_actualFonts;

        /// <summary>
        /// Create the actual ImGui Font.
        /// </summary>
        /// <param name="font">Font to create. </param>
        /// <param name="size">Size to create. </param>
        /// <remarks>Font must exist in the actual fonts dictionary. </remarks>
        void CreateFontImGui(EmbeddedFont font, float size);

        /// <summary>
        /// Push a font to draw.
        /// </summary>
        /// <param name="font">Font to draw. </param>
        /// <param name="size">Size to draw. </param>
        void PushFont(EmbeddedFont font, float size) const;

        /// <summary>
        /// Stop drawing font.
        /// </summary>
        /// <param name="font">Font drawn. </param>
        /// <param name="size">Size drawn. </param>
        void PopFont(EmbeddedFont font, float size) const;

        /// <summary>
        /// Convert Vec color to ImVec4.
        /// This is a stop gap to make it easier to key in values
        /// by 255.
        /// </summary>
        /// <param name="r">Red</param>
        /// <param name="g">Green</param>
        /// <param name="b">Blue</param>
        /// <param name="a">Alpha</param>
        /// <returns>ImVec version of a colour. </returns>
        ImVec4 FromColour(int r, int g, int b, int a) const;
    };
}


