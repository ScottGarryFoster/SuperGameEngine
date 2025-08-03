#pragma once
#include <memory>
#include <string>
#include <vector>

#include "ToolsEngine/FrameworkManager/SelectionManager/Selectable.h"

namespace SuperGameEngine
{
    class RectangleInt;
}

namespace SuperGameTools
{
    class AssetMetaData;
    class AssetFolder;

    /// <summary>
    /// Represents a single Asset File.
    /// </summary>
    class AssetFile : public virtual Selectable
    {
    public:

        /// <summary>
        /// Gets the parent folder.
        /// </summary>
        /// <returns>The parent of the given file. </returns>
        virtual std::weak_ptr<AssetFolder> GetParent() const = 0;

        /// <summary>
        /// Get the name to display in a browser.
        /// </summary>
        /// <returns>The display name. </returns>
        virtual std::string GetDisplayName() const = 0;

        /// <summary>
        /// Get the path to this file in relation to the package.
        /// </summary>
        /// <returns>The path relative to the products folder. </returns>
        virtual std::string GetPackagePath() const = 0;

        /// <summary>
        /// Draws an image representing the file with the given size.
        /// </summary>
        /// <param name="screenRectangle">Location and size on the screen to draw. </param>
        virtual void DrawLargeTile(const SuperGameEngine::RectangleInt& screenRectangle) const = 0;

        /// <summary>
        /// Selects this file or tile.
        /// </summary>
        virtual void SelectFile() = 0;

        /// <summary>
        /// Unselects this file or tile.
        /// </summary>
        virtual void UnselectFile() = 0;

        /// <summary>
        /// True means the file is selected in the browser.
        /// </summary>
        /// <returns>True means the file is selected in the browser. </returns>
        virtual bool IsSelected() const = 0;

        /// <summary>
        /// Get the metadata for this file type. This describes. how to edit the file.
        /// </summary>
        /// <returns>The metadata for this file type. This describes. how to edit the file. </returns>
        virtual const std::shared_ptr<const AssetMetaData> GetMetaData() const = 0;
    };
}
