#pragma once

namespace SuperGameTools
{
    /// <summary>
    /// Helps to keep the colours and styles uniform.
    /// </summary>
    class ColoursAndStyles
    {
    public:

        /// <summary>
        /// Called at the start of the tool to set global colours.
        /// </summary>
        virtual void SetGlobalColoursAndStyles() const = 0;

        /// <summary>
        /// Called before the main top menu.
        /// </summary>
        virtual void SetTopMenuColoursAndStyles() const = 0;

        /// <summary>
        /// Called after the main top menu.
        /// </summary>
        virtual void PopTopMenuColoursAndStyles() const = 0;

        /// <summary>
        /// Set colours for the top menu.
        /// </summary>
        /// <param name="isOpen">True means item is open. </param>
        /// <param name="isHovered">True means item is hovered. </param>
        virtual void SetMenuColoursAndStyles(bool isOpen, bool isHovered) const = 0;

        /// <summary>
        /// Called after <see cref="SetMenuColoursAndStyles()"/>.
        /// </summary>
        virtual void PopMenuColoursAndStyles() const = 0;

        /// <summary>
        /// Call as a new dockable window is made.
        /// </summary>
        /// <param name="isOpen">True means window is open. </param>
        /// <param name="isHovered">True means window is hovered. </param>
        virtual void SetWindowTabColoursAndStyles(const bool isOpen, const bool isHovered) const = 0;

        /// <summary>
        /// Called after <see cref="SetWindowTabColoursAndStyles()"/>.
        /// </summary>
        virtual void PopWindowTabColoursAndStyles() const = 0;
    };
}


